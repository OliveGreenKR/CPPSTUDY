#include <iostream>
using namespace std;

#include <vector>

class Class
{
public:
	Class()
	{
		//
	}
	Class(initializer_list<int> li)
	{
		//
	}
	int _data=0;

};

int main()
{
	
	
	int b{ 3 }; //중괄호 초기화

	Class c1;
	Class c2 = c1; //복사 생성자
	Class c22{ c1 };

	Class c3;
	c3 = c1; //대입연산자

	vector<int> v1{ 1,2,4,5,6,0 };

	int a[]{ 1,2,3,4 };
	int d{ 3 };

	int x = 10;
	//축소변환시 컴파일 에러가 뜬다
	double y{ x };

}