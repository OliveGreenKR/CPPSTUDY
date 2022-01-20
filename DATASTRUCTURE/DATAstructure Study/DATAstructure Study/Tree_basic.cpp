#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>
#include <list>
#include <string>

using namespace std;
using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node() {}
	Node(const string data) :  data(data) {}

	string data;
	vector<NodeRef> children;
};

NodeRef CreateTree()
{

	NodeRef root = make_shared<Node>("R1개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("아트팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->children.push_back(leaf);
		}
	}


	return root;
}

void PrintTree(NodeRef root, int depth)
{
	for(int i= 0 ;  i < depth ; i++)
	{
		if (i == depth-1)
			cout << "-";
		cout << " ";
	}
	//재귀적 속성 이용(fractal)
	cout << root->data << endl;

	for (NodeRef& child : root->children)
	{
		PrintTree(child, ++depth);
	}
}

#if 1

int main()
{
	NodeRef root = 	CreateTree();
	PrintTree(root,0);

}
#endif // 1
