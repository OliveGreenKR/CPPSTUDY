#include <iostream>
using namespace std;
#include "Knight.h"
#include "Archer.h"
#include "Mage.h"
#include "Pet.h"
#include "Arrow.h"

// [Bug Report #10]
// 궁수라며면 자고로 화살을 쏴야겠죠.
// Arrow는 자신을 목표 대상물을 target으로 관리하고
// Arrow를 만들 때 설정한 데미지 만큼 target의 체력을 깎습니다.
// 테스트를 위해 화살 10개를 생성해서 기사를 피격했는데...
// C++이 늘 그렇지만 되는 일이 없고 또 크래시가 납니다.
// 뭐가 문제일까요?

//이미 타겟이 기사의 주소로 들어가있음
//기사가 죽은 후 기사를 삭제시키면 
//이전에 타켓에 대한 주소를 넣었기때문에
//화살은 기사였던 것의 주소를(유효하지 않은 데이터를 가지고있는 주소값) 
//향해 화살의 공격이 발동됨.

//공격을 하기위해서 타겟에 접근하여 체력과, 정보를 출력해야하는데
//접근한 데이터가 이미 delete되어 유효하지 않은 데이터 이다.
// PrintInfo는 가상함수 이기 때문에, 테이블을 통해 올바른 자신의 class를 찾던 중에
//오류가 생긴다. 
//(만약 이게 없었으면, 데이터만 수정하는 AddHp는 계속해서 데이터를 오염했을 것)

//-->기사가 죽으면 공격행위를 멈추게함.
//-->또는 기사의 삭제를 미룸.

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
	knight->_attack = 10;
	
	Arrow* arrows[10] = {};
	for (int i = 0; i < 10; i++)
	{
		// 기사를 타겟으로, 궁수의 공격력을 지닌 상태
		Arrow* arrow = new Arrow(knight, archer->_attack);
		arrows[i] = arrow;
	}

	for (int i = 0; i < 10; i++)
	{
		arrows[i]->AttackTarget();

		// 기사가 죽었으면 소멸시켜준다
		if (knight != nullptr)
		{
			if (knight->IsDead())
			{
				delete knight;
				knight = nullptr;
				break;
			}
		}
	
		delete arrows[i];
		arrows[i] = nullptr;
	}

	//방법2. 미루는 방법
	//delete archer;
	//delete knight;
}
