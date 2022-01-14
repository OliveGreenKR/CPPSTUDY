#include <iostream>
using namespace std;

class Knight
{
public:
	int _hp = 100;
	
	//대입연산자 금지
	void operator=(const Knight& knight) = delete;
};
#if 0

int main()
{
	return 0;
}

#endif // 1
