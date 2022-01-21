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

void SetConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO	cursorinfo;
	::GetConsoleCursorInfo(output, &cursorinfo);
	cursorinfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorinfo);
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

void BinarySearchTree::Print()
{
	::system("cls");
	SetConsoleCursor(false);
	Print(_root, 10, 0);
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

//BST������ �����ϰ� ��-����Ʈ�� ���� �� ��
void BinarySearchTree::Delete(Node* node)
{
	if (node == _nil)
		return;

	if (node->left == _nil) //�ڽ��� �ϳ��� ���ų� �ϳ������� ��
	{
		//������ ����� ����
		Color color = node->color; 
		Node* right = node->right;

		Replace(node, node->right);
		if (color == Color::Black)
			DeleteFixup(right);
	}
	else if (node->right == _nil)
	{
		Color color = node->color;
		Node* left = node->left;

		Replace(node, node->left);
		if (color == Color::Black)
			DeleteFixup(left);
	}
	else//�Ѵ� ���� ��
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}

	

}

//����� Ʈ���� ��Ģ��� �ٲ��ְ� �ɰ�
void BinarySearchTree::DeleteFixup(Node* node)
{
	Node* x = node;  //������ ���

	//[case1][case2]
	while (x != _root && x->color == Color::Black)
	{
		if(x == x->parent->left) //������ ����� ��ġ Ȯ��
		{
			//[case3]üũ
			Node* s = x->parent->right;
			if (s->color == Color::Red) //������ ������
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;

				LeftRotate(x->parent);  //�θ�������� DB�������� ȸ��

				s = x->parent->right; //������ �ٲ������ ��������
			}
			//case 4
			if(s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
			else //case 5�̸� case6���� ����
			{
				if (s->right->color == Color::Black)
				{
					s->left->color = Color::Black;
					s->color = Color::Red;
					RightRotate(s);
					s = x->parent->right;
				}

				//case 6
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				LeftRotate(x->parent);
				x = _root; //loop ����
			}
		}
		else
		{
			//[case3]üũ
			Node* s = x->parent->left;
			if (s->color == Color::Red) //������ ������
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;

				RightRotate(x->parent);  //�θ�������� DB�������� ȸ��

				s = x->parent->left; //������ �ٲ������ ��������
			}
			//case 4
			if (s->right->color == Color::Black && s->left->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
			else //case 5�̸� case6���� ����
			{
				if (s->left->color == Color::Black)
				{
					s->right->color = Color::Black;
					s->color = Color::Red;
					LeftRotate(s);
					s = x->parent->left;
				}

				//case 6
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				RightRotate(x->parent);
				x = _root; //loop ����
			}

		}
		
	}
	//x�� ���� Red��
	x->color = Color::Black;
}

//u ����Ʈ���� v����Ʈ���� ��ü ��, u�� ����
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil)
		_root = v;
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
		u->parent->right = v;

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
