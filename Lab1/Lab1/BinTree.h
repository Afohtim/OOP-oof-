#pragma once
#include <stdlib.h> 

struct BinNode
{
	BinNode* left;
	BinNode* right;
	int val;

};

class BinTree
{
private:
	BinNode* root;
public:
	BinTree();
	~BinTree();
	void insert(int val);


};

