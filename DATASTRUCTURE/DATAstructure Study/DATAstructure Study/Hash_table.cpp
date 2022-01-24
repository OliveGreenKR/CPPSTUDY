#if 0
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>


//'���̺�'
void TestTable()
{
	struct User
	{
		int userid = 0; //1~999
		string username;
	};

	vector<User> users;
	users.resize(1000);

	//777�� ���� ����
	users[777] = User{ 777,"ID" };
	//777������ �̸���?
	string name = users[777].username;
}
//'�ؽ�' ���̺�
void TestHash()
{
	struct User
	{
		int userid = 0; //1~int32_MAX
		string username;
	};

	vector<User> users;
	users.resize(1000);

	const int userid = 123456789;

	//123456789�� ���� ����
	int key = (userid) % 1000; // hash < ������ȣ ����
	users[key] = User{ userid, "ID" };

	//userid������ �̸���?
	User& user = users[key];
	if (user.userid == userid)
	{
		string name = user.username;
	}
}

//�ؽ� ���̺� + ü�̴�
void TestHashTableChaining()
{
	struct User
	{
		int userid = 0; //1~int32_MAX
		string username;
	};



	vector<vector<User>> users;
	users.resize(1000);

	const int userid = 123456789;

	//123456789�� ���� ����
	//�ؽ��Լ�
	int key = (userid) % 1000; // hash < ������ȣ ����
	users[key].push_back( User{ userid, "ID" });

	//userid ������ �̸���?
	vector<User>& bucket = users[key];
	
	for (User& user : bucket)
	{
		if (user.userid == userid)
		{
			string username = user.username;
		}
	}
}

int main()
{
}
#endif // 1
