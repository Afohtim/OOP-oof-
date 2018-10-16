#pragma once

template<typename TValue>
struct BSNode
{
	BSNode(TValue value);
	~BSNode();
	TValue val;
	BSNode<TValue>* left;
	BSNode<TValue>* right;
	BSNode<TValue>* parent;
};

template<typename TValue>
class BSTree
{
protected:
	void delSubtree(BSNode<TValue>* node);
	BSNode<TValue>* root;
	void delNode(BSNode<TValue>* node);
	void showSubTree(BSNode<TValue>* rootNode);
public:
	BSTree();
	~BSTree();

	void insert(TValue value);
	void erase(TValue value);
	void showTree();
};

template<typename TValue>
inline void BSTree<TValue>::delSubtree(BSNode<TValue>* node)
{
	if (node == nullptr || (node->left == nullptr && node->right == nullptr))
	{
		delete node;
	}
	else
	{
		delSubtree(node->left);
		delSubtree(node->right);
		delete node;
	}
}

template<typename TValue>
void BSTree<TValue>::delNode(BSNode<TValue>* node)
{
	if (node->left != nullptr)
	{
		BSNode<TValue>* subnode = node->left;
		while (subnode->right != nullptr)
		{
			subnode = subnode->right;
		}
		node->val = subnode->val;
		delete subnode;

	}
	else if (node->right != nullptr)
	{
		BSNode<TValue>* subnode = node->right;
		while (subnode->left != nullptr)
		{
			subnode = subnode->left;
		}
		node->val = subnode->val;
		delete subnode;
	}
	else
	{
		delete node;
	}
}

template<typename TValue>
inline BSTree<TValue>::BSTree()
{
	root = nullptr;
}

template<typename TValue>
inline BSTree<TValue>::~BSTree()
{
	delSubtree(root);
}

template<typename TValue>
inline void BSTree<TValue>::insert(TValue value)
{
	BSNode<TValue>* inserted = new BSNode<TValue>(value);
	if (root == nullptr)
	{
		root = inserted;
	}
	else
	{
		BSNode<TValue>* parent = root;
		while (true)
		{
			if (parent->val > inserted->val)
			{
				if (parent->left == nullptr)
				{
					parent->left = inserted;
					inserted->parent = parent;
					break;
				}
				else
				{
					parent = parent->left;
				}
			}
			else 
			{
				if (parent->right == nullptr)
				{
					parent->right = inserted;
					inserted->parent = parent;
					break;
				}
				else
				{
					parent = parent->right;
				}
			}
		}
	}
}

template<typename TValue>
inline void BSTree<TValue>::erase(TValue value)
{
	BSNode<TValue>* tempNode = root;
	while (true)
	{
		if (tempNode == nullptr)
			return;
		if (tempNode->val == value)
		{
			delNode(tempNode);
			return;
		}
		else if (tempNode->val < value)
		{
			tempNode = tempNode->right;
		}
		else if (tempNode->val > value)
		{
			tempNode = tempNode->left;
		}
	}
	
}

template<typename TValue>
void BSTree<TValue>::showSubTree(BSNode<TValue>* rootNode)
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
inline void BSTree<TValue>::showTree()
{
	showSubTree(root);
}

template<typename TValue>
inline BSNode<TValue>::BSNode(TValue value)
{
	val = value;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

template<typename TValue>
inline BSNode<TValue>::~BSNode()
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
