#pragma once
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;
using std::pair;

enum {Black, Red};


struct Elem
{
	explicit Elem(int id, string data) : id(id), data(data) {};
	Elem() {};
	string data;
	int id;
	bool operator<(Elem other);
	bool operator<=(Elem other);
	bool operator>(Elem other);
	bool operator>=(Elem other);
	bool operator==(Elem other);
};

template<class T>
struct Node
{
	Node(shared_ptr<T> key, shared_ptr<Node> parent = nullptr, int node_color = Red);
	int color;
	//shared_ptr<Elem> key;
	shared_ptr<T> key;
	shared_ptr<Node> parent;
	shared_ptr<Node> left;
	shared_ptr<Node> right;

};

template<class T>
class Red_black_tree
{
private:
	shared_ptr<Node<T> > root;
	shared_ptr<Node<T> > root_par;
	vector<vector<pair<T, int> > > current_tree;
	bool updated;

	void insert_balance(shared_ptr<Node<T> >);
	void erase_balance(shared_ptr<Node<T> >, shared_ptr<Node<T> >);

	void rotate_left(shared_ptr<Node<T> >);
	void rotate_right(shared_ptr<Node<T> >);

	shared_ptr<Node<T> > successor(shared_ptr<Node<T> >);
	shared_ptr<Node<T> > find_node(shared_ptr<T> key);
	void erase(shared_ptr<Node<T> >);

	void refresh_tree(int depth, int n, shared_ptr<Node<T> > node);

public:
	vector<vector<pair<T, int> > > show_tree();
	void insert(shared_ptr<T> key);
	void erase(shared_ptr<T> key);
	Red_black_tree();
	~Red_black_tree();
};

#include "Red_black_tree.tlt"



