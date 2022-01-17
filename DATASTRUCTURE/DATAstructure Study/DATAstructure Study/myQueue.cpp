#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <queue>
#include <deque>
using namespace std;

//Queue 선입선출

//[][][][]
template <typename T>
class Queue
{
public:
	void push(const T& data)
	{
		_container.push_back(data);
	}
	void pop()
	{
		//_container.erase(_container.begin());
		_container.pop_front();
	}

	T& front()
	{
		return _container.front();
	}

	size_t size()
	{
		return _container.size();
	}
	bool empty()
	{
		return _container.empty();
	}
private:
	//pop의 동작이 너무느림 :O(n)복잡도
	/*vector<T> _container; */
	//list<T> _container;
	deque<T> _container;
};

template <typename T>
class ArrayQueue
{
public:
	ArrayQueue()
	{
		_container.resize(100);
	}
	void push(const T& data)
	{
		//todo :  가득 체크
		if (_size == _container.size())
		{
			//증설
				//max: 둘중 더 큰거 리턴
			int newsize = max(1, _size * 2);
			vector<T> newData;
			newData.resize(newsize);

			//data copy
			for (size_t i = 0; i < _size; i++)
			{
				int index = (_front + i) % _container.size();
				newData[i] = _container[index];

				_container.swap(newData);
				_front = 0;
				_back = _size;
			}
		}
		_container[_back] = data;
		_back = (_back + 1) % _container.size();
		_size++;
	}
	void pop()
	{
		//todo : enmpty
		_front = (_front + 1) % _container.size();
		_size--;
	}

	T& front()
	{
		return _container[_front];
	}

	size_t size()
	{
		return _size;
	}
	bool empty()
	{
		return _size == 0;
	}
private:
	vector<T> _container;

	int _front = 0;
	int _back = 0;
	int _size = 0;
};



#if 0
int main()
{
	ArrayQueue<int> q;

	for (size_t i = 0; i < 100; i++)
	{
		q.push(i);
	}
	
	while (!q.empty())
	{
		int val = q.front();
		q.pop();
		cout << val << endl;
	}

	int size = q.size();
}
#endif // 1
