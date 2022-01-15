#include <iostream>
#include<algorithm>
using namespace std;


// 스마트 포인터
class Knight
{
public:
	Knight()
	{
		cout << "기사생성" << endl;
	}

	~Knight()
	{
		cout << "기사소멸" << endl;
	}

	void Attack()
	{
		if(_target)
		{
			_target->_hp -= _dmg;
			cout << "Target HP : " << _target->_hp << endl;
		}
	}
public:
	int _hp = 100;
	int _dmg = 10;
	Knight* _target = nullptr;

};

class RefCountBlock
{
public:
	int _refCount = 1;
};

template<typename T>
class SharedPtr
{
public:
	SharedPtr()
	{
	}
	SharedPtr(T* ptr) : _ptr(ptr) 
	{
		if(ptr != nullptr)
		{
			_block = new RefCountBlock;
			cout << "Ref Count : " << _block->_refCount << endl;
		}
	}
	SharedPtr(const SharedPtr& sptr) : _ptr(sptr._ptr),
		_block(sptr._block)
	{
		if (_ptr != nullptr)
		{
			_block->refCount++;
			cout << "Ref Count : " << _block->_refCount << endl;
		}
	}
	~SharedPtr() 
	{
		if (_ptr != nullptr)
		{
			_block->_refCount--;
			cout << "Ref Count : " << _block->_refCount << endl;
			if(_block->_refCount == 0)
			{
				delete _ptr;
				delete _block;
				cout << "delete Data" << endl;
			}
		}
	}
	void operator=(const SharedPtr& sptr)
	{
		_ptr = sptr._ptr;
		_block = sptr._block;

		if (_ptr != nullptr)
		{
			_block->_refCount++;
			cout << "Ref Count : " << _block->_refCount << endl;
		}
	}
	
public:
	T* _ptr = nullptr;
	RefCountBlock* _block = nullptr;
};



#if 1

int main()
{
	/*Knight* k1 = new Knight();
	Knight* k2 = new Knight();

	k1->_target = k2;

	delete k2;*/


	SharedPtr<Knight> k2; // 생성 (1)
	{
	SharedPtr<Knight> k1 = new Knight(); // 1
	k2 = k1; //2
	}



	return 0;


}
#endif // 0
