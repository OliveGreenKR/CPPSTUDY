#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>

//#define List
//#define Matrix

using namespace std;

#define List

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
	//인접리스트
	adjacent = vector<vector<int>>(6);

	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };
#endif // 

#ifdef Matrix
	//인접행렬
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
	//자신의 발견자가 누구인지
	vector<int> parent(vertices.size(), -1);
	//시작점으로부터 거리
	vector<int> distance(vertices.size(), -1);

	queue<int> q;
	//시작점
	q.push(here);
	discovered[here] = true;
	parent[here] = here;
	distance[here] = 0;

	//반복
	while (q.empty() == false)
	{
		//발견(pop)
		here = q.front();
		q.pop();

		cout << "visited : " << here << endl;

		for (int there : adjacent[here])
		{
			if (discovered[there])
				continue;
			//방문(push)
			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}

}
void BfsAll()
{
	for(int i = 0 ; i < vertices.size(); i++)
	{
		if(discovered[i] == false)
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
