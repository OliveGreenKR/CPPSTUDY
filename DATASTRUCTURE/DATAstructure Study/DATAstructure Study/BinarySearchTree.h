#pragma once

struct Node
{
	Node* parent = nullptr;
	Node* left =  nullptr;
	Node* right = nullptr;
	int key = {};
	

	//bool external;   //추가적인 bool을 통해 leaf여부를 저장할 수 있음
						//이럴경우 아무것도 없는 노드(Nill Node)를 nullptr
						//이 아닌 더미노드로 채우고, leaf여부를 확인할 수 있도록
						//관리할 수 있다.
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

