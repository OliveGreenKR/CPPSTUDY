#if 1
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

//병합정렬_결합
void MergeResult(vector<int>& v, int left, int mid, int right)
{
	//각 블럭은 정렬되어있다고 가정(정복됨)


	int leftidx = left; //왼쪽 블럭
	int rightidx = mid + 1; // 오른쪽 블럭
	vector<int> tmp;

	while (leftidx <= mid && rightidx <= right)
	{
		if (v[leftidx] <= v[rightidx])
		{
			tmp.push_back(v[leftidx]);
			leftidx++;
		}
		else
		{
			tmp.push_back(v[rightidx]);
			rightidx++;
		}
	}
	//둘중 하나의 블럭이 끝난 상태
	//왼쪽이 먼저 끝났나? 그럼 오른쪽 데이터 복사
	if (leftidx > mid)
	{
		while (rightidx <= right)
		{
			tmp.push_back(v[rightidx]);
			rightidx++;
		}
	}
	else
	{
		while (leftidx <= mid)
		{
			tmp.push_back(v[leftidx]);
			leftidx++;
		}
	}

	//v는 유효영역이 정해졌기 때문에 단순복사하면 안됨.
	for (int i = 0; i < tmp.size(); i++)
	{
		v[left + i] = tmp[i];
	}
}

//병합정렬
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right) //기저상황 : 분할 마무리
		return;

	//분할 및 정복 
	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	//결합하는 함수
	MergeResult(v, left, mid, right);
}

//버블정렬 N^2
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

//선택정렬 N^2
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
//삽입정렬 N^2
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

//힙 정렬
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, ::greater<int>> pq;

	//N(데이터개수) * logN(우선순위 큐 데이터 삽입)
	for (int num : v)
	{
		pq.push(num);
	}

	v.clear();

	//N(데이터개수) * logN(우선순위 큐)
	while (pq.empty()==false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
	//따라서 최종 복잡도는
	// N log N
}

//퀵 정렬
int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];

	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low] )
			low++;
		while (high >= left + 1 && pivot <= v[high])
			high--;
		if (low < high)
			::swap(v[low], v[high]);
	}

	swap(v[left], v[high]);
	return high;
}
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;
	int pivot = Partition(v, left, right);

	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot+1, right);
}
int main()
{
	vector<int> v;

	srand(time(nullptr));

	for (int i = 0; i < 50; i++)
	{
		v.push_back(rand() % 100);
	}

	//BubbleSort(v);
	//SelectionSort(v);

	//HeapSort(v);
	//MergeSort(v, 0, v.size() - 1);
	QuickSort(v, 0, v.size()-1);
	PrintVec(v);
}
#endif // 0
