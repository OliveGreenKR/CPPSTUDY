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
//�߰����� bool�� ���� leaf���θ� ������ �� ����
//�̷���� �ƹ��͵� ���� ���(Nill Node)�� nullptr
//�� �ƴ� ���̳��� ä���, leaf���θ� Ȯ���� �� �ֵ���
//������ �� �ִ�.

/*Red Black Tree
	1. ��� ���� �� or ����
	2. ��Ʈ�� ��
	3. ��� ������ ��
	4. ������ �ڽ��� ��
	5. �� ���κ���~ �������� ���� ��� ��δ� ���� ���� �� ��带 ������.*/

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

