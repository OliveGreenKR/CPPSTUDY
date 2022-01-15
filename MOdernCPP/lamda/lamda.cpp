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

	auto jewlyit = std::find_if(v.begin(), v.end(),isJewelryLamda);

	cout << jewlyit->_itemid << endl;

	return 0;
}
#endif // 1
