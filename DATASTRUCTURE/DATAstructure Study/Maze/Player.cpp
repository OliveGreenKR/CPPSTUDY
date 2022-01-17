#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = _board->GetEnterPos();
	_board = board;

	//경로 계산

	//목적지 도착 전에는 계속 실행
	Pos pos = _pos;
	Pos dest = board->GetExitPos();

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
		
		if (CanGo(pos+front[newDir]))
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
	}
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
