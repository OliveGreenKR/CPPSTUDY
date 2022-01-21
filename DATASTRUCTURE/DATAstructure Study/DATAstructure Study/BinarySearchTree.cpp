#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>

using namespace std;



enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}
void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

BinarySearchTree::BinarySearchTree() 
{
	_nil = new Node();
	_root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
	delete _nil;
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == _nil) return;

	SetCursorPosition(x, y);
	if(node->color == Color::Black)
	{
		SetCursorColor(ConsoleColor::BLUE);
	}
	else
	{
		SetCursorColor(ConsoleColor::RED);
	}
	cout << node->key;
	Print(node-> left, x - (5 / (y + 1)), y + 1);
	Print(node-> right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(); //���Գ��
	newNode->key = key;

	//�߰��� �� Ž��
	Node* node = _root;
	Node* parent = _nil;

	while (node!= _nil)
	{
		parent = node; //root

		if (key < node->key) //������ ����
			node = node->left;
		else
			node = node->right;//ũ�� ������
	}
	//����
	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;

	else if (key < parent->key) //������ ����
		parent->left = newNode;
	else
		parent->right = newNode;//ũ�� ������

	//�˻� (�����Ʈ��)
	newNode->left = _nil;
	newNode->right = _nil;
	// �����Ʈ�� Ư���� ���� �߰��ϴ� ���� ��� ����
	newNode->color = Color::Red;

	InsertFixup(newNode);

}

void BinarySearchTree::InsertFixup(Node* node)
{
	//	1) p = red, uncle = red
	//	2) p = red, uncle = black (triangle)
	//	3) p = red, uncle = black (list)

	//
	while (node->parent->color == Color::Red)//�θ�� ������
	{
		if (node->parent == node->parent->parent->left) //�θ� ����
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)//���� ������
			{
				//�θ�, ������ ���� ������, ���θ���� ������ ����� ��ȯ
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				
				//���θ�� �ݺ�
				node = node->parent->parent;
			}
			else //������ ������
			{
				if (node == node->parent->right) //Ʈ���̾ޱ�(���� ������)
				{
					node = node->parent;
					LeftRotate(node); //�θ� �߽� ��ȸ��
					//-->����Ʈ���·� �������
				}
				//����Ʈ(���� ����)
				
					//�θ� ��, ���θ�� ����, ���θ� �߽����� ��ȸ��
					node->parent->color = Color::Black;
					node ->parent->parent->color = Color::Red;
					RightRotate(node->parent->parent);
				

			}
		}
		else//�θ� ������
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->color == Color::Red)//���� ������
			{
				//�θ�, ������ ���� ������, ���θ���� ������ ����� ��ȯ
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;

				//���θ�� �ݺ�
				node = node->parent->parent;
			}
			else //������ ������
			{
				if (node == node->parent->left) //Ʈ���̾ޱ�(���� ������)
				{
					node = node->parent;
					RightRotate(node); //�θ� �߽� ��ȸ��
					//-->����Ʈ���·� �������
				}
				//����Ʈ(���� ����)
				
					//�θ� ��, ���θ�� ����, ���θ� �߽����� ��ȸ��
					node->parent->color = Color::Black;
					node->parent->parent->color = Color::Red;
					LeftRotate(node->parent->parent);
				
			}
		}
	}
	_root->color = Color::Black;
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
	if (node == _nil || key == node->key)
	{
		return node;
	}

	if (node->key > key)
		return Search(key, node->left);
	else
		return Search(key, node->right);
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right != _nil)
	{
		node = node->right;
	}
	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	if (node->left != _nil)
		node = node->left;
	return node;
}


//�ѹ� ���������� �� ��, �������� ������ ���� ��
//�������� ������ ->  1. �ڽ��� �θ��� �������� �� -> �θ� ���ʰ��϶����� �θ�����
// 2. �ڽ��� �θ��� ������ �� -> �θ� ����
Node* BinarySearchTree::Next(Node* node)
{
	if (node->right != _nil)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
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
	if (node == _nil)
		return;

	if (node->left == _nil) //�ڽ��� �ϳ��� ���ų� �ϳ������� ��
	{
		Replace(node, node->right);
	}
	else if (node->right == _nil)
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


// 	  	    [y]
//	    [x]		[3]
//    [1][2]


//  		[x]
//  	[1]		[y]
//  		   [2][3]
void BinarySearchTree::LeftRotate(Node* x) //down->up
{
	Node* y = x->right;

	x->right = y->left; //[2]

	if (y->left != _nil)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == _nil)
		_root = y;
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;

}

void BinarySearchTree::RightRotate(Node* y) //up->down
{
	Node* x = y->left;

	y->left = x->right; // [2]

	if (x->right != _nil)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == _nil)
		_root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}
