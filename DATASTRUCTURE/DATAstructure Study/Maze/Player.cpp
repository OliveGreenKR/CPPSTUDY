#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>
void Player::RightHand()
{
	//목적지 도착 전에는 계속 실행
	Pos pos = _pos;
	Pos dest = _board->GetExitPos();

	_path.clear();
	_path.push_back(pos);

	while (pos != dest)
	{
		//1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는가?
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		Pos front[4] =
		{
			Pos{-1,0}, //UP
			Pos{0,-1}, //LEFT
			Pos{1,0}, //DOWN
			Pos{0,1} //RIGHTxc
		};

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
void Player::Init(Board* board)
{
	_pos = _board->GetEnterPos();
	_board = board;

	//경로계산
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
