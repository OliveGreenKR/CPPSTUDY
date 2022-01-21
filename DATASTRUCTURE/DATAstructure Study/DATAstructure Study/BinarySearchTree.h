#pragma once

enum class Color
{
	Red =0,
	Black =1,
};


struct Node
{
	Node* parent = nullptr;
	Node* left =  nullptr;
	Node* right = nullptr;
	int key = {};

	Color color = Color::Black;

	//bool external;   
};
//추가적인 bool을 통해 leaf여부를 저장할 수 있음
//이럴경우 아무것도 없는 노드(Nill Node)를 nullptr
//이 아닌 더미노드로 채우고, leaf여부를 확인할 수 있도록
//관리할 수 있다.

/*Red Black Tree
	1. 모든 노드는 블랙 or 레드
	2. 루트는 블랙
	3. 모든 리프는 블랙
	4. 레드의 자식은 블랙
	5. 각 노드로부터~ 리프까지 가는 모든 경로는 같은 수의 블랙 노드를 지난다.*/

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void Print();
	void Print(Node* node, int x, int y);

	void Insert(int key);
	void InsertFixup(Node* node);

	Node* Search(int key, Node* node);
	Node* Search(int key) {return Search(key, _root); }

	Node* Max(Node* node);
	Node* Min(Node* node);
	Node* Next(Node* node);

	void Delete(int key);
	void Delete(Node* node);
	void DeleteFixup(Node* node);

	void Replace(Node* u, Node* v);
	Node* const Getroot() { return _root; }

	//Red-Black_Tree
	void LeftRotate(Node* node);
	void RightRotate(Node* node);

private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};

