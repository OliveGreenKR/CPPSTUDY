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
	//주소값 참조 못하도록 방지
	void operator&() const = delete; 

} _nullptr;//클래스 선언과 동시에 객체 생성 ->이렇게 할경우
//클래스 이름도 필요가 없음-->이렇게 하면 다른 객체 생성 x



#if 0
int  main()
{
	return 0;
}
#endif // 1
