#include <iostream>
#include "List.h"
#include "MultiTree.h"
#include "BSTree.h"

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

	BSTree<int> tree;
	tree.insert(4);
	tree.insert(3);
	tree.insert(6);
	tree.insert(5);
	tree.showTree();
	tree.erase(4);
	tree.showTree();
	system("pause");
}