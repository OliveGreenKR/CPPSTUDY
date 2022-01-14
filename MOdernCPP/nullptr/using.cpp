#include <iostream>
#include <list>
using namespace std;

//void 반환 함수의 포인터 
typedef void* MyFunc();
using MyFunc = void(*)();

template<typename T>
struct List2
{
	typedef std::list<T> mytype;
};

template<typename T>
using List = std::list<T>;


#if 0
int main()
{
	List<int>li1{1, 2};
	List2<int>::mytype li2{1,2,3};
}
#endif // 1

