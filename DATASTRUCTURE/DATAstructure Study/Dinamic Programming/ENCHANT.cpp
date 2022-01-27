#if 0
#include <vector>
#include <iostream>
#include <map>
using namespace std;

//ENCHANT : 
/*
* 문제상황 : 
* 
* 무기 강화 주문서를 통해 인챈트 가능 -> +1/+2/+3 중 랜덤으로 강화됨( 실패는 없음)
* 
* +num 아이템이 목표수치 (+N)으로 가는 경우의 수를 구하시오
*/



int N;
vector<int> cache; //cache[n] =  0 부터~ n강화까지  가능한 경우의 수
//1,2,3 =? 1,2,3 인데...

//현재 강화수치 num 일때 N까지의 경우의 수를 구하라
int Enchant(vector<int>& cache, int num)
{
	int enchant = N - num;

	//기저상황
	if (enchant < 0 || enchant > N)
		return 0;

	int& ret = cache[enchant];
	if (enchant == 0)
		return ret = 1;

	//캐시체크
	if (ret != 0)
		return ret;

	else
	{
		return ret = Enchant(cache, num + 1) + Enchant(cache, num + 2) + Enchant(cache, num + 3);
	}


}

int main()
{
	cache = vector<int>(50, 0);

	N = 20;

	int ans = Enchant(cache, 0);
	
	cout << ans << endl;

}
#endif // 1
