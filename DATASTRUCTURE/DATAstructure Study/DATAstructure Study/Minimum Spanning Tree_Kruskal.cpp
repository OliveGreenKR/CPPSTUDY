#if 0
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

//최소신장 트리 -> 그래프의 응용
//Kruskal : Greedy + Union-Find

class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
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

struct Vertex
{
	// int data
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;  //인접행렬

void CreateGraph()
{
	//정점 생성 및 인접행렬 기본값 초기화
	vertices.resize(6);
	adjacent = vector<vector<int>>(6,vector<int>(6,-1));

	adjacent[0][1]  = adjacent[1][0] = 15;
	adjacent[0][3]  = adjacent[3][0] = 35;
	adjacent[1][2]  = adjacent[2][1] = 5;
	adjacent[1][3]  = adjacent[3][1] = 10;
	adjacent[3][5]  = adjacent[5][3] = 10;
	adjacent[3][4]  = adjacent[4][3] = 5;
	adjacent[5][4]  = adjacent[4][5] = 5;
}

struct CostEdge
{
	int cost;
	int u;
	int v;
	//u->v 로 가는 cost

	bool operator<(CostEdge& other)
	{
		return cost < other.cost;
	}
};

//연결되어지는 얘들의 최종 코스트를 return 
int Kruskal(vector<CostEdge>& selected)
{
	int ret = 0;

	selected.clear();

	vector<CostEdge> edges;

	for (int u = 0; u < adjacent.size(); u++)
	{
		for (int v = 0; v < adjacent.size(); v++)
		{
			int cost = adjacent[u][v];
			//연결 안된 정점과, 중복 간선 피하기
			if (cost != -1 && u<v ) 
			{
				edges.push_back(CostEdge{ cost,u,v });
			}
		}
	}
	//cost가 작은 것부터 정리
	::sort(edges.begin(), edges.end());

	//같은 그룹 판별
	DisjointSet sets(vertices.size());

	for (CostEdge& edge : edges)
	{
		// 같은 그룹이면 스킵(사이클 방지)
		if (sets.Find(edge.u) == sets.Find(edge.v))
			continue;

		//타 그룹끼리 병합
		sets.Merge(edge.u , edge.v);
		selected.push_back(edge);
		ret += edge.cost;
	}

	return ret;
}


int main()
{
	CreateGraph();

	vector<CostEdge> selected;
	int cost = Kruskal(selected);
}

#endif // 1
