#if 0
#include <vector>
#include <iostream>
#include <map>
#include<Windows.h>
using namespace std;

/*
* Tic_Tae_toe
* 
* 3목같은 게임.
* 
* [.][.][.]
* [.][.][.]
* [.][.][.]
* 
* 문제 : 이런 보드 판에서 게임이 진행되던 와중에
* 플레이어가 이길 방법이 있는지 없는지 판단하는 함수를 만들어보자
* (승리, 패배, 무승부를 판별한다.)
* 
* >> 이 함수가 있다면 틱택토 AI를 만들 수 있게 된다.
* 
* ** 캐시 활용을 어떻게?
* 
* 한 칸당 o x '.' , 3가지 상태가 가능
* 총 가능한 가지의 수는 3^9 = 19683 이 가능.
* 
* >> [0~2][3~8][9~26]
*	 .....
*	 .......   [~~19628]
* 
* > 이렇게 동작
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
	//3진법처럼 모든 가지의 수를 하나의 배열안에 놓을 수 있도록, Hash화!!
	for( int y = 0 ;  y < 3 ;  y++)
	{
		for (int x = 0; x < 3; x++)
		{
			ret = ret * 3; //칸 이 넘어감

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
	// 좌우
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
			return true;
	}

	// 상하
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
			return true;
	}
	// 대각선
	if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
		return true;
	if (board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
		return true;

	return false;
}

int CanWin(vector<vector<char>>& board,char turn)
{
	//기저사례( 상대편이 승리했을 경우 )
	if (IsFinished(board, 'x' + 'o' - turn))
		return LOSE;

	//캐시확인
	int key = HashKey(board);
	int& ret = cache[key]; //참조로 받아서 저장이 되게끔 
	if (ret != DEFAULT)
	{
		return ret;
	}

	//풀기

	int minValue = DEFAULT;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			//차지할 수 없는 부분 패스
			if (board[y][x] != '.')
				continue;

			//여기 표시한다면?(착수)
			board[y][x] = turn;

			//확인
			minValue = min(minValue, CanWin(board, 'x' + 'o' - turn));
			// 상대방이 패배하는것이 제일 좋은 케이스(LOSE = -1)
			//>> 숫자가 작을수록 나한테 좋은 케이스 (-1, 0)...

			//원본을 그대로 사용하므로, 착수한 부분 취소
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
	//이렇게 하면 안됨
	/*::memset(cache, DEFAULT, sizeof(cache));*/
	//memset은 1byte 단위, 즉 char로 메모리를 밀기때문,(-1 과  0  은 모든 바이트가 같은 수를 나타내므로 상관이 없다.)

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
