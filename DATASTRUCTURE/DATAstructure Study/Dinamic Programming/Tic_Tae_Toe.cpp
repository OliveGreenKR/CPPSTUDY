#if 0
#include <vector>
#include <iostream>
#include <map>
#include<Windows.h>
using namespace std;

/*
* Tic_Tae_toe
* 
* 3���� ����.
* 
* [.][.][.]
* [.][.][.]
* [.][.][.]
* 
* ���� : �̷� ���� �ǿ��� ������ ����Ǵ� ���߿�
* �÷��̾ �̱� ����� �ִ��� ������ �Ǵ��ϴ� �Լ��� ������
* (�¸�, �й�, ���ºθ� �Ǻ��Ѵ�.)
* 
* >> �� �Լ��� �ִٸ� ƽ���� AI�� ���� �� �ְ� �ȴ�.
* 
* ** ĳ�� Ȱ���� ���?
* 
* �� ĭ�� o x '.' , 3���� ���°� ����
* �� ������ ������ ���� 3^9 = 19683 �� ����.
* 
* >> [0~2][3~8][9~26]
*	 .....
*	 .......   [~~19628]
* 
* > �̷��� ����
* 
* 
*/

vector<vector<char>> board;
int cache[19683];

enum
{
	DEFAULT =2,
	WIN =1,
	DRAW =0,
	LOSE =-1
};

int HashKey(const vector<vector<char>>& board)
{
	int ret = 0;

	//Hash
	//3����ó�� ��� ������ ���� �ϳ��� �迭�ȿ� ���� �� �ֵ���, Hashȭ!!
	for( int y = 0 ;  y < 3 ;  y++)
	{
		for (int x = 0; x < 3; x++)
		{
			ret = ret * 3; //ĭ �� �Ѿ

			if (board[y][x] == 'o')
				ret += 1;
			if (board[y][x] == 'x')
				ret += 2;
		}
	}

	return ret;
}

bool IsFinished(vector<vector<char>>& board, char turn)
{
	// �¿�
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
			return true;
	}

	// ����
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
			return true;
	}
	// �밢��
	if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
		return true;
	if (board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
		return true;

	return false;
}

int CanWin(vector<vector<char>>& board,char turn)
{
	//�������( ������� �¸����� ��� )
	if (IsFinished(board, 'x' + 'o' - turn))
		return LOSE;

	//ĳ��Ȯ��
	int key = HashKey(board);
	int& ret = cache[key]; //������ �޾Ƽ� ������ �ǰԲ� 
	if (ret != DEFAULT)
	{
		return ret;
	}

	//Ǯ��

	int minValue = DEFAULT;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			//������ �� ���� �κ� �н�
			if (board[y][x] != '.')
				continue;

			//���� ǥ���Ѵٸ�?(����)
			board[y][x] = turn;

			//Ȯ��
			minValue = min(minValue, CanWin(board, 'x' + 'o' - turn));
			// ������ �й��ϴ°��� ���� ���� ���̽�(LOSE = -1)
			//>> ���ڰ� �������� ������ ���� ���̽� (-1, 0)...

			//������ �״�� ����ϹǷ�, ������ �κ� ���
			board[y][x] = '.';
		}
	}

	if (minValue == DRAW || minValue == DEFAULT)
		 ret = DRAW;
	else 
	ret = -minValue;

	return ret;
}



int main()
{
	board = vector<vector<char>>
	{
		{'o', 'x', 'x'},
		{'.', 'o', '.'},
		{'o', '.', '.'}
	};
	//�̷��� �ϸ� �ȵ�
	/*::memset(cache, DEFAULT, sizeof(cache));*/
	//memset�� 1byte ����, �� char�� �޸𸮸� �б⶧��,(-1 ��  0  �� ��� ����Ʈ�� ���� ���� ��Ÿ���Ƿ� ����� ����.)

	for (int i = 0; i < 19683; i++)
	{
		cache[i] = DEFAULT;
	}

	int start = GetTickCount64();

	int win = CanWin(board, 'x');

	int end = GetTickCount64();

	cout << "Time  " << end - start << " ms" << endl;

	switch (win)
	{
	case WIN : 
		cout << "WIN" << endl;
		break;
	case LOSE:
		cout << "LOSE" << endl;
		break;
	case DRAW:
		cout << "DRAW" << endl;
		break;
	}

}
#endif
