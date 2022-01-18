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

	adjacent = vector<vector<int>>(6, vector<int>(6, -1));//����ġ�� ��ϵ� ���
	
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
	//�Ǵ� pair�� �����ص� ��

	list<VertexCost> discovered; //�߰� ���
	vector<int> best(vertecies.size(), INT32_MAX); //�� �������� ���ݱ��� �߰��� �ּҰŸ�
	vector<int> parent(vertecies.size(), -1);
	//�ʱ������
	discovered.push_back(VertexCost{here,0});
	best[here] = 0;
	parent[here] = here;

	while (discovered.empty() == false)
	{
		
		list<VertexCost>::iterator bestit;
		int bestCost = INT32_MAX;
		//���� ���� �ĺ��� ã�´�
		for (auto it = discovered.begin(); it != discovered.end(); ++it)
		{
			const int cost = it->cost;
			 //����ġ�� ���ϸ� ����
			if (cost < bestCost)
			{
				bestCost = cost;
				bestit = it;
			}
		}

		int cost = bestit->cost;
		here = bestit->vertex;
		discovered.erase(bestit);
		
		//�̹� �� ª�� ��ΰ� �ִٸ� ��ŵ
		if (best[here] < cost)
			continue; 
		
		//���� �湮
		for (int there = 0; there < vertecies.size(); there++)
		{
			//������� ������
			if (adjacent[here][there] == -1)
				continue;

			//����Ǿ� �����Ƿ� ����ġ ����
			int nextCost = best[here] + adjacent[here][there];
			//�̹� there�� ���� �� ª�� ��ΰ� ���� -> ��ŵ
			if (nextCost >= best[there])
				continue;

			//������� ����, ã�� ��δ� ������� �߿� �ش� ������ ���� ���� �������̴�.
			// ..>>���
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
