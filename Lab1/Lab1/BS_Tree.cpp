#include "BS_Tree.h"

void BS_Tree::del_subtree(Node *node)
{
	if (node->left != nullptr)
		del_subtree(node->left);

	if (node->right != nullptr)
		del_subtree(node->right);

	delete node;
}

Node* BS_Tree::push_node(unsigned key)
{
	if (root == nullptr)
	{
		root = new Node(key);
		return root;
	}
	Node *node = root;
	while (true)
	{
		if (key == node->val)
		{
			return node;
		}
		else if (key < node->val)
		{
			if (node->left != nullptr)
			{
				node = node->left;
			}
			else
			{
				node->left = new Node(key, node);
				return node->left;
			}
		}
		else
		{
			if (node->right != nullptr)
			{
				node = node->right;
			}
			else
			{
				node->right = new Node(key, node);
				return node->right;
			}
		}
	}
}

Node* BS_Tree::del_node(unsigned key)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	Node *node = root;
	while (true)
	{
		if (key == node->val)
		{
			if (node->left != nullptr)
			{
				Node *subnode = node->left;
				while (subnode->right != nullptr)
				{
					subnode = subnode->right;
				}
				node->val = subnode->val;
				return subnode;

			}
			else if (node->right != nullptr)
			{
				Node *subnode = node->right;
				while (subnode->left != nullptr)
				{
					subnode = subnode->left;
				}
				node->val = subnode->val;
				return subnode;
			}
			return node;
		}
		else if (key < node->val)
		{
			if (node->left != nullptr)
			{
				node = node->left;
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			if (node->right != nullptr)
			{
				node = node->right;
			}
			else
			{
				return nullptr;
			}
		}
	}
}


BS_Tree::BS_Tree()
{
	root = nullptr;
}


BS_Tree::~BS_Tree()
{
	del_subtree(root);
}

void BS_Tree::insert(unsigned key)
{
	push_node(key);
}

void BS_Tree::erase(unsigned key)
{
	Node *deleted = del_node(key);
	delete deleted;
}



Node::Node(unsigned key, Node *parent)
{
	left = right = nullptr;
	par = parent;
	val = key;
}