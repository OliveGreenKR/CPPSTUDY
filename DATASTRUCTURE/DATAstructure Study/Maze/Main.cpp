#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"

using namespace std;

int main()
{
	uint64 lastTick = 0;

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

		ConsoleHelper::SetCursorPosition(0,0);
		ConsoleHelper::SetConsoleCursor(false); //�����Ÿ��� Ŀ�� �Ⱥ���
		ConsoleHelper::SetCursorColor(ConsoleColor::RED);

		const char* TILE =  "��";
		for (int32 y = 0; y < 25; y++)
		{
			for (int32 x = 0; x < 25; x++)
			{
				cout << TILE;
			}
			cout << endl;
		}



	}

}