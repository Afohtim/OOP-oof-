#pragma once
#include "List.h"


template<typename TValue>
struct TNode
{
	TValue val;
	unsigned key;
	List* childrens;
	TNode<TValue> parent;
};


template<typename TValue>
class Tree
{
private:
	TNode<TValue>* root;
	TNode<TValue>* dfs(TNode<TValue>* node, unsigned key);
	unsigned nextkey;
public:
	void insert(TValue value, unsigned key);
	void erase(unsigned key);
	//TValue key(unsigned key);
	Tree();
	~Tree();
};

template<typename TValue>
Tree<TValue>::Tree()
{
	root = nullptr;
	nextkey = 0;
}


template<typename TValue>
TNode<TValue>* Tree<TValue>::dfs(TNode<TValue>* node, unsigned key)
{
	if (node->key == key)
		return node;
	else
	{
		unsigned length = node->children->length();
		for (unsigned i = 0; i < length; ++i)
		{
			TNode<TValue>* searchedNode = dfs(*(node->children)[i], key);
			if (searchedNode != nullptr)
				return searchedNode;
		}
	}
	return nullptr;
}

template<typename TValue>
void Tree<TValue>::insert(TValue value, unsigned key)
{
	TNode<TValue>* node = new TNode<TValue>;
	node->val = value;
	TNode<TValue>* parent = dfs(root, key);
	node->parent = parent;
	parent->childrens->pushBack(node);
}

template<typename TValue>
void Tree<TValue>::erase(unsigned key)
{
	TNode<TValue>* node = dfs(root, key);
	TNode<TValue>* parent = node->parent;
	unsigned siblingsNum = parent->childrens->length();
	for (unsigned i = 0; i < siblingsNum; ++i)
	{
		if (*(parent->childrens)[i] == node)
		{
			erase(i);
			break;
		}
	}
	delete node;
}

