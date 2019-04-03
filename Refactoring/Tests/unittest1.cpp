#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Refactoring/Red_black_tree.h"
#include <fstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::ofstream;
using std::ifstream;
//using std::getline;

void print_tree(vector<vector<string> > v_tree)
{
	ofstream fout("tree.txt");
	int k = 1;
	for (auto row : v_tree)
	{
		for (auto val : row)
		{
			fout << (val == "" ? "." : val) << ' ';
		}
		fout << '\n';
		++k;
	}
}

void AssertFilesAreEqual(string file1, string file2)
{
	ifstream correct_tree(file1);
	ifstream result_tree(file2);
	string result_tree_row, correct_tree_row;
	while (getline(result_tree, result_tree_row))
	{
		getline(correct_tree, correct_tree_row);
		Assert::AreEqual(correct_tree_row, result_tree_row);
	}
}

namespace Tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestClassInit)
		{
			Red_black_tree tree;
			Assert::IsTrue(true);
		}
		TEST_METHOD(InsertRoot)
		{
			Red_black_tree tree;
			tree.insert(shared_ptr<Elem>(new Elem(1, "1")));


			print_tree(tree.show_tree());
			//AssertFilesAreEqual("insert_root.tr", "tree.txt");
			ifstream correct_tree("insert_root.tr");
			ifstream result_tree("tree.txt");
			string result_tree_row, correct_tree_row;
			while (getline(result_tree, result_tree_row))
			{
				getline(correct_tree, correct_tree_row);
				Assert::AreEqual(correct_tree_row, result_tree_row);
			}
		}

		TEST_METHOD(Insert10Elements)
		{
			Red_black_tree tree;

			for (int i = 0; i < 10; ++i)
			{
				tree.insert(shared_ptr<Elem>(new Elem(i, std::to_string(i))));
			}


			print_tree(tree.show_tree());
			//AssertFilesAreEqual("insert_root.tr", "tree.txt");
			ifstream correct_tree("insert_10_elem.tr");
			ifstream result_tree("tree.txt");
			string result_tree_row, correct_tree_row;
			while (getline(result_tree, result_tree_row))
			{
				getline(correct_tree, correct_tree_row);
				Assert::AreEqual(correct_tree_row, result_tree_row);
			}
		}

		TEST_METHOD(Insert15Delete5Elem)
		{
			Red_black_tree tree;

			for (int i = 0; i < 15; ++i)
			{
				tree.insert(shared_ptr<Elem>(new Elem(i, std::to_string(i))));
			}
			for (int i = 3; i < 15; i += 2)
			{
				tree.erase(shared_ptr<Elem>(new Elem(i, std::to_string(i))));
			}


			print_tree(tree.show_tree());
			//AssertFilesAreEqual("insert_root.tr", "tree.txt");
			ifstream correct_tree("insert_15_delete_5.tr");
			ifstream result_tree("tree.txt");
			string result_tree_row, correct_tree_row;
			while (getline(result_tree, result_tree_row))
			{
				getline(correct_tree, correct_tree_row);
				Assert::AreEqual(correct_tree_row, result_tree_row);
			}
		}

	};
}