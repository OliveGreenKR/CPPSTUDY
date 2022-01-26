#if 0
#include <vector>
#include <iostream>
#include <map>
using namespace std;


/*
* ���� : �ﰢ ���
* (0,0)������ �����ؼ�  �Ʒ� or �Ʒ��������� �̵�����
* ������ ���ڴ� ��� ���Ѵ�.
* ���� ���ڰ� �ִ밡 �Ǵ� ����� ����? �׷��ٸ� ��δ�?
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
vector<vector<int>> nextX;

int Path( int y=0, int x=0)
{
	//������Ȳ
	int N = board.size();
	if (x > N-1 || y > N-1)
		return 0;

	//ĳ��Ȯ��
	if (cache[y][x] != 0)
		return cache[y][x];

	//����
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
