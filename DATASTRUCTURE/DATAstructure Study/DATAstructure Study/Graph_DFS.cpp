#if 0
#include <iostream>
#include <vector>
#include <algorithm>

//#define List
#define Matrix

using namespace std;

struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<bool> visited;

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

//DFS
void Dfs(int here)
{
	//방문
	visited[here] = true;
	cout << here << "visited!" << endl;

#ifdef List

	//인접리스트 버전, 인접정점 순환
	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there = adjacent[here][i];
		if (visited[there] == false)
			Dfs(there);
}
#endif // List

#ifdef Matrix
	for (int there = 0; there < adjacent[here].size(); there++)
	{
		//아직 방문하지 않은 곳에 한하여 방문
		if ((adjacent[here][there] != 0) && visited[there] == false)
		{
			Dfs(there);
		}
	}
#endif // 

}
void DfsAll()
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < vertices.size(); i++)
	{
		if (visited[i] == false)
		{
			Dfs(i);
		}
	}
}

#if 0
int main()
{
	CreateGraph();

	DfsAll();
}
#endif // 1

#endif // 0
