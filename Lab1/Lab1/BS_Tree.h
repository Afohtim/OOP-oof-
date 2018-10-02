#pragma once

struct Node
{
	Node(unsigned key, Node *parent = nullptr);
	int val;
	Node *par;
	Node *left, *right;
	unsigned key;
};


class BS_Tree
{
protected:
	void del_subtree(Node *node);
	Node* root;
	Node* push_node(unsigned key);
	Node* del_node(unsigned key);
public:
	BS_Tree();
	~BS_Tree();

	virtual void insert(unsigned key);
	virtual void erase(unsigned key);
};
