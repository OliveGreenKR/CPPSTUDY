#if 0
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>




// 팀전 + 배틀로얄

// 1000명 (각  유저 id 0~999)
// 동맹 가능! -> 1번(대장) + 2번  =  1번팀(대장)
void TeamBattelRoyal()
{
	struct User
	{
		int teamid;
		//todo
	};

	//todo  : user manager
	vector<User> users;
	for (int i = 0; i < 1000; i++)
	{
		users.push_back(User{ i });
	}

	// 팀 동맹 시스템 

	// #1. 둘중 하나를 다른 팀으로 변경
	for (User& user : users)
	{
		if (user.teamid == 1)
			user.teamid = 2;
	}
	//>>이 방식은 찾기는 상수복잡도이나, 
	//합치기 연산의 복잡도(N)가 비교적 높음
	//이 때 상호배타적 집합 Disjoint set 을 사용하면 좋음

}

class NaiveDisjointSet
{
public:
	NaiveDisjointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}
	//최상위 부모 찾기
	int Find(int u)
	{
		if ( u == _parent[u])
			return u;
		return Find(_parent[u]);
	}

	//u가 v를 중심으로 합쳐진다.
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);
		if (u == v)
			return;
		//v 대장 밑으로 u가 들어감
		_parent[u] = v;

	}

private:
	vector<int> _parent;
};
//이러한 방식은 트리의 균형이 깨질경우, 트리의 높이가 높아져 
//연산이 오래걸리게 되는 문제가 있다.

//>> 트리의 균형을 유지시켜주는 해결법?
//트리를 합칠 때, 높이가 낮은 트리를 높이가 높은 트리의 밑으로 합친다면?
//--> Union by Rank
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n,1)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}
	//최상위 부모 찾기
	int Find(int u)
	{
		if (u == _parent[u])
			return u;
		return _parent[u] = Find(_parent[u]); 
		//최적화1 : 부하의 부하를 없애주고, 모든 대장아래에 부하가 동등해짐
		//>> 트리의 랭크가 감소.
	}

	// rank를 비교하며 합친다.
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);
		if (u == v)
			return;
		//최적화2. 트리의 높이가 높은쪽을 중심으로 합침
		if (_rank[u] > _rank[v])
		{
			::swap(u, v);
		}
		//위 의 코드로 인해 항상 v의 rank가 더 높다
		//>> v의 대장 밑으로 u가 들어감
		_parent[u] = v;

		//둘이 높이가 같은 트리였다면 높이+1
		if (_rank[u] == _rank[v])
			_rank[v]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};


int main()
{
	
}
#endif // 1
