#if 0
#include <vector>
#include <iostream>
#include <map>
using namespace std;


/*
* 문제 : 삼각 경로
* (0,0)에서ㅏ 시작해서  아래 or 아래우측으로 이동가능
* 만나는 숫자는 모두 더한다.
* 더한 숫자가 최대가 되는 경로의 합은? 그렇다면 경로는?
* 
* 6
* 1 2
* 3 7 4
* 9 4 1 7
* 2 7 5 9 4
* 
*/


/*
* 풀이 알고리즘:
*  문제가 요구하는 특성을 가진 경로를 LP라고 한다면,
* 
* LP의 선택지 둘중 더 큰 LP를 가진 숫자를 택해 간다면 
* LP 경로가 만들어질것?
*/


vector<vector<int>> board=
{
	{6},
	{1,  2},
	{3,  7 ,  4},
	{9,  4 ,  1,  7},
	{2,  7 ,  5,  9,  4}
};

vector<vector<int>> cache;
vector<vector<int>> nextX;

int Path( int y=0, int x=0)
{
	//기저상황
	int N = board.size();
	if (x > N-1 || y > N-1)
		return 0;

	//캐시확인
	if (cache[y][x] != 0)
		return cache[y][x];

	//적용
	int sum = board[y][x];
	int nextRight = Path(y + 1, x);
	int nextRight2 = Path(y + 1, x + 1);

	if (nextRight > nextRight2)
	{
		sum += nextRight;
		nextX[y][x] = x;
	}
	else
	{
		sum += nextRight2;
		nextX[y][x] = x+1;
	}

	//sum = sum + max(Path(y + 1, x), Path(y + 1, x + 1));
	cache[y][x] = sum;

	return sum;
}

int main()
{
	int N = board.size();
	cache = vector<vector<int>>(N, vector<int>(N, 0));
	nextX = vector<vector<int>>(N, vector<int>(N));

	int ans = Path();
	
	int y = 0, x = 0;

	while (y < N)
	{
		cout << board[y][x] << " ->";
		
		x = nextX[y][x];
		y++;
	}
}

#endif // 1
