#include "Archer.h"
#include "Pet.h"

Archer::Archer(Pet* pet) : _pet(pet)
{
	
}

Archer::Archer(int hp) : Player(hp), _pet(nullptr)
{
}

Archer::~Archer()
{
	if(_pet != nullptr)
	{
		delete _pet;
	}
	
}

void Archer::AddHp(int value)
{
	Player::AddHp(value);

	// �׾����� �굵 ������
	if (IsDead())
	{
		delete _pet;
		_pet = nullptr;
	}
}
