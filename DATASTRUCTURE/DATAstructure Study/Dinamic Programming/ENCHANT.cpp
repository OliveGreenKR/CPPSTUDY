#if 0
#include <vector>
#include <iostream>
#include <map>
using namespace std;

//ENCHANT : 
/*
* ������Ȳ : 
* 
* ���� ��ȭ �ֹ����� ���� ��æƮ ���� -> +1/+2/+3 �� �������� ��ȭ��( ���д� ����)
* 
* +num �������� ��ǥ��ġ (+N)���� ���� ����� ���� ���Ͻÿ�
*/



int N;
vector<int> cache; //cache[n] =  0 ����~ n��ȭ����  ������ ����� ��
//1,2,3 =? 1,2,3 �ε�...

//���� ��ȭ��ġ num �϶� N������ ����� ���� ���϶�
int Enchant(vector<int>& cache, int num)
{
	int enchant = N - num;

	//������Ȳ
	if (enchant < 0 || enchant > N)
		return 0;

	int& ret = cache[enchant];
	if (enchant == 0)
		return ret = 1;

	//ĳ��üũ
	if (ret != 0)
		return ret;

	else
	{
		return ret = Enchant(cache, num + 1) + Enchant(cache, num + 2) + Enchant(cache, num + 3);
	}


}

int main()
{
	cache = vector<int>(50, 0);

	N = 20;

	int ans = Enchant(cache, 0);
	
	cout << ans << endl;

}
#endif // 1
