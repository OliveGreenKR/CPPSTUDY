#include "pch.h"
#include "Board.h"

const char* TILE = "��";

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
	ConsoleHelper::SetConsoleCursor(false); //�����Ÿ��� Ŀ�� �Ⱥ���
	
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
//#1. Binary Tree �̷� ���� �˰���
//���ڹ��� ���¿���, ���� �߾ӿ��� �������� ����, Ȥ�� �Ʒ����� �վ���

void Board::GenerateMap()
{
	//���ڹ��̿ϼ�
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

	//�������� ���۶Ծ���
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;
			//������ ������
			if(y == _size - 2 && x == _size - 2)
			{
				_tile[y][x + 1] = TileType::WALL;
				continue;
			}
			//�ֿܰ��� 
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
			//�������� �� ����
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
