#if 0
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

//�ּҽ��� Ʈ�� -> �׷����� ����
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
	//�ֻ��� �θ� ã��
	int Find(int u)
	{
		if (u == _parent[u])
			return u;
		return _parent[u] = Find(_parent[u]);
		//����ȭ1 : ������ ���ϸ� �����ְ�, ��� ����Ʒ��� ���ϰ� ��������
		//>> Ʈ���� ��ũ�� ����.
	}

	// rank�� ���ϸ� ��ģ��.
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);
		if (u == v)
			return;
		//����ȭ2. Ʈ���� ���̰� �������� �߽����� ��ħ
		if (_rank[u] > _rank[v])
		{
			::swap(u, v);
		}
		//�� �� �ڵ�� ���� �׻� v�� rank�� �� ����
		//>> v�� ���� ������ u�� ��
		_parent[u] = v;

		//���� ���̰� ���� Ʈ�����ٸ� ����+1
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
vector<vector<int>> adjacent;  //�������

void CreateGraph()
{
	//���� ���� �� ������� �⺻�� �ʱ�ȭ
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
	//u->v �� ���� cost

	bool operator<(CostEdge& other)
	{
		return cost < other.cost;
	}
};

//����Ǿ����� ����� ���� �ڽ�Ʈ�� return 
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
			//���� �ȵ� ������, �ߺ� ���� ���ϱ�
			if (cost != -1 && u<v ) 
			{
				edges.push_back(CostEdge{ cost,u,v });
			}
		}
	}
	//cost�� ���� �ͺ��� ����
	::sort(edges.begin(), edges.end());

	//���� �׷� �Ǻ�
	DisjointSet sets(vertices.size());

	for (CostEdge& edge : edges)
	{
		// ���� �׷��̸� ��ŵ(����Ŭ ����)
		if (sets.Find(edge.u) == sets.Find(edge.v))
			continue;

		//Ÿ �׷쳢�� ����
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
