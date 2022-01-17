#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"

Board board;

using namespace std;

int main()
{
	//�ʱ�ȭ
	uint64 lastTick = 0;
	board.Init(25);
	::srand(static_cast<unsigned int>(time(nullptr)));

	while(true)
	{
#pragma region �����Ӱ���
		//�ð�
		const uint64 currentTick =  ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		//�����������̶��?
		//if(deltaTick > 60) continue;
		lastTick = currentTick;
#pragma endregion 
		//�Է�

		//���� -> (�¶����̶�� �Ϻδ� ����)

		//������
		board.Render();

	}

}