#pragma once

struct Node
{
	Node* parent = nullptr;
	Node* left =  nullptr;
	Node* right = nullptr;
	int key = {};
	

	//bool external;   //�߰����� bool�� ���� leaf���θ� ������ �� ����
						//�̷���� �ƹ��͵� ���� ���(Nill Node)�� nullptr
						//�� �ƴ� ���̳��� ä���, leaf���θ� Ȯ���� �� �ֵ���
						//������ �� �ִ�.
};


class BinarySearchTree
{
public:
	void Print() { Print(_root, 10, 0); }
	void Print(Node* node, int x, int y);

	void Print_Inorder(Node* node);
	void Print_Inorder() { Print_Inorder(_root); }

	void Insert(int key);

	Node* Search(int key, Node* node);
	Node* Search(int key) {return Search(key, _root); }

	Node* Max(Node* node);
	Node* Min(Node* node);
	Node* Next(Node* node);

	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u, Node* v);
	Node* const Getroot() { return _root; }
private:
	Node* _root = nullptr;
};

