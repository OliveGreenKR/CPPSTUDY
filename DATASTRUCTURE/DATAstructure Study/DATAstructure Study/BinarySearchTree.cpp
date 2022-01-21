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
	Node* newNode = new Node(); //삽입노드
	newNode->key = key;

	//추가할 곳 탐색
	Node* node = _root;
	Node* parent = _nil;

	while (node!= _nil)
	{
		parent = node; //root

		if (key < node->key) //작으면 왼쪽
			node = node->left;
		else
			node = node->right;//크면 오른족
	}
	//저장
	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;

	else if (key < parent->key) //작으면 왼쪽
		parent->left = newNode;
	else
		parent->right = newNode;//크면 오른족

	//검사 (레드블랙트리)
	newNode->left = _nil;
	newNode->right = _nil;
	// 레드블랙트리 특성상 새로 추가하는 것은 모두 레드
	newNode->color = Color::Red;

	InsertFixup(newNode);

}

void BinarySearchTree::InsertFixup(Node* node)
{
	//	1) p = red, uncle = red
	//	2) p = red, uncle = black (triangle)
	//	3) p = red, uncle = black (list)

	//
	while (node->parent->color == Color::Red)//부모님 붉은색
	{
		if (node->parent == node->parent->parent->left) //부모가 왼쪽
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)//삼촌 붉은색
			{
				//부모, 삼촌의 색을 블랙으로, 조부모님의 색상을 레드로 변환
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;
				
				//조부모님 반복
				node = node->parent->parent;
			}
			else //삼촌이 검은색
			{
				if (node == node->parent->right) //트라이앵글(내가 오른쪽)
				{
					node = node->parent;
					LeftRotate(node); //부모 중심 좌회전
					//-->리스트형태로 만들어줌
				}
				//리스트(내가 왼쪽)
				
					//부모를 블랙, 조부모는 레드, 조부모 중심으로 우회전
					node->parent->color = Color::Black;
					node ->parent->parent->color = Color::Red;
					RightRotate(node->parent->parent);
				

			}
		}
		else//부모가 오른쪽
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->color == Color::Red)//삼촌 붉은색
			{
				//부모, 삼촌의 색을 블랙으로, 조부모님의 색상을 레드로 변환
				node->parent->parent->color = Color::Red;
				node->parent->color = Color::Black;
				uncle->color = Color::Black;

				//조부모님 반복
				node = node->parent->parent;
			}
			else //삼촌이 검은색
			{
				if (node == node->parent->left) //트라이앵글(내가 오른쪽)
				{
					node = node->parent;
					RightRotate(node); //부모 중심 우회전
					//-->리스트형태로 만들어줌
				}
				//리스트(내가 왼쪽)
				
					//부모를 블랙, 조부모는 레드, 조부모 중심으로 우회전
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
	//	if (node->key > key) //찾으려는 값이 더 작다
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


//한번 오른쪽으로 간 후, 왼쪽으로 끝까지 가면 됨
//오른쪽이 없으면 ->  1. 자신이 부모의 오른쪽일 때 -> 부모가 왼쪽값일때까지 부모추적
// 2. 자신이 부모의 왼쪽일 때 -> 부모 리턴
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
	//1. 자식 없음
	//2. 자식 하나
	//3. 자식 둘 --> 삭제될 것의 Next는 자신의 위치에 오고 Next삭제함수 호출

	Node* deleteNode = Search( key, _root);
	Delete(deleteNode);
}

//BST삭제를 실행하고 블랙-레드트리 보정 들어갈 것
void BinarySearchTree::Delete(Node* node)
{
	if (node == _nil)
		return;

	if (node->left == _nil) //자식이 하나도 없거나 하나만있을 때
	{
		//삭제할 노드의 정보
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
	else//둘다 있을 때
	{
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}

	

}

//레드블랙 트리의 규칙대로 바꿔주게 될것
void BinarySearchTree::DeleteFixup(Node* node)
{
	Node* x = node;  //삭제할 노드

	//[case1][case2]
	while (x != _root && x->color == Color::Black)
	{
		if(x == x->parent->left) //삭제할 노드의 위치 확인
		{
			//[case3]체크
			Node* s = x->parent->right;
			if (s->color == Color::Red) //형제가 붉은색
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;

				LeftRotate(x->parent);  //부모기준으로 DB방향으로 회전

				s = x->parent->right; //형제가 바뀌었으니 갱신해줌
			}
			//case 4
			if(s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
			else //case 5이면 case6으로 만듦
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
				x = _root; //loop 해제
			}
		}
		else
		{
			//[case3]체크
			Node* s = x->parent->left;
			if (s->color == Color::Red) //형제가 붉은색
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;

				RightRotate(x->parent);  //부모기준으로 DB방향으로 회전

				s = x->parent->left; //형제가 바뀌었으니 갱신해줌
			}
			//case 4
			if (s->right->color == Color::Black && s->left->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}
			else //case 5이면 case6으로 만듦
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
				x = _root; //loop 해제
			}

		}
		
	}
	//x의 색이 Red임
	x->color = Color::Black;
}

//u 서브트리를 v서브트리로 교체 후, u를 삭제
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
