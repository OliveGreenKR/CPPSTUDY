#if 1
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

//��������_����
void MergeResult(vector<int>& v, int left, int mid, int right)
{
	//�� ���� ���ĵǾ��ִٰ� ����(������)


	int leftidx = left; //���� ��
	int rightidx = mid + 1; // ������ ��
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
	//���� �ϳ��� ���� ���� ����
	//������ ���� ������? �׷� ������ ������ ����
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

	//v�� ��ȿ������ �������� ������ �ܼ������ϸ� �ȵ�.
	for (int i = 0; i < tmp.size(); i++)
	{
		v[left + i] = tmp[i];
	}
}

//��������
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right) //������Ȳ : ���� ������
		return;

	//���� �� ���� 
	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	//�����ϴ� �Լ�
	MergeResult(v, left, mid, right);
}

//�������� N^2
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

//�������� N^2
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
//�������� N^2
void InsertSort(vector<int>& v)
{
	const int n = static_cast<int>(v.size());
	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];
		int j;
		for (j = i - 1; j >= 0; j--) //���ľȵ� �迭
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

//�� ����
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, ::greater<int>> pq;

	//N(�����Ͱ���) * logN(�켱���� ť ������ ����)
	for (int num : v)
	{
		pq.push(num);
	}

	v.clear();

	//N(�����Ͱ���) * logN(�켱���� ť)
	while (pq.empty()==false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
	//���� ���� ���⵵��
	// N log N
}

//�� ����
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
