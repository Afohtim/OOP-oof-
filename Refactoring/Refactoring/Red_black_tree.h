#pragma once
#include <string>
#include <vector>
#include <memory>


using std::string;
using std::vector;
using std::shared_ptr;

enum {Black, Red};

struct Elem
{
	Elem(int key, string data) : key(key), data(data) {};
	string data;
	int key;
};

struct Node
{
	Node(shared_ptr<Elem> key, shared_ptr<Node> parent = nullptr, int node_color = Red);
	int color;
	shared_ptr<Elem> key;
	shared_ptr<Node> parent;
	shared_ptr<Node> left;
	shared_ptr<Node> right;
	int inserted_less;

};

class Red_black_tree
{
private:
	shared_ptr<Node> root;
	shared_ptr<Node> root_par;
	vector<vector<string>* >* current_tree;
	bool updated;

	void insert_balance(shared_ptr<Node>);
	void erase_balance(shared_ptr<Node>, shared_ptr<Node>);

	void rotate_left(shared_ptr<Node>);
	void rotate_right(shared_ptr<Node>);

	shared_ptr<Node> successor(shared_ptr<Node>);
	shared_ptr<Node> find_node(shared_ptr<Elem> key);
	void erase(shared_ptr<Node>);

	void show_tree(int depth, int n, shared_ptr<Node> node);

public:
	vector<vector<string>* >* show_tree();
	void insert(shared_ptr<Elem> key);
	void erase(shared_ptr<Elem> key);
	Red_black_tree();
	~Red_black_tree();
};

