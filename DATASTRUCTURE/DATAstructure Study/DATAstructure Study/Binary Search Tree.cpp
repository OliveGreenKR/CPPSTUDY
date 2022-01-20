#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>
#include <list>

using namespace std;


vector<int> numbers;


void BinarySearch(int N)
{
	int last = static_cast<int>(numbers.size());
	int start = 0;

	while(true)
	{
		int middle = (last + start)/ 2;

		if (numbers[middle] == N)
		{
			cout << "found!" << endl;
			break;
		}
			
		if (middle <= 0 || middle >= numbers.size()-1)
		{
			cout << "Not found!" << endl;
			break;
		}

		if (numbers[middle] < N)
		{
			start = middle;
			continue;
		}

		last = middle;

	}
}

#if 1
int main()
{
	numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 81 ,99 };

	BinarySearch(82);
}
#endif // 1
