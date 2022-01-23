#if 0
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

	for (int i = 0; i < n; i++)
	{
		cout << v[i] << endl;
	}
}

void SelectionSort(vector<int>& v)
{
	int n = static_cast<int>(v.size());
	int cnt = 0;
	bool fn = false;

	for (int i = 0; i < n - 1; i++)
	{
		int small = INT_MAX;
		for (int j = i; j < n; j++)
		{
			if (v[j] < small)
			{
				small = v[j];
				::swap(v[j], v[i]);
			}

		}
	}
}

void InsertSort(vector<int>& v)
{
	const int n = static_cast<int>(v.size());
	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];
		int j;
		for (j = i - 1; j >= 0; j--) //정렬안된 배열
		{
			if (v[j] > insertData)
			{
				v[j + 1] = v[i];
			}
			else
				break;
		}
		v[j + 1] = insertData;
	}

}
int main()
{
	vector<int> v = { 100, 1,4,6,10,39 };

	//BubbleSort(v);
	SelectionSort(v);
	PrintVec(v);
}
#endif // 0
