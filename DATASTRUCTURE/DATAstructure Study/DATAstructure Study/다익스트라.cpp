#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>
#include <list>

using namespace std;

struct Vertex
{
	//data
};

vector<Vertex> vertecies;
vector<vector<int>> adjacent;  


void CreatGraph_4()
{
	vertecies.resize(6);;

	adjacent = vector<vector<int>>(6, vector<int>(6, -1));//가중치가 기록된 행렬
	
	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};
	//또는 pair로 관리해도 됨

	list<VertexCost> discovered; //발견 목록
	vector<int> best(vertecies.size(), INT32_MAX); //각 정점별로 지금까지 발견한 최소거리
	vector<int> parent(vertecies.size(), -1);
	//초기시작점
	discovered.push_back(VertexCost{here,0});
	best[here] = 0;
	parent[here] = here;

	while (discovered.empty() == false)
	{
		
		list<VertexCost>::iterator bestit;
		int bestCost = INT32_MAX;
		//제일 좋은 후보를 찾는다
		for (auto it = discovered.begin(); it != discovered.end(); ++it)
		{
			const int cost = it->cost;
			 //가중치를 비교하며 선택
			if (cost < bestCost)
			{
				bestCost = cost;
				bestit = it;
			}
		}

		int cost = bestit->cost;
		here = bestit->vertex;
		discovered.erase(bestit);
		
		//이미 더 짧은 경로가 있다면 스킵
		if (best[here] < cost)
			continue; 
		
		//간선 방문
		for (int there = 0; there < vertecies.size(); there++)
		{
			//연결되지 않으면
			if (adjacent[here][there] == -1)
				continue;

			//연결되어 있으므로 가중치 덧셈
			int nextCost = best[here] + adjacent[here][there];
			//이미 there로 가는 더 짧은 경로가 존재 -> 스킵
			if (nextCost >= best[there])
				continue;

			//여기까지 오면, 찾은 경로는 현재까지 중에 해당 정점을 향한 가장 빠른길이다.
			// ..>>기록
			discovered.push_back(VertexCost{ there,nextCost });
			best[there] = nextCost;
			parent[there] = here;
			
		}
	}
	
}



#if 1
int main()
{
	CreatGraph_4();
	Dijikstra(0);

}
#endif // 1
