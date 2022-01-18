#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//�׷���:
//�������� ���հ� �׵��� ���踦 �̾��־����.
//�������� ���� -> ����<����>
//
//������ ������ �����Ϳ� ����� �������� ������
//�� �������� ����

void CreateGraph_1()
{

	struct Vertex
	{
		vector<Vertex*> edges;
		//int data;
	};
	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// 0-> 3 check
	bool connected = false;
	
	for (Vertex* edge :  v[0].edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}
}


void CreateGraph_2()
{

	struct Vertex
	{
		//int data;
	};

	vector<Vertex> v;
	v.resize(6);

	//������ ���� ����
	//adjacent[n] ==> n�� ������ ����� �������� ���;
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };
	
	// 0-> 3 check
	bool connected = false;

	for (int vertex : adjacent[0])
	{
		if (vertex == 3)
		{
			connected = true;
			break;
		}
	}
	// std
	vector<int> adj = adjacent[0];
	bool connected2 = std::find(adj.begin(), adj.end(), 3) != adj.end();

}

void CreateGraph_3()
{
	struct Vertex
	{
		//int data;
	};
	/*
	*  6*6 �� 2�� ���
	*  ����� ���¸� ǥ��
	* 
		[X][O][X][O][X][X]
		[O][X][O][O][X][X]
		[X][X][X][X][X][X]
		[X][X][X][X][O][X]
		[X][X][X][X][X][X]
		[X][X][X][X][O][X]

	*/
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	//���� ��� : adjacent[from][to]
	//2���� ����� �̿��� �׷��� ǥ��
	//�޸� �Ҹ� ũ����, ���� ������ �����ϴ� => ���� ������ ����.
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;


	//0->3 check
	bool connected3 = adjacent[0][3];

	vector<vector<int>> adjacent2(6, vector<int>(6, -1));

	adjacent2[0][1] = 15;
	adjacent2[0][3] = 35;
	adjacent2[1][0] = 15;
	adjacent2[1][2] = 5;
	adjacent2[1][3] = 10;
	adjacent2[3][4] = 5;
	adjacent2[5][4] = 5;

	//0->3 check
	bool connected4 = (adjacent2[0][4] != -1);
	int weight = adjacent2[0][3];

	cout << connected4 << " " << weight << endl;
}

#if 0

int main()
{
	CreateGraph_1();
	CreateGraph_2();
	CreateGraph_3();
}
#endif // 1
