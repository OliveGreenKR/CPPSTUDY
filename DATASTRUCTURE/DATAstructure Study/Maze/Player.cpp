#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>
void Player::RightHand()
{
	//������ ���� ������ ��� ����
	Pos pos = _pos;
	Pos dest = _board->GetExitPos();

	_path.clear();
	_path.push_back(pos);

	while (pos != dest)
	{
		//1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ°�?
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
void Player::Init(Board* board)
{
	_pos = _board->GetEnterPos();
	_board = board;

	//��ΰ��
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
