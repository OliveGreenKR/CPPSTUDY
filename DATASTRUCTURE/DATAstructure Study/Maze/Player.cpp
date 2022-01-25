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
	//평가 시스템
	// F = G + H 공식 사용할 것.
	//F = 최종점수, 작을 수록 좋다, 경로에 따라 달라질것
	//	G =  시작점에서 해당 좌표까지 이동하는데 걸리는 비용, 경로에 다라 달라짐, 작을수록 좋음
	//	H =  목적지에서 얼마나 가까운지, 작을수록 좋다, 경로와 무관한 고정값

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

	//이동비용
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

	//ClosedList _ '방문'한 목록(optional)- best로만해도 구현가능
	//closed[y][x] = 이 좌표에 방문했는지
	/*vector<vector<bool>> closed(size, vector<bool>(size, false));*/
	
	//best[y][x] =  지금까지 해당 좌표에 대한 최소비용
	vector<vector<int32>>best(size, vector<int32>(size, INT32_MAX));

	//부모 추적용도
	map<Pos, Pos> parent;

	//OpenList - 예약(발견)하는 것을 관리하는 자료시스템을 말한다.
	priority_queue<PQNode, vector<PQNode>, ::greater<PQNode>> pq;

	//	1) 예약(발견) 시스템  -> 최소값만을 이용할것 -> 우선순위 큐 사용
	//	2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수!

	{//초기값설정
		int32 g = 0;
		//공식은 사용자가 정하는것
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); 
		pq.push(PQNode{ g + h , g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}
	while (pq.empty() == false)
	{
		//best 후보
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로를 찾아서,
		// 더빠른 경로로 인해서 이미 방문했을 경우 스킵

		/*if (closed[node.pos.y][node.pos.x])
			continue;*/
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		//방문
		/*closed[node.pos.y][node.pos.x] = true;*/

		//목적지에 도착하면 종료
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextpos = node.pos + front[dir];
			//다음지역의 가능여부 
			if (CanGo(nextpos) == false)
				continue;

			//nextpos 의 비용 계산
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextpos.y) + abs(dest.x - nextpos.x));

			//이미 있는 경로의 비용과 비교
			if (best[nextpos.y][nextpos.x] <= g + h)
				continue;

			//예약진행
			best[nextpos.y][nextpos.x] = g + h; 
			pq.push(PQNode{ g + h, g, nextpos });
			parent[nextpos] = node.pos;
		}

		//거꾸로 거슬러 올라가 경로로 만든다.
		_path.clear();
		_pathindex = 0;

		start = dest;
		while (true)
		{
			_path.push_back(start);

			//시작점은 자기 자신이 부모라는 특징이있음
			if (parent[start] == start)
				break;
			start = parent[start];
		}

		//경로 reverse
		std::reverse(_path.begin(), _path.end());

	}
}

void Player::Init(Board* board)
{
	_pos = _board->GetEnterPos();
	_board = board;

	//경로계산
	//RightHand();
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	//이동 ..
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
