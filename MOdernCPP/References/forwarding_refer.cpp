#include <iostream>
using namespace std;

//���� ����

class Knight
{
public:
	Knight(){cout << "�⺻������" << endl;}
	Knight(const Knight& knight){cout << "���������" << endl;}
	Knight(Knight&&) noexcept {cout << "�̵�������" << endl;} 

};

void Test_RValueRef(Knight&& knight)
{}

void Test_Copy(Knight K)
{}

template<typename T>
void Test_ForwardingRef(T&& param) //��������
{
	//todo
	//Test_Copy(param); //param �� �ް������϶�
	//Test_Copy(std::move(param)); //param�� ����������
	Test_Copy(std::forward<T>(param)); //��������
}


#if 0

int main()
{

	Knight k1;

	//Test_RValueRef(move(k1));

	//Test_ForwardingRef(move(k1)); //������ ������ ����
	//Test_ForwardingRef(k1);//�ް� ������ ����

	//auto&& k2 = k1; //�̷��� �ص� �ް� ������ ����
	//auto&& k3 = move(k1); //������ ������ ����
	//=========================================

	Knight& k4 = k1; //left ref
	Knight&& k5 = std::move(k1); //right ref

	Test_ForwardingRef(std::move(k1));  
	Test_ForwardingRef(k1);  
	//k5�� ������ ����������!, �������� �ƴ�.
	//(�������� ���ϽĿ��� ����� ����� �Ұ����� ��)
	
	return 0;
}
#endif // 1
