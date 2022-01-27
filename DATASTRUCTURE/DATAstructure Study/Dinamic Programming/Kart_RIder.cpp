#if 0

#include <vector>
#include <iostream>
#include<algorithm>
#include<queue>

using namespace std;

/*
 * ������Ȳ
 * īƮ�� ������ �����ϸ� �޸��� ����, T�� ���� �޸���.
 * ó�� �̵��ӵ�, �⺻ �̵��ӵ��� 1m/s
 * 
 * ������ ���۵ǰ� Ư�� �ð�(a)�� �Ǹ�, �ٴڿ� �Ź� �������� �����ȴ�.
 * īƮ�� �Ź��� �Űų�, ����ĥ �� �ִ�. ������ �Ź��� ���� �ٽ� �ֿ� �� ����.
 * 
 * �Ź��� �����Ϸ���, (b)�� �ð��� �ʿ��ϴ�. ��  b�� ���� ���ڸ����� ���߾�� ������ �� �ִ�.
 * 
 * �Ź��� �����ϸ� �����ð�(C) ���� �Ź� �ӵ�(d)�� �޸� �� �ִ�.
 * �Ź��� �ϳ��� ������ �� �ְ�, ���� �ֱ� ������ �Ź��� �ӵ��� ����ȴ�.
 * �Ź��� ���ų� �ٸ� �Ź߷� �ٲ� ������ �� �߰��ð��� ���� �ʴ´�. (���ο� �Ź��� �Ŵ� �ð��� �ҿ� �ȴ�.)
 * 
 * �Ź� ȿ���� ������, �ٽ� �⺻ �̵��ӵ� 1m/s�� �޸���.
 * 
 * �Ź��� �Ŵµ��� �ٸ� �Ź��� ���� ���� ����.
 * 
 * Q) �����Ǵ� ��� �Ź� ������ �־����� ��, T�ʵ��� �� �� �ִ� �ִ� �Ÿ��� ���϶�.
 */


/*input.txt
 * T : 20
 * �Ź߰��� : 4
 *          a b  c d
 * �Ź�1 :	3 4 10 3
 * �Ź�2 :	4 1 4 2
 * �Ź�3 :	10 2 5 5 
 * �Ź�4 :	15 1 3 7
 */



//�����ذ� �����غ���
/*
#2. �Ź� ������
(a,b,c,d) 4���� �Ӽ��� ������ �־����

#3. �̵��Ÿ� ����� ���� ������ ����ϰ�, �ִ� �Ÿ��� ����� ã�ƾ���.


*/

struct Shoe
{
	Shoe(int a, int b, int c, int d)
	{
		time = a;
		start = a + b;
		end = a + b + c;
		speed = d;
	}
	int time; // �����Ǵ� �ð�
	int start;// �Ź� ȿ�� ���۽ð�
	int end; // �Ź� ȿ�� �� �ð�
	int speed; // �ӵ�
};

vector<Shoe> shoes; //�Ź߾����� ����

int T; //�� �̵��ð�.

vector<int>cache; //cahce[time]�� time���� ���� �ִ� �̵��Ÿ�

//now�� �Ź��� �Ű� �� �� �ִ� �ִ� �Ÿ��� ��ȯ.!!
//��, �Ź��� "�ű� ��" ���� �������!
int Solve(int now)
{
//��������
	if (now >= shoes.size())
		return 0;

//ĳ��Ȯ��
	int& ret = cache[now];

	if (ret != -1)
		return ret;

//���
	Shoe& shoe = shoes[now];

	//�Ź߽Ű� �̵��� �Ÿ� + �ɾ �̵��� �Ÿ�
	int dist = (shoe.end - shoe.start) * shoe.speed + (T - shoe.end) * 1;
	ret = max(ret,dist);

	//�ٸ� �Ź��� ��������, �� ���� ���� ����.
	for (int next = now + 1; next < shoes.size(); next++)
	{
		Shoe& nextshoe = shoes[next];
		if (nextshoe.time < shoe.start)//�Ŵµ��߿� �����ϴ� �Ź��̸� ���� �� ����
			continue;

		//���� �Ź߱����� �̵��� �Ÿ�
		int moveDist = 0;

		//���� �Ź� ȿ���� ������ ���� ���� �Ź� ����
		if (nextshoe.time <= shoe.end)
		{
			moveDist = (nextshoe.time - shoe.start) * shoe.speed;
		}
		else
		{
			moveDist = (shoe.end - shoe.start) * shoe.speed + (nextshoe.time - shoe.end) * 1;
		}
		ret = max(ret, moveDist + Solve(next));
	}
	return ret;
}

int main()
{
	T = 20;

	//shoe push back'
	shoes.push_back(Shoe{ 0,0,T,1 });
	shoes.push_back(Shoe{ 3,4,10,3 });
	shoes.push_back(Shoe{ 4,1,4,2 });
	shoes.push_back(Shoe{ 10,2,5,5 });
	shoes.push_back(Shoe{ 15,1,3,7 });

	//shoe ���� start�ð��� ���� ������ ����
	::sort(shoes.begin(), shoes.end(), [=](Shoe& shoe1, Shoe& shoe2) {return shoe1.time < shoe2.time ; });
	cache = vector<int>(shoes.size(), -1);

	int answer = Solve(0);

	cout << answer << endl;
}


#endif // 1
