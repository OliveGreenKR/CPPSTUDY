#include "pch.h"
#include "DisjointSet.h"


DisjointSet::DisjointSet(int n) : _parent(n), _rank(n, 1)
{
	for (int i = 0; i < n; i++)
	{
		_parent[i] = i;
	}
}
//�ֻ��� �θ� ã��
int DisjointSet::Find(int u)
{
	if (u == _parent[u])
		return u;
	return _parent[u] = Find(_parent[u]);
	//����ȭ1 : ������ ���ϸ� �����ְ�, ��� ����Ʒ��� ���ϰ� ��������
	//>> Ʈ���� ��ũ�� ����.
}

// rank�� ���ϸ� ��ģ��.
void DisjointSet::Merge(int u, int v)
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