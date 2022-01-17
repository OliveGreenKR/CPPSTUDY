#include "pch.h"
#include "Board.h"

const char* TILE = "■";

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size)
{
	_size = size;

	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::SetConsoleCursor(false); //깜빡거리는 커서 안보임
	
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			ConsoleColor color = GetTileColor(Pos{ y,x });
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}
		cout << endl;
	}
}
//#1. Binary Tree 미로 생성 알고리즘
//격자무늬 상태에서, 격자 중앙에서 랜덤으로 우측, 혹은 아래측을 뚫어줌

void Board::GenerateMap()
{
	//격자무늬완성
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x%2 ==0 || y%2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	//랜덤으로 구멍뚤어줌
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;
			//마지막 꼭짓점
			if(y == _size - 2 && x == _size - 2)
			{
				_tile[y][x + 1] = TileType::WALL;
				continue;
			}
			//최외각벽 
			if (y == _size - 2)
			{
				_tile[y][x+1] = TileType::EMPTY;
				continue;
			}
			if (x == _size - 2)
			{
				_tile[y+1][x] = TileType::EMPTY;
				continue;
			}
			//랜덤으로 길 생성
			const int32 randValue = ::rand() % 2;
			if (randValue == 0)
			{
				_tile[y][x + 1] = TileType::EMPTY;
			}
			else
			{
				_tile[y+1][x] = TileType::EMPTY;
			}
		}
	}

}

TileType Board::GetTileType(Pos pos)
{
	if (pos.x < 0 || pos.x >= _size||
		pos.y < 0 || pos.y >= _size)
	{
		return TileType::NONE;
	}

	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	TileType tiletype = GetTileType(pos);

	switch (tiletype)
	{
	case TileType::EMPTY:
		return ConsoleColor::GREEN;
	case TileType::WALL:
		return ConsoleColor::RED;
	}

	return ConsoleColor::WHITE;
}
