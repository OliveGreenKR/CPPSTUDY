#include <iostream>
using namespace std;
//왼값 오른값 참조 : 가장 핵심적인 cpp11의 변화, 꽃!

//#왼 값(l - value) : 단일식을 넘어서 계속 지속되는 개체
//
//
//
//#오른 값(r - value) : 왼값이 아닌 나머지
//(임시 값, 열거형, 람다, i++ 등 ...)

class Pet
{
};

class Knight
{
public:
	Knight()
	{
		cout << "Knight()!" << endl;
	}
	Knight(const Knight& knight) //복사생성자
	{
		cout << "Knight(Knight&)!" << endl;
	}
	
	Knight(Knight&& knight) //이동 생성자
	{}

	~Knight()
	{
		if (_pet)
		{
			delete _pet;
		}
		cout << "~Knight()!" << endl;
	}

	//대입 연산자
	void operator=(const Knight& knight)
	{
		// 깊은 복사
		cout << "대입연산자" << endl;
		
		_hp = knight._hp;
		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}

	//이동 대입 연산자
	void operator=(Knight&& knight) noexcept //에러를 뱉지 않는 다는 뜻?
	{
		cout << "이동 대입 연산자" << endl;
		//얕은 복사 
		_hp = knight._hp;
		_pet = knight._pet;
		 
		knight._pet = nullptr;
	}

	void PrintInfo(){}
	void ConstPrintInfo() const{}

public:

	int _hp = 100;
	Pet* _pet = nullptr;
};



void TestKnight_Copy(Knight knight){}

void TestKnight_LValueRef(Knight& knight){}
void TestKnight_ConstLValueRef(const Knight& knight){}
void TestKnight_RValueRef(Knight&& knight){}


#if 0

int main()
{
	Knight k1;
	TestKnight_Copy(k1);
	TestKnight_LValueRef(k1);
	
	TestKnight_RValueRef(Knight());
	/*TestKnight_LValueRef(Knight());*/
	TestKnight_ConstLValueRef(Knight());

	Knight k2;
	k2._pet = new Pet();
	k2._hp = 100;
	
	//이동대입 연산자 호출
	/*Knight k3 = static_cast<Knight&&>(k2); */
	Knight k3 = std::move(k2); 

	unique_ptr<Knight> uptr = make_unique<Knight > ();
	//new knight()를 unique하게 가지고 있게 동작한다.

	unique_ptr<Knight> uptr2 = move(uptr); ///소유권을 '이동'
	//uptr 은 실행 후 empty가 된다//
	
	return 0;

}
#endif // 1
