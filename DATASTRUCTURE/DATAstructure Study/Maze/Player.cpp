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
		DIR_COUNT = 4
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
		return;

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
