#include <iostream>
#include "Red_black_tree.h"
#include <fstream>
#include <clocale>
#include <Windows.h>

using namespace std;

void print_tree(vector<vector<pair<Elem, int > > > v_tree)
{
	ofstream fout("tree.txt");
	int k = 1;
	for (auto row : v_tree)
	{
		cout << k << "r ";
		fout << k << "r ";
		for (auto val : row)
		{
			cout << (val.first.data == "" ? "." : std::to_string(val.first.id) + ":" + val.first.data + ":" + std::to_string(val.second) ) << ' ';
			fout << (val.first.data == "" ? "." : std::to_string(val.first.id) + ":" + val.first.data + ":" + std::to_string(val.second) ) << ' ';
		}
		
		cout << '\n';
		fout << '\n';
		++k;
	}
}

int main() 
{

	
	ifstream fin("data.txt");
	Red_black_tree<Elem> tree;
	vector<shared_ptr<Elem> > data;
	for (int i = 0; i < 10; ++i)
	{
		int k;
		string name, surname;
		fin >> k >> name >> surname;
		data.push_back(shared_ptr<Elem>(new Elem(k, name + " " + surname)));
		tree.insert(data.back());

	}
	
	vector<vector<pair<Elem, int > > > v_tree;
	v_tree = tree.show_tree();
	print_tree(v_tree);
	cout << '\n';
	
#ifdef _MSC_VER
	system("pause");
#endif // _MSC_VER


	
}