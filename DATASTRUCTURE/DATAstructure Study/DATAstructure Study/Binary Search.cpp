#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>
#include <list>

using namespace std;

#include "BinarySearchTree.h"

#if 0
vector<int> numbers;


void BinarySearch(int N)
{
	int last = static_cast<int>(numbers.size()) - 1;
	int start = 0;

	while (true)
	{
		int middle = (last + start) / 2;

		if (numbers[middle] == N)
		{
			cout << "found!" << endl;
			break;
		}

		if (middle <= 0 || middle >= numbers.size() - 1)
		{
			cout << "Not found!" << endl;
			break;
		}

		if (numbers[middle] < N)
		{
			start = middle + 1;
			continue;
		}

		last = middle - 1;

	}
}









#if 1
int main()
{
	numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 81 ,99 };

	BinarySearch(82);
}
#endif // 1

#endif // 1
#if 1

int main()
{
	BinarySearchTree bst;
	
	bst.Insert(20);
	bst.Insert(10);
	bst.Insert(30);
	bst.Insert(25);
	bst.Insert(26);
	bst.Insert(40);
	bst.Insert(50);

	Node* root = bst.Getroot();
	
	bst.Delete(20);
	bst.Delete(26);
	bst.Delete(30);
	bst.Print();

	//Node* max = bst.Max(root);
	//Node* min = bst.Min(root);
	//Node* next = bst.Next(bst.Search(26));

}
#endif // 1

