#include <iostream>
using namespace std;



const class //NullPtr
{
public:
	void Func() {};

	//any type pointer
	template<typename T>
	operator T* () const
	{
		return 0;
	}
	//ant member pointer
	template<typename T, typename C>
	operator T C::*() const
	{
		return 0;
	}
	//�ּҰ� ���� ���ϵ��� ����
	void operator&() const = delete; 

} _nullptr;//Ŭ���� ����� ���ÿ� ��ü ���� ->�̷��� �Ұ��
//Ŭ���� �̸��� �ʿ䰡 ����-->�̷��� �ϸ� �ٸ� ��ü ���� x



#if 0
int  main()
{
	return 0;
}
#endif // 1
