#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>


void Player::RightHand()
{
	//������ ���� ������ ��� ����
	Pos pos = _pos;
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos{-1,0}, //UP
		Pos{0,-1}, //LEFT
		Pos{1,0}, //DOWN
		Pos{0,1} //RIGHTxc
	};

	_path.clear();
	_path.push_back(pos);

	while (pos != dest)
	{
		//1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ°�?
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
	
		if (CanGo(pos + front[newDir]))
		{
			//	>>������ �������� 90�� ȸ��
			_dir = newDir;
			//	>>������ �� �� ����.
			pos += front[_dir];

			_path.push_back(pos);
		}
		//2. ���� �ٶ󺸴� �������� ���� �� �� �ִ°�?
		else if (CanGo(pos + front[newDir]))
		{
			// >>������ �� �� ����
			pos += front[_dir];
			_path.push_back(pos);
		}
		else
		{
			//3. ���� �������� 90�� ȸ��
			_dir = (_dir + 1) % DIR_COUNT;
		}

		//-----------path ��� ��----------

		stack<Pos> s;
		for (int i = 0; i < _path.size() - 1; i++)
		{
			if (!s.empty() && s.top() == _path[i + 1])
			{
				s.pop();
			}
			else
				s.push(_path[i]);
		}

		//������ ��ǥ
		if (!_path.empty())
		{
			s.push(_path.back());
		}
		// �������� �ϴ� ���Ϳ� ����
		vector<Pos> path;
		while (!s.empty())
		{
			path.push_back(s.top());
			s.pop();
		}
		//���� reverse
		std::reverse(path.begin(), path.end());

		_path = path;
	}
}

void Player::Bfs()
{
	Pos pos = _pos;
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos{-1,0}, //UP
		Pos{0,-1}, //LEFT
		Pos{1,0}, //DOWN
		Pos{0,1} //RIGHT
	};
	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	//vector<vector<Pos>> parent;

	//parent[A]=B ==> A�� B�� ���� �߰���, �� B�� �θ�
	map<Pos, Pos> parent;

	queue<Pos> q;

	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while(q.empty() != true)
	{
		pos = q.front();
		q.pop();

		//�湮
		if (pos == dest) 
			break;

		for (int32 dir = 0; dir < 4;  dir++)
		{
			Pos nextPos = pos + front[dir];
			//�� �� �ִ� ��ġ����
			if (CanGo(nextPos) == false)
				continue;
			//�̹� �߰��� ��ġ����
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	_path.clear();
	//TODO:
	//�Ųٷ� �ö󰣴�.
	pos = dest;
	while (true)
	{
		_path.push_back(pos);

		//�������� �ڱ� �ڽ��� �θ��� Ư¡������
		if (parent[pos] == pos)
			break;
		pos = parent[pos];
	}
	//��� reverse
	std::reverse(_path.begin(), _path.end());
}

struct PQNode
{
	bool operator<(const PQNode& other) const
	{
		return f < other.f;
	}
	bool operator>(const PQNode& other) const
	{
		return f > other.f;
	}
	int32 f; // f= g+h
	int32 g;
	Pos pos;
};
void Player::AStar()
{
	//�� �ý���
	// F = G + H ���� ����� ��.
	//F = ��������, ���� ���� ����, ��ο� ���� �޶�����
	//	G =  ���������� �ش� ��ǥ���� �̵��ϴµ� �ɸ��� ���, ��ο� �ٶ� �޶���, �������� ����
	//	H =  ���������� �󸶳� �������, �������� ����, ��ο� ������ ������

	Pos start = _pos;
	Pos dest = _board->GetExitPos();

	enum 
	{
		DIR_COUNT = 4  //way
	};

	Pos front[] =
	{
		Pos{-1,0}, //UP
		Pos{0,-1}, //LEFT
		Pos{1,0}, //DOWN
		Pos{0,1}, //RIGHT
		Pos{-1,-1}, //up_left
		Pos{1,-1}, //down_left
		Pos{1,1}, //down_right
		Pos{-1,1}, //up_right

	};

	//�̵����
	int32 cost[] =
	{
		10, //up
		10, //left
		10,	//down
		10, //right
		14, //up left
		14, //down left
		14,	//up right
		14,	//down left
	};

	const int32 size = _board->GetSize();

	//ClosedList _ '�湮'�� ���(optional)- best�θ��ص� ��������
	//closed[y][x] = �� ��ǥ�� �湮�ߴ���
	/*vector<vector<bool>> closed(size, vector<bool>(size, false));*/
	
	//best[y][x] =  ���ݱ��� �ش� ��ǥ�� ���� �ּҺ��
	vector<vector<int32>>best(size, vector<int32>(size, INT32_MAX));

	//�θ� �����뵵
	map<Pos, Pos> parent;

	//OpenList - ����(�߰�)�ϴ� ���� �����ϴ� �ڷ�ý����� ���Ѵ�.
	priority_queue<PQNode, vector<PQNode>, ::greater<PQNode>> pq;

	//	1) ����(�߰�) �ý���  -> �ּҰ����� �̿��Ұ� -> �켱���� ť ���
	//	2) �ڴʰ� �� ���� ��ΰ� �߰ߵ� �� ���� -> ���� ó�� �ʼ�!

	{//�ʱⰪ����
		int32 g = 0;
		//������ ����ڰ� ���ϴ°�
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); 
		pq.push(PQNode{ g + h , g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}
	while (pq.empty() == false)
	{
		//best �ĺ�
		PQNode node = pq.top();
		pq.pop();

		// ������ ��ǥ�� ���� ��θ� ã�Ƽ�,
		// ������ ��η� ���ؼ� �̹� �湮���� ��� ��ŵ

		/*if (closed[node.pos.y][node.pos.x])
			continue;*/
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		//�湮
		/*closed[node.pos.y][node.pos.x] = true;*/

		//�������� �����ϸ� ����
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextpos = node.pos + front[dir];
			//���������� ���ɿ��� 
			if (CanGo(nextpos) == false)
				continue;

			//nextpos �� ��� ���
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextpos.y) + abs(dest.x - nextpos.x));

			//�̹� �ִ� ����� ���� ��
			if (best[nextpos.y][nextpos.x] <= g + h)
				continue;

			//��������
			best[nextpos.y][nextpos.x] = g + h; 
			pq.push(PQNode{ g + h, g, nextpos });
			parent[nextpos] = node.pos;
		}

		//�Ųٷ� �Ž��� �ö� ��η� �����.
		_path.clear();
		_pathindex = 0;

		start = dest;
		while (true)
		{
			_path.push_back(start);

			//�������� �ڱ� �ڽ��� �θ��� Ư¡������
			if (parent[start] == start)
				break;
			start = parent[start];
		}

		//��� reverse
		std::reverse(_path.begin(), _path.end());

	}
}

void Player::Init(Board* board)
{
	_pos = _board->GetEnterPos();
	_board = board;

	//��ΰ��
	//RightHand();
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	//�̵� ..
	if (_pathindex >= _path.size())
	{
		//_board->GenerateMap_Kruskal();
		_board->GenerateMap_Prim();
		Init(_board);
		return;
	}
	
	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
		_pos = _path[_pathindex];
		_pathindex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tiletype = _board->GetTileType(pos);
	return (tiletype == TileType::EMPTY);
}
