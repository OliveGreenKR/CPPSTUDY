#if 1
#include <vector>
#include <iostream>
#include <Windows.h>
using namespace std;

/*
** LIS (Longest Increasing Sequence) �� ���̸� ���϶�
Sequence : ����

�κ� ���� :  �������� �Ϻ� ���ڸ� ����� ���� ����

�� ���� �κ� ���� :  ���� �����ϴ� �κм���,



>> LIS  ���� �� , �� ���� �κ� ������ ���̸� ���ϴ� ����

if seq :  1 9 2 5 7

LIS :  1 2 5 7 , �� 4�� ���̸� ������.
*/


vector<int> seq;
int cache[100];


/**
 * @brief 
 * 
 * �κм����� �� ���� �κм����� ������ ���� �� ����.
 * �κм����� ���۵Ǵ� �ε����� �ް�, ���� �ε����� �κм����� �޴´�.
 * �ݺ��Ͽ� ���̰� ���� ū �κм����� ã���� ��.
 * 
 * @param v  ����
 * @param pos  �κ� ������ ���� index
 * @return ���� ������ ����
*/
int LIS(vector<int>& seq, int pos)
{
//������Ȳ (���� ���� ����) 

//ĳ�� Ȯ��
	int& ret = cache[pos];
	if (ret != -1)
		return ret;

//LIS ���ϱ�

	//�ּ� �� ����
	ret = 1;
	//int max = 0;

	for (int next = pos + 1; next < seq.size(); next++)
	{
		
		if (seq[pos] >= seq[next])
			continue;
		/*if (LIS(seq, next) > max)
			max = LIS(seq, next);*/
		ret = max(ret, 1 + LIS(seq,next));
	}
	//ret += max;
	cache[pos] = ret;

	return ret;
}

int main()
{
	::memset(cache, -1,sizeof(cache));
	seq = vector<int>{ 1,9,2,5,7 };

	int ans = LIS(seq, 0);
}

#endif // 1
