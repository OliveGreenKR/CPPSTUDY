#include "pch.h"
#include "Board.h"
#include "Player.h"
#include "DisjointSet.h"

const char* TILE = "��";

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

	//GenerateMap_Kruskal();
	GenerateMap_Prim();
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
//#2. kruskal �̷λ��� �˰���
//���ڹ��� ���¿���, ����ġ�� ������ ������ �����ϰ�, �̸� �̾ ��θ� ����.
void Board::GenerateMap_Kruskal()
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

	struct CostEdge
	{
		int cost;
		Pos u;
		Pos v;

		bool operator<(const CostEdge& other)
		{
			return cost < other.cost;
		}
	};

	vector<CostEdge> edges;

	// edges �ĺ��� ���� cost�� ����Ѵ�.
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			//�������� ���� �ĺ�
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue,Pos{y,x}, Pos{y,x + 2} });
			}

			//�Ʒ��� �����ϴ� ���� �ĺ�
			if (y < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue,Pos{y,x}, Pos{y+2,x} });
			}

		}
	}

	//���� �ĺ��� �ϼ� -> Kruskal��  �ּ� ���д� Ʈ�� �ϼ�

	//#1. ���� ������ Sort(default : ���� ����)
	::sort(edges.begin(), edges.end());
	//#2. DisjointSet (��ȣ��Ÿ�� ����)�� �̿��Ͽ� �� Ʈ���� ��ģ��.
	//(DisJointSet -> Ʈ���� ���̰� �ּ�ȭ�ϵ��� ��ħ)

	DisjointSet sets(_size * _size);
	for (CostEdge& edge : edges)
	{
		int  u = edge.u.y * _size + edge.u.x;
		int v = edge.v.y * _size + edge.v.x;
		
		//���� �׷��̸� ��ŵ!!
		if (sets.Find(u) == sets.Find(v))
			continue;
		//��ħ
		sets.Merge(u, v);

		//����
		//[u][wall][v]�� ���� ���� ����� wall�� �վ��־����
		int y = (edge.u.y + edge.v.y) / 2;
		int x = (edge.u.x + edge.v.x) / 2;
		_tile[y][x] = TileType::EMPTY;
	}

}

void Board::GenerateMap_Prim()
{
	//���ڹ��̿ϼ�
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	struct CostEdge
	{
		int cost;
		Pos vtx;

		//�켱����ť�� ����ϱ����� const�Լ��� �������
		bool operator<(const CostEdge& other) const 
		{
			return cost < other.cost;
		}
	};

	//Ư�� ������ ����� ������ �������� �� �ʿ䰡 ����
	//edges[u] :  u ������ ����� ������ ����
	map<Pos, vector<CostEdge>> edges;

	//edges �ĺ��� �������� ����Ѵ�.
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			Pos u = Pos{ y,x };
			//�������� ���� �ĺ�
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				Pos v = Pos{ y,x + 2 };
				edges[u].push_back(CostEdge{ randValue,v });
				edges[v].push_back(CostEdge{ randValue,u });
			}

			//�Ʒ��� �����ϴ� ���� �ĺ�
			if (y < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				Pos v = Pos{ y+2,x };
				edges[u].push_back(CostEdge{ randValue,v });
				edges[v].push_back(CostEdge{ randValue,u });
			}
		}
	}

	//�����ĺ��� ����
	//PRIM �˰������� ���� ����

	//������ Ʈ�� ���Կ��� Ȯ��
	map<Pos, bool> added;
	//� ������ ������ ���� ����Ǿ��ֳ�
	map<Pos, Pos> parent;
	//����� �ִ� Ʈ���� ������ ���� ��, �ش� ������ ��� �ּ� ������ ����
	map<Pos, int32> best;

	//���ͽ�Ʈ��� ���� ����, �׷��� 
	//���ͽ�Ʈ�� :  best�� [������]����������  cost
	//PRIM : best�� [���� Ʈ��]�� �������� �� cost


	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			best[Pos{y,x}] = INT32_MAX;
			added[Pos{ y,x }] = false;
		}
	}

	priority_queue<CostEdge> pq;

	const Pos startPos = Pos{ 1,1 };  //�������� ���ص� ��(���� �ƴ� ��)
	
	pq.push(CostEdge{ 0,startPos });
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (pq.empty() == false)
	{
		CostEdge bestEdge = pq.top();
		pq.pop();

		//���� ����� ���� 
		Pos v = bestEdge.vtx;
		//�̹� �߰���� ��ŵ
		if (added[v] == true)
			continue;
		added[v] = true;

		//�ʿ� ����
		{
			int y = (parent[v].y + v.y) / 2;
			int x = (parent[v].x + v.x) / 2;
			_tile[y][x] = TileType::EMPTY;
		}

		//��� �߰��� ������ ������ �������� �˻�...
		for (CostEdge& edge : edges[v])
		{
			//�̹� �߰��Ǿ����� ��ŵ
			if (added[edge.vtx] == true)
				continue;

			//������ ��ΰ� �� ������ ��ŵ
			if (edge.cost > best[edge.vtx])
				continue;

			best[edge.vtx] = edge.cost;
			parent[edge.vtx] = v;
			pq.push(edge);
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
