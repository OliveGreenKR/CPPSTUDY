#if 1
#include <iostream>
#include <vector>
#include<queue>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

template<typename T, class Container =  vector<T>>
class Priority_Queue
{
public:
	Priority_Queue()
	{}

	void push(const T& data)
	{
		//우선 힙 구조 부터 맞춰줌
		_container.push_back(data);

		//도장깨기_정렬
		int now = static_cast<int>(_container.size()) - 1;
		while (now > 0)
		{
			int parent = (now - 1) / 2;

			if (_container[parent] > _container[now])
				break;

			::swap(_container[parent], _container[now]);
			now = parent;
		}
		/*Arrange();*/


	}

	void pop()
	{
		_container[0] = _container.back();
		_container.pop_back();

		//정렬
		int now = 0;
		while (true)
		{
			int child1 = 2*now + 1;
			int child2 = 2*now + 2;

			if (child1 >= _container.size())
				break;
			int next = now;

			//compare to left
			if (_container[next] < _container[child1])
				next = child1;

			//둘 중 승자를 오른쪽과 비교
			if (child2 < _container.size() && _container[next] < _container[child2])
				next = child2;
			
			if (next == now)
				break;

			::swap(_container[now], _container[next]);
			now = next;
		}
		/*Arrange();*/
	}

	bool empty()
	{
		return _container.empty();
	}
	
	T& top()
	{
		return _container[0];
	}

private:
	Container _container;

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
