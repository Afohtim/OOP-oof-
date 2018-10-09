#include "BinTree.h"



BinTree::BinTree()
{
}


BinTree::~BinTree()
{
}

void BinTree::insert(int val)
{
	BinNode* randNode = root;
	BinNode* newNode = new BinNode;

	while (randNode->left == nullptr && randNode->right == nullptr)
	{
		if (rand() & 1)
		{
			if (randNode->left == nullptr)
			{
				randNode->left = newNode;
			}
			else
			{
				randNode = randNode->left;
			}
		}
		else
		{
			if (randNode->right == nullptr)
			{
				randNode->right = newNode;
			}
			else
			{
				randNode = randNode->right;
			}
		}
	}
}
