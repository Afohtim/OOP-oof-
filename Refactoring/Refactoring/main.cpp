﻿#include <iostream>
#include "Tree.h"
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
	Tree tree;
	vector<Elem*> data;
	for (int i = 0; i < 10; ++i)
	{
		int k;
		string name, surname;
		fin >> k >> name >> surname;
		data.push_back(new Elem(k, name + " " + surname));
		tree.insert(data.back());

	}
	vector<vector<string>* >* v_tree;
	v_tree = tree.show_tree();
	print_tree(v_tree);
	cout << '\n';
	
	cout << '\n';


	system("pause");

	
}