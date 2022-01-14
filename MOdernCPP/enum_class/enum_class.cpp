#include <iostream>
using namespace std;


enum PlayerType :  char //data type지정
{
	PT_Knight,
	PT_Archer
};
// 기본적으로 int 로 사용된다.


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
