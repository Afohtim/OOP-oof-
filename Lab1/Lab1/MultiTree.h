#pragma once
#include "List.h"
#include "Tree.h"


template<typename TValue>
struct MultiNode 
{
	MultiNode(TValue value);
	TValue val;
	List<MultiNode<TValue>*>* childrens;
	MultiNode<TValue>* parent;
};


template<typename TValue>
class MultiTree : Tree<TValue>
{
private:
	MultiNode<TValue>* root;
	MultiNode<TValue>* dfs(MultiNode<TValue>* node, TValue value);
	void delSubTree(MultiNode<TValue>* node);
public:
	MultiTree();
	virtual ~MultiTree();
	void insert(TValue value, TValue parent = NULL);
	void erase(TValue value);
	void showSubTree(MultiNode<TValue>* rootNode);
	void showTree();
};


template<typename TValue>
MultiNode<TValue>* MultiTree<TValue>::dfs(MultiNode<TValue>* node, TValue value)
{
	if (node->val == value)
	{
		return node;
	}
	for (unsigned i = 0; i < node->childrens->length(); ++i)
	{
		MultiNode<TValue>* res = dfs((*(node->childrens))[i], value);
		if (res != nullptr)
		{
			return res;
		}
	}

	return nullptr;
}

template<typename TValue>
inline void MultiTree<TValue>::delSubTree(MultiNode<TValue>* node)
{
	if (node->childrens->length() == 0)
	{
		delete node;
	}
	else
	{
		for (unsigned i = 0; i < node->childrens->length(); ++i)
		{
			delSubTree((*(node->childrens))[i]);
		}
		delete node;
	}
}

template<typename TValue>
inline MultiTree<TValue>::MultiTree()
{
	root = nullptr;
}

template<typename TValue>
inline MultiTree<TValue>::~MultiTree()
{
	delSubTree(root);
}

template<typename TValue>
void MultiTree<TValue>::insert(TValue value, TValue parent)
{
	MultiNode<TValue>* insertedNode = new MultiNode<TValue>(value);
	if (root == nullptr)
	{
		root = insertedNode;
	}
	else
	{
		MultiNode<TValue>* par = dfs(root, parent);
		par->childrens->pushBack(insertedNode);
		insertedNode->parent = par;
	}
}

template<typename TValue>
void MultiTree<TValue>::erase(TValue value)
{
	MultiNode<TValue>* erased = dfs(root, value);
	if (erased == nullptr)
	{
		return;
	}
	MultiNode<TValue>* par = erased->parent;
	for (unsigned i = 0; i < par->childrens->length(); ++i)
	{
		if ((*(par->childrens))[i] == erased)
		{
			par->childrens->erase(i);
			break;
		}
	}
	for (unsigned i = 0; i < erased->childrens->length(); ++i)
	{
		par->childrens->pushBack((*(erased->childrens))[i]);
	}
	delete erased;
}

template<typename TValue>
void MultiTree<TValue>::showSubTree(MultiNode<TValue>* rootNode)
{
	std::cout << rootNode->val << ": ";
	for (unsigned i = 0; i < rootNode->childrens->length(); ++i)
	{
		std::cout << ((*(rootNode->childrens))[i])->val << ' ';
	}
	std::cout << '\n';
	for (unsigned i = 0; i < rootNode->childrens->length(); ++i)
	{
		showSubTree((*(rootNode->childrens))[i]);
	}
}

template<typename TValue>
void MultiTree<TValue>::showTree()
{
	if (root != nullptr)
	{
		showSubTree(root);
	}
}

template<typename TValue>
inline MultiNode<TValue>::MultiNode(TValue value)
{
	val = value;
	childrens = new List<MultiNode<TValue>*>;
	parent = nullptr;
}
