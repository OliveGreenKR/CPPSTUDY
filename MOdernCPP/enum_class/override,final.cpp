#include <iostream>
using namespace std;

class Player
{
public:
	virtual void Attack() final
	{
		cout << "Player!" << endl;
	}
};

class Knight : public Player
{
public:
	virtual void Attack() override
	{
		cout << "Knight!" << endl;
	}
};
#if 1

int main()
{
	Player* player = new Knight();

	player->Attack(); 

	return 0;
}

#endif // 1
