#pragma once
#include <string>
#include <vector>


using std::string;
using std::vector;

enum {Black, Red};

struct Elem
{
	Elem(int key, string data) : key(key), data(data) {};
	string data;
	int key;
};

struct Node
{
	Node(Elem* key, Node* parent = nullptr, int node_color = Red);
	int color;
	Elem* key;
	Node* parent;
	Node* left;
	Node* right;
	int inserted_less;

};

class Tree
{
private:
	Node* root;
	Node* root_par;
	vector<vector<string>* >* current_tree;
	bool updated;

	void insert_balance(Node*);
	void erase_balance(Node*, Node*);

	void rotate_left(Node*);
	void rotate_right(Node*);

	Node* successor(Node*);
	Node* find_node(Elem* key);
	void erase(Node*);

	void show_tree(int depth, int n, Node* node);

public:
	vector<vector<string>* >* show_tree();
	void insert(Elem* key);
	void erase(Elem* key);
	Tree();
	~Tree();
};

