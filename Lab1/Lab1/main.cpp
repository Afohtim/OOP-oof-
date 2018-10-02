#include <iostream>
#include "List.h"
#include "Tree.h"

int main()
{
	List<int> list;
	list.push(0, 1);
	list.pushBack(4);
	list.push(1, 3);
	for (int i = 0; i < list.length(); ++i)
	{
		std::cout << list[i] << ' ';
	}
	system("pause");
}