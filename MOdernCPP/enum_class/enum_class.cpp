#include <iostream>
using namespace std;


enum PlayerType :  char //data type����
{
	PT_Knight,
	PT_Archer
};
// �⺻������ int �� ���ȴ�.


enum class ObjectType
{
	Player,
	Knight,
	Archer,
};

enum class ObjectType2
{
	Player,
	Knight,
	Archer,
};


#if 0
int main()
{
	double Val1 = PT_Knight;
	double Val2 = static_cast<double>(ObjectType::Knight);

	size_t bitFlag;
	bitFlag << PT_Knight;
	bitFlag << static_cast<int>(ObjectType::Player);



}
#endif // 1
