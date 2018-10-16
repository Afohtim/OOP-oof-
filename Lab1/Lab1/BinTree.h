#pragma once

template<typename TValue>
struct BinNode
{
	BinNode(TValue value);
	~BinNode();
	BinNode<TValue>* left;
	BinNode<TValue>* right;
	BinNode<TValue>* parent;
	TValue val;
	

};

template<typename TValue>
class BinTree
{
private:
	BinNode<TValue>* root;
	BinNode<TValue>* dfs(BinNode<TValue>* root, TValue value);
	BinNode<TValue>* search(TValue value);
	void showSubTree(BinNode<TValue>* rootNode);
public:
	BinTree();
	~BinTree();
	void insertLeft(TValue value, TValue parent = NULL);
	void insertRight(TValue value, TValue parent = NULL);
	void erase(TValue value);
	void showTree();
};

template<typename TValue>
BinNode<TValue>* BinTree<TValue>::dfs(BinNode<TValue>* root, TValue value)
{
	if (root->val == value)
	{
		return root;
	}
	else
	{
		BinNode<TValue>* child = dfs(root->left, value);
		if (child == nullptr)
		{
			child = dfs(root->right, value);
		}
		return child;
	}
	return nullptr;
}

template<typename TValue>
inline BinNode<TValue>* BinTree<TValue>::search(TValue value)
{
	return dfs(root, value);
}

template<typename TValue>
void BinTree<TValue>::showSubTree(BinNode<TValue>* rootNode)
{
	if (rootNode == nullptr)
		return;
	std::cout << rootNode->val << ": ";
	if (rootNode->left != nullptr)
	{
		std::cout << rootNode->left->val << ' ';
	}
	if (rootNode->right != nullptr)
	{
		std::cout << rootNode->right->val;
	}
	std::cout << '\n';
	showSubTree(rootNode->left);
	showSubTree(rootNode->right);
}

template<typename TValue>
inline BinTree<TValue>::BinTree()
{
	root = nullptr;
}

template<typename TValue>
inline BinTree<TValue>::~BinTree()
{

}

template<typename TValue>
void BinTree<TValue>::insertLeft(TValue value, TValue parent)
{
	BinNode<TValue>* inserted = new BinNode<TValue>(value);
	if (parent == NULL)
	{
		inserted->left = root;
		root = inserted;
	}
	else
	{
		BinNode<TValue>* par = search(parent);
		if (par == nullptr)
			return;
		inserted->left = par->left;
		inserted->parent = par;
		par->left = inserted;
	}
}

template<typename TValue>
void BinTree<TValue>::insertRight(TValue value, TValue parent)
{
	BinNode<TValue>* inserted = new BinNode<TValue>(value);
	if (parent == NULL)
	{
		inserted->right = root;
		root = inserted;
	}
	else
	{
		BinNode<TValue>* par = search(parent);
		if (par == nullptr)
			return;
		inserted->right = par->right;
		inserted->parent = par;
		par->right = inserted;
	}
}

template<typename TValue>
void BinTree<TValue>::erase(TValue value)
{
	BinNode<TValue>* erased = search(value);
	if (erased == nullptr)
		return;
	if (erased->left != nullptr)
	{
		BinNode<TValue>* subnode = erased->left;
		while (subnode->right != nullptr)
		{
			subnode = subnode->right;
		}
		erased->val = subnode->val;
		delete subnode;
	}
	else if (erased->right != nullptr)
	{
		BinNode<TValue>* subnode = erased->right;
		while (subnode->left != nullptr)
		{
			subnode = subnode->left;
		}
		erased->val = subnode->val;
		delete subnode;
	}
	else
	{
		delete erased;
	}
}

template<typename TValue>
inline void BinTree<TValue>::showTree()
{
	showSubTree(root);
}

template<typename TValue>
inline BinNode<TValue>::BinNode(TValue value)
{
	val = value;
	left = nullptr;
	right = nullptr;
}

template<typename TValue>
inline BinNode<TValue>::~BinNode()
{
	if (this->parent != nullptr)
	{
		if (this == parent->left)
		{
			parent->left = nullptr;
		}
		else
		{
			parent->right = nullptr;
		}
	}
}
