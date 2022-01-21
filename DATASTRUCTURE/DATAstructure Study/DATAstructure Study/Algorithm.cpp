#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>
#include <list>

using namespace std;

#include "BinarySearchTree.h"
#include <thread>


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
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);


	bst.Insert(40);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(50);
	bst.Print();
	this_thread::sleep_for(1s);

}
#endif // 1

