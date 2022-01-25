#include "pch.h"
#include "DisjointSet.h"


DisjointSet::DisjointSet(int n) : _parent(n), _rank(n, 1)
{
	for (int i = 0; i < n; i++)
	{
		_parent[i] = i;
	}
}
//최상위 부모 찾기
int DisjointSet::Find(int u)
{
	if (u == _parent[u])
		return u;
	return _parent[u] = Find(_parent[u]);
	//최적화1 : 부하의 부하를 없애주고, 모든 대장아래에 부하가 동등해짐
	//>> 트리의 랭크가 감소.
}

// rank를 비교하며 합친다.
void DisjointSet::Merge(int u, int v)
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