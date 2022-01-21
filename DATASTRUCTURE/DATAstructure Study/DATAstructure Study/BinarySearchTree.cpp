#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr) return;

	SetCursorPosition(x, y);
	cout << node->key;
	Print(node-> left, x - (5 / (y + 1)), y + 1);
	Print(node-> right, x + (5 / (y + 1)), y + 1);
}

//중위 순회법
void BinarySearchTree::Print_Inorder(Node* node)
{
	if (node == nullptr)
	{
		cout << endl << "___________________________" << endl;
		return;
	}
	Print_Inorder(node->left);
	cout << node->key << endl;
	Print_Inorder(node->right);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(); //삽입노드

	newNode->key = key;

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	//추가할 곳 탐색
	Node* node = _root;
	Node* parent = nullptr;

	while (node)
	{
		parent = node; //root

		if (key < node->key) //작으면 왼쪽
			node = node->left;
		else
			node = node->right;//크면 오른족
	}
	//저장
	newNode->parent = parent;

	if (key < parent->key) //작으면 왼쪽
		parent->left = newNode;
	else
		parent->right = newNode;//크면 오른족

}

Node* BinarySearchTree::Search(int key, Node* node)
{
	//while (node&& key !=  node->key)
	//{
	//	if (node->key > key) //찾으려는 값이 더 작다
	//		node = node->left;
	//	else
	//		node = node->right;
	//}
	//return node;

	//>>>.recursion
	if (node == nullptr || key == node->key)
	{
		if (node == nullptr)
			cout << "not found" << endl;

		return node;
	}

	if (node->key > key)
		return Search(key, node->left);
	else
		return Search(key, node->right);
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right)
	{
		node = node->right;
	}
	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	if(node->left == nullptr)
		return node;
	else
	return Min(node->left);
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node == nullptr)
		return node;
	//한번 오른쪽으로 간 후, 왼쪽으로 끝까지 가면 됨
	
	//오른쪽이 없으면 ->  1. 자신이 부모의 오른쪽일 때 -> 부모가 왼쪽값일때까지 부모추적
					// 2. 자신이 부모의 왼쪽일 때 -> 부모 리턴
	if (node->right == nullptr)
	{
		while(node->parent && node->parent->right == node)
		{
			node->parent = node->parent->parent;
		}
		return node->parent;
	}
	else
	{
		return Min(node->right);
	}
	
	
}

void BinarySearchTree::Delete(int key)
{
	//1. 자식 없음
	//2. 자식 하나
	//3. 자식 둘 --> 삭제될 것의 Next는 자신의 위치에 오고 Next삭제함수 호출

	Node* deleteNode = Search( key, _root);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	if (node->left == nullptr) //자식이 하나도 없거나 하나만있을 때
	{
		Replace(node, node->right);
	}
	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}
	else//둘다 있을 때
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
	
}

//u 서브트리를 v서브트리로 교체 후, u를 삭제
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
		_root = v;
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
		u->parent->right = v;

	if (v)
		v->parent = u->parent;
	delete u;
}
