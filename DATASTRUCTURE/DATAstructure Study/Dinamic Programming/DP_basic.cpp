#if 0
#include <vector>
#include <iostream>
#include <Windows.h>
using namespace std;

//memoization �޸������̼�
int cache[50][50];

int Combination(int n, int r)
{
	//���� ���
	if (n == r || r == 0)
	{
		return 1;
	}

	//�̹� ���� ���� �� ������ �ٷ� ��ȯ
	int& ret = cache[n][r];

	if (ret != -1)
		return ret;

	//�ƴϸ� ���� ���� ���ؼ� ĳ�ÿ� ����.
	return ret = Combination(n - 1, r - 1) + Combination(n - 1, r);
}

int main()
{
	::memset(cache, -1, sizeof(cache)); //�ʱⰪ -1


	__int64 start = GetTickCount64();

	int lotto = Combination(45, 6); 

	__int64 end = GetTickCount64();

	cout << end - start << "ms"  << endl;
	//���Ϲ� ����Լ�  :  141ms

	//chache (DP ) :  0ms
}
#endif // 1
