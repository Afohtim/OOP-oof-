#include <iostream>
#include "Red_black_tree.h"
#include <fstream>
#include <clocale>
#include <Windows.h>

using namespace std;

void print_tree(vector<vector<string>* >* v_tree)
{
	ofstream fout("tree.txt");
	int k = 1;
	for (auto row : *v_tree)
	{
		cout << k << "r ";
		fout << k << "r ";
		for (auto val : *row)
		{
			cout << (val == "" ? "." : val) << ' ';
			fout << (val == "" ? "." : val) << ' ';
			/*for (int i = 0; i < (1 << (v_tree->size() - k)); ++i)
			{

				cout << '\t';
				fout << '\t';
			}*/
		}
		
		cout << '\n';
		fout << '\n';
		++k;
	}
}

int main() 
{

	
	ifstream fin("data.txt");
	Red_black_tree tree;
	vector<shared_ptr<Elem> > data;
	for (int i = 0; i < 10; ++i)
	{
		int k;
		string name, surname;
		fin >> k >> name >> surname;
		data.push_back(shared_ptr<Elem>(new Elem(k, name + " " + surname)));
		tree.insert(data.back());

	}
	vector<vector<string>* >* v_tree;
	v_tree = tree.show_tree();
	print_tree(v_tree);
	cout << '\n';
	
#ifdef _MSC_VER
	system("pause");
#endif // _MSC_VER


	
}