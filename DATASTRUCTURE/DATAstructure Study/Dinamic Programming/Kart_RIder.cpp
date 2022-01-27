#if 0

#include <vector>
#include <iostream>
#include<algorithm>
#include<queue>

using namespace std;

/*
 * 문제상황
 * 카트는 게임이 시작하면 달리기 시작, T초 동안 달린다.
 * 처음 이동속도, 기본 이동속도는 1m/s
 * 
 * 게임이 시작되고 특정 시간(a)가 되면, 바닥에 신발 아이템이 생성된다.
 * 카트는 신발을 신거나, 지나칠 수 있다. 지나간 신발은 영영 다시 주울 수 없다.
 * 
 * 신발을 착용하려면, (b)의 시간이 필요하다. 즉  b초 동안 제자리에서 멈추어야 움직일 수 있다.
 * 
 * 신발을 착용하면 일정시간(C) 동안 신발 속도(d)로 달릴 수 있다.
 * 신발은 하나만 착용할 수 있고, 가장 최근 착용한 신발의 속도만 적용된다.
 * 신발을 벗거나 다른 신발로 바꿔 장착할 때 추가시간이 들지 않는다. (새로운 신발을 신는 시간만 소요 된다.)
 * 
 * 신발 효과가 끝나면, 다시 기본 이동속도 1m/s로 달린다.
 * 
 * 신발을 신는동안 다른 신발을 신을 수는 없음.
 * 
 * Q) 생성되는 모든 신발 정보가 주어졌을 때, T초동안 갈 수 있는 최대 거리를 구하라.
 */


/*input.txt
 * T : 20
 * 신발개수 : 4
 *          a b  c d
 * 신발1 :	3 4 10 3
 * 신발2 :	4 1 4 2
 * 신발3 :	10 2 5 5 
 * 신발4 :	15 1 3 7
 */



//문제해결 생각해보기
/*
#2. 신발 아이템
(a,b,c,d) 4가지 속성을 가지고 있어야함

#3. 이동거리 경우의 수를 따져서 기록하고, 최대 거리의 기록을 찾아야함.


*/

struct Shoe
{
	Shoe(int a, int b, int c, int d)
	{
		time = a;
		start = a + b;
		end = a + b + c;
		speed = d;
	}
	int time; // 생성되는 시간
	int start;// 신발 효과 시작시간
	int end; // 신발 효과 끝 시간
	int speed; // 속도
};

vector<Shoe> shoes; //신발아이템 집합

int T; //총 이동시간.

vector<int>cache; //cahce[time]은 time에서 가장 최대 이동거리

//now번 신발을 신고 갈 수 있는 최대 거리를 반환.!!
//즉, 신발을 "신기 전" 과는 상관없음!
int Solve(int now)
{
//기저조건
	if (now >= shoes.size())
		return 0;

//캐시확인
	int& ret = cache[now];

	if (ret != -1)
		return ret;

//계산
	Shoe& shoe = shoes[now];

	//신발신고 이동한 거리 + 걸어서 이동한 거리
	int dist = (shoe.end - shoe.start) * shoe.speed + (T - shoe.end) * 1;
	ret = max(ret,dist);

	//다른 신발을 신을수도, 안 신을 수도 있음.
	for (int next = now + 1; next < shoes.size(); next++)
	{
		Shoe& nextshoe = shoes[next];
		if (nextshoe.time < shoe.start)//신는도중에 등장하는 신발이면 신을 수 없음
			continue;

		//다음 신발까지의 이동한 거리
		int moveDist = 0;

		//현재 신발 효과가 끝나기 전에 다음 신발 스폰
		if (nextshoe.time <= shoe.end)
		{
			moveDist = (nextshoe.time - shoe.start) * shoe.speed;
		}
		else
		{
			moveDist = (shoe.end - shoe.start) * shoe.speed + (nextshoe.time - shoe.end) * 1;
		}
		ret = max(ret, moveDist + Solve(next));
	}
	return ret;
}

int main()
{
	T = 20;

	//shoe push back'
	shoes.push_back(Shoe{ 0,0,T,1 });
	shoes.push_back(Shoe{ 3,4,10,3 });
	shoes.push_back(Shoe{ 4,1,4,2 });
	shoes.push_back(Shoe{ 10,2,5,5 });
	shoes.push_back(Shoe{ 15,1,3,7 });

	//shoe 벡터 start시간이 작은 순으로 정렬
	::sort(shoes.begin(), shoes.end(), [=](Shoe& shoe1, Shoe& shoe2) {return shoe1.time < shoe2.time ; });
	cache = vector<int>(shoes.size(), -1);

	int answer = Solve(0);

	cout << answer << endl;
}


#endif // 1
