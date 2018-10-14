#include <iostream>
#include "List.h"
#include "MultiTree.h"

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

	MultiTree<int> tree;
	tree.insert(4);
	tree.insert(3, 4);
	tree.showTree();
	tree.erase(3);
	system("pause");
}