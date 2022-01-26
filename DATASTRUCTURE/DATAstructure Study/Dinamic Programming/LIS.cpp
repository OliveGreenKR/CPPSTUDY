#if 0
#include <vector>
#include <iostream>
using namespace std;

/*
** LIS (Longest Increasing Sequence) 의 길이를 구하라
Sequence : 수열

부분 수열 :  수열에서 일부 숫자를 지우고 남은 수열

순 증가 부분 수열 :  수가 증가하는 부분수열,



>> LIS  가장 긴 , 순 증가 부분 수열의 길이를 구하는 문제

if seq :  1 9 2 5 7

LIS :  1 2 5 7 , 즉 4의 길이를 가진다.
*/


vector<int> seq;
int cache[100];


/**
 * @brief 
 * 
 * 부분수열은 더 작은 부분수열의 합으로 구할 수 있음.
 * 부분수열이 시작되는 인덱스를 받고, 다음 인덱스의 부분수열을 받는다.
 * 반복하여 길이가 가장 큰 부분수열을 찾으면 됨.
 * 
 * @param v  수열
 * @param pos  부분 수열을 나눌 index
 * @return 증가 수열의 길이
*/
int LIS(vector<int>& seq, int pos)
{
//기저상황 (없을 수도 있음) 

//캐시 확인
	int& ret = cache[pos];
	if (ret != -1)
		return ret;

//LIS 구하기

	//최소 값 지정
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

int GetLIS(vector<int>& seq)
{
	int ret = 1;

	for (int pos = 0; pos < seq.size(); pos++)
	{
		ret = max(ret, LIS(seq, pos));
	}

	return ret;
}
int main()
{
	::memset(cache, -1,sizeof(cache));
	seq = vector<int>{ 1,9,2,5,7 };
	seq = vector<int>{ 7,1,2,5,7 };

	int ans = GetLIS(seq);
}

#endif // 1
