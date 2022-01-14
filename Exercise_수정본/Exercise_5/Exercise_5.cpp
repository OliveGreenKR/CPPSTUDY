#include <iostream>
using namespace std;
#include "Knight.h"

// [Bug Report #5]
// 최대 체력(MaxHP)의 개념이 추가되었습니다.
// 아울러 짜릿한 역전의 희망을 주기 위해
// 체력이 50% 이하로 떨어지면 공격 데미지를 2배로 적용합니다.
// 테스트를 위해 기사 두마리를 생성하고 한대씩 데미지를 주고 받습니다.
// 그런데 또 프로그램이 크래시나는 문제가 발생하고 있습니다.
// 원인을 파악하고 의도대로 동작하게 수정해주세요!

// 비율계산이 정수로 되어있어서 0으로나누는 문제가 생김
// 비율계산을 수정해서 문제해결

//==> 0이 될 가능성이 매우 낮은 최대체력을 이용해 리코딩!

int main()
{
	Knight* k1 = new Knight();
	k1->_hp = 100;
	k1->_maxHp = 100;
	k1->_attack = 100;

	Knight* k2 = new Knight();
	k2->_hp = 100;
	k2->_maxHp = 100;
	k2->_attack = 100;

	int damage = k1->GetAttackDamage();
	k2->AddHp(-damage);
	cout << damage << endl;

	int damage2 = k2->GetAttackDamage();
	k1->AddHp(-damage2);
	cout << damage2 << endl;
	delete k1;
	delete k2;
}
