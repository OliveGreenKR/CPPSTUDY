#include "Archer.h"
#include "Pet.h"
#include <iostream>
using namespace std;

Archer::Archer()
{
	// �̷� ���� ���� ä�� ����~
	_pet = new Pet();
}

Archer::Archer(int hp) : Player(hp)
{
	// �̷� ���� ���� ä�� ����~
	_pet = new Pet();
}

Archer::~Archer()
{
	// ��ſ��� �� �� :(
	if (_pet != nullptr)
		delete _pet;
	cout << "~Acchor()" << endl;

}

