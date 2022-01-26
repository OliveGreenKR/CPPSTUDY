#if 1
#include <vector>
#include <iostream>
#include <map>
using namespace std;


/*
* ���� : �ﰢ ���
* (0,0)������ �����ؼ�  �Ʒ� or �Ʒ��������� �̵�����
* ������ ���ڴ� ��� ���Ѵ�.
* ���� ���ڰ� �ִ밡 �Ǵ� ����� ����?
* 
* 6
* 1 2
* 3 7 4
* 9 4 1 7
* 2 7 5 9 4
* 
*/


/*
* Ǯ�� �˰���:
*  ������ �䱸�ϴ� Ư���� ���� ��θ� LP��� �Ѵٸ�,
* 
* LP�� ������ ���� �� ū LP�� ���� ���ڸ� ���� ���ٸ� 
* LP ��ΰ� ���������?
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
