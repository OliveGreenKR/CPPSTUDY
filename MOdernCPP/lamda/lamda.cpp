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
	//�ӽð��� �ѱ�� �ű� ������ push back�� �������� �޴� �Լ��� ȣ���
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
	//		auto ResetHPJob() //�Լ� ��ü�� ��ȯ
	//		{
	//			auto f = [=]()  //�̷���� ����� [this]�� ����.
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
	//	job(); //job��this�� �̹� �����Ͱ� ���� ����, ������ ����!!!

	//}

	

	return 0;
}
#endif // 1
