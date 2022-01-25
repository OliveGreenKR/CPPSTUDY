#include "pch.h"
#include "Board.h"
#include "Player.h"
#include "DisjointSet.h"

const char* TILE = "■";

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size , Player* player)
{
	_size = size;
	_player = player;

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
//#2. kruskal 미로생성 알고리즘
//격자무늬 상태에서, 가중치가 랜덤인 간선을 생성하고, 이를 이어서 경로를 만듦.
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

	vector<CostEdge> edges;

	// edges 후보를 랜덤 cost로 등록한다.
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			//우측연결 간선 후보
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue,Pos{y,x}, Pos{y,x + 2} });
			}

			//아래로 연결하는 간선 후보
			if (y < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue,Pos{y,x}, Pos{y+2,x} });
			}

		}
	}

	//간선 후보군 완성 -> Kruskal로  최소 스패닝 트리 완성

	//#1. 일정 순서로 Sort(default : 작은 순서)
	::sort(edges.begin(), edges.end());
	//#2. DisjointSet (상호배타적 집합)을 이용하여 각 트리를 합친다.
	//(DisJointSet -> 트리의 높이가 최소화하도록 합침)

	DisjointSet sets(_size * _size);
	for (CostEdge& edge : edges)
	{
		int  u = edge.u.y * _size + edge.u.x;
		int v = edge.v.y * _size + edge.v.x;
		
		//같은 그룹이면 스킵!!
		if (sets.Find(u) == sets.Find(v))
			continue;
		//합침
		sets.Merge(u, v);

		//적용
		//[u][wall][v]인 형태 에서 연결된 wall을 뚫어주어야함
		int y = (edge.u.y + edge.v.y) / 2;
		int x = (edge.u.x + edge.v.x) / 2;
		_tile[y][x] = TileType::EMPTY;
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
	if (GetExitPos() == pos )
	{
		return ConsoleColor::BLUE;
	}
	if (_player && _player->GetPos() == pos)
		return ConsoleColor::YELLOW;

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
