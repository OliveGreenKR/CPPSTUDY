#include "Knight.h"
#include <iostream>
using namespace std;

// [사양서] 기본값 Hp=100, Attack=10
Knight::Knight() : _hp(100), _maxHp(100), _attack(10)
{

}

Knight::Knight(int hp) : _hp(hp), _maxHp(hp), _attack(10)
{

}

Knight::~Knight()
{

}

void Knight::AddHp(int value)
{
	_hp += value;
	if (_hp < 0)
		_hp = 0;
	if (_hp > _maxHp)
		_hp = _maxHp;
}

bool Knight::IsDead()
{
	return (_hp <= 0);
}

int Knight::GetAttackDamage()
{
	// hp 50% 이하 => maxHp / hp가 2 이상
	int damage = _attack;

	//0이 될 가능성이 매우 맞은 최대체력을 이용해 리코딩!
	if(_maxHp == 0 )
	{
		return damage;
	}

	//정수끼리 나눗셈을 할때 0이 나오는 것을 막는 방법 2가지 
	int ratio = (_hp / static_cast<float>(_maxHp)) * 100;
	//int ratio = (_hp * 100 / _maxHp);

	if (ratio <= 50 ) damage *= 2;

	return damage;
}

void Knight::PrintInfo()
{
	cout << "HP: " << _hp << endl;
	cout << "ATT: " << _attack << endl;
}