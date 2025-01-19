#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>

using namespace std;


class Item
{
public:
	void getdetail()
	{
		cout << getname() << endl;
		cout << "____________________________________________________________________________________________________" << endl;
		cout << getdepict() << endl;

	}
	string getname()
	{
		return name;
	}
	string getdepict()
	{
		return depict;
	}
	string getcharacter()
	{
		return character;
	}
	int gethealth()
	{
		return health;
	}
	int getmagi()
	{
		return magi;
	}
	int getstack()
	{
		return stack;
	}
	void setstack(int value)
	{
		stack += value;
	}
	int getcost()
	{
		return cost;
	}
	int getaddhunger()
	{
		return addhunger;
	}
	int getaddthirsty()
	{
		return addthirsty;
	}
	Item(string name_, string depict_, string character_, int health_, int magi_, int cost, int hunger, int thirsty) { name = name_; depict = depict_; character = character_; health = health_; magi = magi_; this->cost = cost; addhunger = hunger; addthirsty = thirsty; }
private:
	string name;
	string depict;
	string character;
	int health;
	int magi;
	int attack;
	int addhunger;
	int addthirsty;
	int stack = 0;
	int cost;
};
Item allItem[10] = { Item("哥布林水袋","哥布林部落使用的水袋，使用可恢復水分","水分",0,0,20,0,30),Item("龍肉","地牢屍龍的肉，即使腐敗了但還是可以補充飢餓值","食物",0,0,50,30,0) ,Item("史萊姆黏液","具有魔力的黏液，聽說可以溶解女性的衣物，使用後可回復魔力","回魔",0,10,50,0,0) ,Item("惡魔獠牙","住在地牢中惡魔的獠牙，似乎只能來當裝飾?","裝飾",0,0,100,0,0) ,Item("幽靈寒氣","似乎能降低周圍溫度，地球有救了!!","無用",0,0,125,0,0) ,Item("龍之血珠","龍族經年累月後誕生在體內的寶珠，使用後可以回血","回血",75,0,250,0,0) ,Item("不知名的藥草","不知何處的藥草，雖然很難吃但似乎有奇效","回復",25,10,75,0,0) ,Item("可愛小蘿莉的內褲","不知道為什麼地牢裡有這個東西","香阿",0,0,500,0,0) ,Item("詹力偉的OOP課程","交通大學的至寶，希望教授能幫我加分","??",0,0,999,0,0) ,Item("交大學餐","雖然不難吃但也沒也好吃到哪裡去，吃了可以回復飢餓值跟水分並有解毒效果","回復",0,0,80,50,50) };

#endif