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

//���� ��ȸ��
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
	Node* newNode = new Node(); //���Գ��

	newNode->key = key;

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	//�߰��� �� Ž��
	Node* node = _root;
	Node* parent = nullptr;

	while (node)
	{
		parent = node; //root

		if (key < node->key) //������ ����
			node = node->left;
		else
			node = node->right;//ũ�� ������
	}
	//����
	newNode->parent = parent;

	if (key < parent->key) //������ ����
		parent->left = newNode;
	else
		parent->right = newNode;//ũ�� ������

}

Node* BinarySearchTree::Search(int key, Node* node)
{
	//while (node&& key !=  node->key)
	//{
	//	if (node->key > key) //ã������ ���� �� �۴�
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
	//�ѹ� ���������� �� ��, �������� ������ ���� ��
	
	//�������� ������ ->  1. �ڽ��� �θ��� �������� �� -> �θ� ���ʰ��϶����� �θ�����
					// 2. �ڽ��� �θ��� ������ �� -> �θ� ����
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
	//1. �ڽ� ����
	//2. �ڽ� �ϳ�
	//3. �ڽ� �� --> ������ ���� Next�� �ڽ��� ��ġ�� ���� Next�����Լ� ȣ��

	Node* deleteNode = Search( key, _root);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	if (node->left == nullptr) //�ڽ��� �ϳ��� ���ų� �ϳ������� ��
	{
		Replace(node, node->right);
	}
	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}
	else//�Ѵ� ���� ��
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
	
}

//u ����Ʈ���� v����Ʈ���� ��ü ��, u�� ����
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
