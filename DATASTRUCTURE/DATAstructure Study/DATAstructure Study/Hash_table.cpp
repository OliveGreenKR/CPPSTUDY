#if 0
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>


//'테이블'
void TestTable()
{
	struct User
	{
		int userid = 0; //1~999
		string username;
	};

	vector<User> users;
	users.resize(1000);

	//777번 유저 세팅
	users[777] = User{ 777,"ID" };
	//777유저의 이름은?
	string name = users[777].username;
}
//'해시' 테이블
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

	//123456789번 유저 세팅
	int key = (userid) % 1000; // hash < 고유번호 추출
	users[key] = User{ userid, "ID" };

	//userid유저의 이름은?
	User& user = users[key];
	if (user.userid == userid)
	{
		string name = user.username;
	}
}

//해시 테이블 + 체이닝
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

	//123456789번 유저 세팅
	//해시함수
	int key = (userid) % 1000; // hash < 고유번호 추출
	users[key].push_back( User{ userid, "ID" });

	//userid 유저의 이름은?
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
