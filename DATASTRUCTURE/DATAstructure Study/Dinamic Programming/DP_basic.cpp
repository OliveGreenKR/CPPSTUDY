#if 0
#include <vector>
#include <iostream>
#include <Windows.h>
using namespace std;

//memoization 메모이제이션
int cache[50][50];

int Combination(int n, int r)
{
	//기저 사례
	if (n == r || r == 0)
	{
		return 1;
	}

	//이미 답을 구한 적 있으면 바로 반환
	int& ret = cache[n][r];

	if (ret != -1)
		return ret;

	//아니면 새로 답을 구해서 캐시에 저장.
	return ret = Combination(n - 1, r - 1) + Combination(n - 1, r);
}

int main()
{
	::memset(cache, -1, sizeof(cache)); //초기값 -1


	__int64 start = GetTickCount64();

	int lotto = Combination(45, 6); 

	__int64 end = GetTickCount64();

	cout << end - start << "ms"  << endl;
	//ㅇ일반 재귀함수  :  141ms

	//chache (DP ) :  0ms
}
#endif // 1
