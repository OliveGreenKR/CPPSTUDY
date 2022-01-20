#if 1
#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

template<typename T>
class Priority_Queue
{
public:
	Priority_Queue()
	{}

	void push(const T& data)
	{
		_container.push_back(data);
		Arrange();
	}

	bool empty()
	{
		return _container.empty();
	}
	
	T& top()
	{
		return _container[0];
	}

	void pop()
	{
		int size = _container.size();
		int top = _container[0];

		swap(_container[0], _container[size - 1]);
		_container.pop_back();
		Arrange();
	}


private:
	vector<T> _container;
	void Arrange()
	{
		int size = _container.size();
		for (int i = size - 1; i > 0; --i)
		{
			int parent = (i - 1) / 2;
			if (_container[parent] < _container[i])
				swap(_container[parent], _container[i]);
		}
	}
};

int main()
{
	/*priority_queue<int> pq;*/
	Priority_Queue<int> pq;

	pq.push(100);
	pq.push(500);
	pq.push(200);
	pq.push(300);
	pq.push(400);
	pq.push(600);

	while (pq.empty() == false)
	{
		int value = pq.top();
		pq.pop();

		cout << value << endl;
	}
}
#endif // 1
