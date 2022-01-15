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
		if(_target.expired() == false)
		{
			auto target = _target.lock();
			target->_hp -= _dmg;
			cout << "Target HP : " << target->_hp << endl;
		}
	}
public:
	int _hp = 100;
	int _dmg = 10;
	weak_ptr<Knight> _target;

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

	shared_ptr<Knight> k1 = make_shared<Knight>();
	//shared_ptr<Knight> k1 (new Knight());// 가능은 하나 위 버젼이 성능이 더 좋음
	
	
	shared_ptr<Knight> k2 = make_shared<Knight>();
	k1->_target = k2;
	k2->_target = k1;
	//k2->_target = nullptr;
	
	k1->Attack(); 
	//k1->_target = nullptr;
	

	return 0; 


}
#endif // 0
