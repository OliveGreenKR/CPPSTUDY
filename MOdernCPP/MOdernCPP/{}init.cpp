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
	
	
	int b{ 3 }; //�߰�ȣ �ʱ�ȭ

	Class c1;
	Class c2 = c1; //���� ������
	Class c22{ c1 };

	Class c3;
	c3 = c1; //���Կ�����

	vector<int> v1{ 1,2,4,5,6,0 };

	int a[]{ 1,2,3,4 };
	int d{ 3 };

	int x = 10;
	//��Һ�ȯ�� ������ ������ ���
	double y{ x };

}