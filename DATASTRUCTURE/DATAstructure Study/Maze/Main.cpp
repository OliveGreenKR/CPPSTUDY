#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"

using namespace std;

int main()
{
	uint64 lastTick = 0;

	while(true)
	{
#pragma region 프레임관리
		//시간
		const uint64 currentTick =  ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		//고정프레임이라면?
		//if(deltaTick > 60) continue;
		lastTick = currentTick;
#pragma endregion 

		//입력

		//로직 -> (온라인이라면 일부는 서버)

		//렌더링

		ConsoleHelper::SetCursorPosition(0,0);
		ConsoleHelper::SetConsoleCursor(false); //깜빡거리는 커서 안보임
		ConsoleHelper::SetCursorColor(ConsoleColor::RED);

		const char* TILE =  "■";
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