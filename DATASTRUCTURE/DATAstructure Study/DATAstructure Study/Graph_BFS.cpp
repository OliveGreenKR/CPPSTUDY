#if 0
#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>

//#define List
//#define Matrix

using namespace std;

//#define List
#define Matrix

struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);

#ifdef List
	//��������Ʈ
	adjacent = vector<vector<int>>(6);

	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };
#endif // 

#ifdef Matrix
	//�������
	adjacent = vector<vector<int>>(6, vector<int>(6, 0));
	adjacent[0][1] = 1;
	adjacent[0][3] = 1;
	adjacent[1][0] = 1;
	adjacent[1][2] = 1;
	adjacent[1][3] = 1;
	adjacent[3][4] = 1;
	adjacent[5][4] = 1;
#endif // Matrix

}

void Bfs(int here)
{
	//�ڽ��� �߰��ڰ� ��������
	vector<int> parent(vertices.size(), -1);
	//���������κ��� �Ÿ�
	vector<int> distance(vertices.size(), -1);

	queue<int> q;
	//������
	q.push(here);
	discovered[here] = true;
	parent[here] = here;
	distance[here] = 0;
#ifdef List

	//�ݺ�
	while (q.empty() == false)
	{
		//�߰�(pop)
		here = q.front();
		q.pop();

		cout << "visited : " << here << endl;

		for (int there : adjacent[here])
		{
			if (discovered[there])
				continue;
			//�湮(push)
			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
}
#endif // List

#ifdef Matrix
	//�ݺ�
	while (q.empty() == false)
	{
		//�߰�(pop)
		here = q.front();
		q.pop();

		cout << "visited : " << here << endl;

		//����� ��� ������谡 ǥ���Ǿ������Ƿ� ���ȯ
		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == 0)
				continue;
			if (discovered[there])
				continue;
			//�湮(push)
			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}

#endif // Matrix

}
void BfsAll()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (discovered[i] == false)
			Bfs(i);
	}
}

#if 1
int main()
{
	discovered = vector<bool>(6, false);
	CreateGraph();

	Bfs(0);
	/*BfsAll();*/
}
#endif // 1

#endif // 0
