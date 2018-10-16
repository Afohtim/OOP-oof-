#pragma once

template<typename TValue>
struct BSNode
{
	BSNode(TValue value);
	TValue val;
	BSNode<TValue>* parent;
	BSNode<TValue>* left;
	BSNode<TValue>* right;  
};

template<typename TValue>
class BSTree
{
protected:
	void del_subtree(BSNode<TValue>* node);
	BSNode* root;
	void delNode(BSNode<TValue>* node);
public:
	BSTree();
	~BSTree();

	void insert(TValue value, TValue parent = NULL);
	void erase(TValue value);
	void showSubTree(MultiNode<TValue>* rootNode);
	void showTree();
};

template<typename TValue>
inline void BSTree<TValue>::del_subtree(BSNode<TValue>* node)
{

}

template<typename TValue>
inline void BSTree<TValue>::delNode(BSNode<TValue>* node)
{
	if (node->left != nullptr)
	{
		(BSNode<TValue>* subnode = node->left;
		while (subnode->right != nullptr)
		{
			subnode = subnode->right;
		}
		node->val = subnode->val;
		delete subnode;

	}
	else if (node->right != nullptr)
	{
		Node *subnode = node->right;
		while (subnode->left != nullptr)
		{
			subnode = subnode->left;
		}
		node->val = subnode->val;
		delete subnode;
	}
}

template<typename TValue>
inline void BSTree<TValue>::insert(TValue value, TValue parent)
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
			if (parent->val > insert->val)
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
