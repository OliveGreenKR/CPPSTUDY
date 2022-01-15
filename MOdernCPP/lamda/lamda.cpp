#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


enum class ItemType
{
	None,
	Armor,
	Weapon,
	Jewelry,
	Comsumable
};


enum class Rarity
{
	Common,
	Rare,
	Unique
};

class Item
{
public:
	Item(){}
	Item(int itemid, Rarity rarity, ItemType itemtype) : 
	_itemid(itemid),
	_rarity(rarity),
	_itemtype(itemtype)
	{}

public:
	int _itemid = 0;
	Rarity _rarity = Rarity::Common;
	ItemType _itemtype = ItemType::None;
};

#if 1
int main()
{
	vector<Item> v;
	//임시값을 넘기는 거기 때문에 push back은 오른값을 받는 함수가 호출됨
	v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
	v.push_back(Item(2, Rarity::Common, ItemType::Armor));
	v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
	v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));

	auto isJewelryLamda = [](Item& item) 
	{
		return (item._itemtype == ItemType::Jewelry); 
	};

	struct FindByItemType
	{
		FindByItemType(ItemType itemtype) : 
			_itemtype(itemtype)
		{}

		bool operator()(Item& item)
		{
			return item._itemtype == _itemtype;
		}

	public:
		ItemType _itemtype;

	};

	ItemType ItemTypeval = ItemType::Jewelry;

	auto FindByItemLamda = 
	[&ItemTypeval](Item& item) 
	{
		return item._itemtype == ItemTypeval;
	};

	/*ItemTypeval = ItemType::Weapon;*/


	auto jewlyit = std::find_if(v.begin(), v.end(),isJewelryLamda);
	auto jewlyit2 = std::find_if(v.begin(), v.end(),FindByItemLamda);


	cout << jewlyit->_itemid << endl;
	cout << jewlyit2->_itemid << endl;


	//{
	//	class Knight
	//	{
	//	public:
	//		auto ResetHPJob() //함수 객체를 반환
	//		{
	//			auto f = [=]()  //이럴경우 사실은 [this]와 같다.
	//			{
	//				_hp = 200;
	//			};
	//			return f;
	//		}
	//	public:
	//		int _hp = 100;
	//	};

	//	Knight* k1 = new Knight();
	//	auto job = k1->ResetHPJob();

	//	delete k1;
	//	job(); //job의this는 이미 데이터가 날라간 상태, 데이터 오염!!!

	//}

	

	return 0;
}
#endif // 1
