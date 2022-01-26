#if 1
#include <vector>
#include <iostream>
#include <map>
using namespace std;


/*
* 문제 : 삼각 경로
* (0,0)에서ㅏ 시작해서  아래 or 아래우측으로 이동가능
* 만나는 숫자는 모두 더한다.
* 더한 숫자가 최대가 되는 경로의 합은?
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

int Path( int y, int x)
{
	int N = board.size();
	if (x > N-1 || y > N-1)
		return 0;

	if (cache[y][x] != 0)
		return cache[y][x];

	int sum = board[y][x];
	sum = sum + max(Path(y + 1, x), Path(y + 1, x + 1));
	cache[y][x] = sum;

	return sum;
}

int main()
{
	int N = board.size();
	cache = vector<vector<int>>(N, vector<int>(N, 0));

	int ans = Path(0, 0);
}

#endif // 1
