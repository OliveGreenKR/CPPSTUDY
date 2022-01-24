#if 0
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>




// ���� + ��Ʋ�ξ�

// 1000�� (��  ���� id 0~999)
// ���� ����! -> 1��(����) + 2��  =  1����(����)
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

	// �� ���� �ý��� 

	// #1. ���� �ϳ��� �ٸ� ������ ����
	for (User& user : users)
	{
		if (user.teamid == 1)
			user.teamid = 2;
	}
	//>>�� ����� ã��� ������⵵�̳�, 
	//��ġ�� ������ ���⵵(N)�� ���� ����
	//�� �� ��ȣ��Ÿ�� ���� Disjoint set �� ����ϸ� ����

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
	//�ֻ��� �θ� ã��
	int Find(int u)
	{
		if ( u == _parent[u])
			return u;
		return Find(_parent[u]);
	}

	//u�� v�� �߽����� ��������.
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);
		if (u == v)
			return;
		//v ���� ������ u�� ��
		_parent[u] = v;

	}

private:
	vector<int> _parent;
};
//�̷��� ����� Ʈ���� ������ �������, Ʈ���� ���̰� ������ 
//������ �����ɸ��� �Ǵ� ������ �ִ�.

//>> Ʈ���� ������ ���������ִ� �ذ��?
//Ʈ���� ��ĥ ��, ���̰� ���� Ʈ���� ���̰� ���� Ʈ���� ������ ��ģ�ٸ�?
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


int main()
{
	
}
#endif // 1
