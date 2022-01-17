#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"

Board board;

using namespace std;

int main()
{
	//초기화
	uint64 lastTick = 0;
	board.Init(25);
	::srand(static_cast<unsigned int>(time(nullptr)));

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
		board.Render();

	}

}