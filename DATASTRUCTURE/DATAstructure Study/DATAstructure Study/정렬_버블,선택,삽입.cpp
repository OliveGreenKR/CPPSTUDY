#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>


//버블정렬 
void BubbleSort(vector<int>& v)
{
	int n = static_cast<int>(v.size());
	int cnt = 0;
	bool fn = false;

	while (!fn)
	{
		for (int i = 0; i < n - 1; i++)
		{
			if (v[i] > v[i + 1])
			{
				::swap(v[i], v[i + 1]);
				cnt++;
			}
			if (i != 0 && cnt == 0)
			{
				fn = true;
				break;
			}
			if (i == n - 2)
			{
				n--;
			}
		}
	}
}

void PrintVec(const vector<int>& v)
{
	const int n = static_cast<int>(v.size());

	for (int i = 0; i < n - 1; i++)
	{
		cout << v[i] << endl;
	}
}



int main()
{
	vector<int> v = { 1,4,6,10,200,39 };
	
	//BubbleSort(v);

	PrintVec(v);


	
}