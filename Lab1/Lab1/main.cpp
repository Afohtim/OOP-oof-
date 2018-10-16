#include <iostream>
#include "List.h"
#include "MultiTree.h"
#include "BSTree.h"
#include "BinTree.h"

int main()
{
	List<int> list;
	list.push(0, 1);
	list.pushBack(4);
	list.push(1, 3);
	for (unsigned i = 0; i < list.length(); ++i)
	{
		std::cout << list[i] << ' ';
	}
	std::cout << '\n';

	BinTree<int> tree;
	tree.insertLeft(4);
	tree.insertRight(3);
	tree.insertLeft(6, 3);
	tree.insertRight(5);
	tree.showTree();
	tree.erase(5);
	tree.showTree();
	system("pause");
}