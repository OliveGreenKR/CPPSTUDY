#include <iostream>
using namespace std;
//�ް� ������ ���� : ���� �ٽ����� cpp11�� ��ȭ, ��!

//#�� ��(l - value) : ���Ͻ��� �Ѿ ��� ���ӵǴ� ��ü
//
//
//
//#���� ��(r - value) : �ް��� �ƴ� ������
//(�ӽ� ��, ������, ����, i++ �� ...)

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
	Knight(const Knight& knight) //���������
	{
		cout << "Knight(Knight&)!" << endl;
	}
	
	Knight(Knight&& knight) //�̵� ������
	{}

	~Knight()
	{
		if (_pet)
		{
			delete _pet;
		}
		cout << "~Knight()!" << endl;
	}

	//���� ������
	void operator=(const Knight& knight)
	{
		// ���� ����
		cout << "���Կ�����" << endl;
		
		_hp = knight._hp;
		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}

	//�̵� ���� ������
	void operator=(Knight&& knight) noexcept //������ ���� �ʴ� �ٴ� ��?
	{
		cout << "�̵� ���� ������" << endl;
		//���� ���� 
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
	
	//�̵����� ������ ȣ��
	/*Knight k3 = static_cast<Knight&&>(k2); */
	Knight k3 = std::move(k2); 

	unique_ptr<Knight> uptr = make_unique<Knight > ();
	//new knight()�� unique�ϰ� ������ �ְ� �����Ѵ�.

	unique_ptr<Knight> uptr2 = move(uptr); ///�������� '�̵�'
	//uptr �� ���� �� empty�� �ȴ�//
	
	return 0;

}
#endif // 1
