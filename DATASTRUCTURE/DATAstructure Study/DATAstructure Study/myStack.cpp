#if 0
#include <iostream>
#include <stack>
#include <vector>
#include <list>
using namespace std;

//Stack.  후입선출 구조

//ex.  되돌리기 기능

template <typename T>
class Stack
{
public:

	void push(T data)
	{
		_container.push_back(data);
	}
	void pop()
	{
		_container.pop_back();
	}

	bool empty()
	{
		return _container.empty();
	}

	T top()
	{
		return _container.back();
	}

	size_t size()
	{
		return _container.size();
	}

public:
	//vector<T> _container;
	list<T> _container;

};



#if 0
int main()
{
	Stack<int> s;
	
	//삽입s
	s.push(1);
	s.push(2);
	s.push(3);

	

	// 비었나?
	while (!s.empty())
	{
		//확인
		int data = s.top();
		//제거
		s.pop();

		cout << data << endl;
	}

	int size = s.size();

	cout << "now stack size is : " <<
		size << endl;
}
#endif // 1
#endif