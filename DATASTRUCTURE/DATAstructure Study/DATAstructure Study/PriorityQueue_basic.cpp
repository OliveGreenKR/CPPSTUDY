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
	

private:
	vector<T> _data;
};

int main()
{
	priority_queue<int> pq;

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
