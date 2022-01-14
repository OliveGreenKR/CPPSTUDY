#include <iostream>
using namespace std;
#include "Knight.h"
#include "Archer.h"
#include "Mage.h"
#include "Pet.h"

// [Bug Report #9]
// 궁수가 죽으면 펫도 같이 죽는 사양이 추가되었습니다.
// 그런데 왜 프로그램도 같이 죽는걸까요?
// 이유를 찾아서 고쳐주세요!


//죽으면 펫이 사라지는데 소멸자에 중복으로 펫을 삭제함.
//둘중 하나를 지워서 해결. (아처소멸자에 있는 delete를 지움)

//--> 더 좋은 해결방법
//delete는 동적할당한 메모리만을 날림, 따라서 그 포인터는 유효하지 않은
//데이터를 여전히 가리키고있다
//따라서 delete후 nullptr을 넣어주는 습관을 항상 가지자!
int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Archer* archer = new Archer(new Pet());
	archer->_hp = 100;
	archer->_maxHp = 100;
	archer->_attack = 20;

	Knight* knight = new Knight();	
	knight->_hp = 150;
	knight->_maxHp = 150;
	knight->_attack = 100;
	
	int damage = knight->GetAttackDamage();
	archer->AddHp(-damage);

	delete archer;
	delete knight;
}
