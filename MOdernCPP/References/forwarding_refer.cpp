#include <iostream>
using namespace std;

//전달 참조

class Knight
{
public:
	Knight(){cout << "기본생성자" << endl;}
	Knight(const Knight& knight){cout << "복사생성자" << endl;}
	Knight(Knight&&) noexcept {cout << "이동생성자" << endl;} 

};

void Test_RValueRef(Knight&& knight)
{}

void Test_Copy(Knight K)
{}

template<typename T>
void Test_ForwardingRef(T&& param) //전달참조
{
	//todo
	//Test_Copy(param); //param 이 왼값참조일때
	//Test_Copy(std::move(param)); //param이 오른값참조
	Test_Copy(std::forward<T>(param)); //최종버전
}


#if 0

int main()
{

	Knight k1;

	//Test_RValueRef(move(k1));

	//Test_ForwardingRef(move(k1)); //오른값 참조로 받음
	//Test_ForwardingRef(k1);//왼값 참조로 받음

	//auto&& k2 = k1; //이렇게 해도 왼값 참조로 받음
	//auto&& k3 = move(k1); //오른값 참조로 받음
	//=========================================

	Knight& k4 = k1; //left ref
	Knight&& k5 = std::move(k1); //right ref

	Test_ForwardingRef(std::move(k1));  
	Test_ForwardingRef(k1);  
	//k5는 오른값 참조이지만!, 오른값은 아님.
	//(오른값은 단일식에서 벗어나면 사용이 불가능한 것)
	
	return 0;
}
#endif // 1
