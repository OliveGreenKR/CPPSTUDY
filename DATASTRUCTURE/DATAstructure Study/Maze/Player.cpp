#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>


void Player::RightHand()
{
	//목적지 도착 전에는 계속 실행
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
		//1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는가?
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
	
		if (CanGo(pos + front[newDir]))
		{
			//	>>오른쪽 방향으로 90도 회전
			_dir = newDir;
			//	>>앞으로 한 보 전진.
			pos += front[_dir];

			_path.push_back(pos);
		}
		//2. 현재 바라보는 방향으로 전진 할 수 있는가?
		else if (CanGo(pos + front[newDir]))
		{
			// >>앞으로 한 보 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		else
		{
			//3. 왼쪽 방향으로 90도 회전
			_dir = (_dir + 1) % DIR_COUNT;
		}

		//-----------path 계산 끝----------

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

		//목적지 좌표
		if (!_path.empty())
		{
			s.push(_path.back());
		}
		// 역순서로 일단 벡터에 저장
		vector<Pos> path;
		while (!s.empty())
		{
			path.push_back(s.top());
			s.pop();
		}
		//순서 reverse
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

	//parent[A]=B ==> A는 B로 인해 발견함, 즉 B가 부모
	map<Pos, Pos> parent;

	queue<Pos> q;

	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while(q.empty() != true)
	{
		pos = q.front();
		q.pop();

		//방문
		if (pos == dest) 
			break;

		for (int32 dir = 0; dir < 4;  dir++)
		{
			Pos nextPos = pos + front[dir];
			//갈 수 있는 위치인지
			if (CanGo(nextPos) == false)
				continue;
			//이미 발견한 위치인지
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	_path.clear();
	//TODO:
	//거꾸로 올라간다.
	pos = dest;
	while (true)
	{
		_path.push_back(pos);

		//시작점은 자기 자신이 부모라는 특징이있음
		if (parent[pos] == pos)
			break;
		pos = parent[pos];
	}
	//경로 reverse
	std::reverse(_path.begin(), _path.end());
}

void Player::Init(Board* board)
{
	_pos = _board->GetEnterPos();
	_board = board;

	//경로계산
	//RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	//이동 ..
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
