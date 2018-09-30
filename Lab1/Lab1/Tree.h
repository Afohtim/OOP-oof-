#pragma once
#include "List.h"


template<typename TValue>
struct TNode
{
	TValue val;
	unsigned key;
	List* childrens;
};


template<typename TValue>
class Tree
{
private:
	TNode<TValue>* root;
	TNode<TValue>* dfs(unsigned key = 0);
	unsigned nextkey
public:
	void insert(unsigned key, TValue value);
	void erase(unsigned key);
	TValue key(unsigned key);
	Tree();
	~Tree();
};

