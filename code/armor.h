#ifndef ARMOR_H
#define ARMOR_H

#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>

using namespace std;

class Armor
{
public:
	string getdetail()
	{
		return depict;
	}
	string getname()
	{
		return name;
	}
	int getcost()
	{
		return cost;
	}
	int getatk()
	{
		return ATK;
	}
	int getdef()
	{
		return DEF;
	}
	int getagi()
	{
		return AGI;
	}
	int getluk()
	{
		return LUK;
	}
	Armor(string name_, string depict_, int ATK_, int DEF_, int LUK_, int AGI_, int cost) { name = name_; depict = depict_; ATK = ATK_; DEF = DEF_; LUK = LUK_; AGI = AGI_; this->cost = cost; };
private:
	string name;
	string depict;
	int ATK;
	int DEF;
	int LUK;
	int AGI;
	int cost;

};

 Armor headArmor[3] = {  Armor("初心者頭盔","普通的安全帽",2,5,2,0,50), Armor("角鬥士頭盔","那個男人曾經穿戴的頭盔",5,10,5,0,150),  Armor("地牢之主頭盔","詹力偉的安全帽",7,13,10,0,500) };
 Armor bodyArmor[3] = {  Armor("初心者盔甲","用紙箱做的盔甲",5,10,2,0,100), Armor("角鬥士盔甲","那個男人曾經穿戴的盔甲",8,15,2,0,300),  Armor("地牢之主盔甲","詹力偉的外套",10,20,5,0,999) };
 Armor feetArmor[3] = {  Armor("初心者鞋子","穿了一年的鞋子",1,3,2,10,40), Armor("角鬥士鞋子","那個男人曾經穿戴的鞋子",2,7,5,15,120),  Armor("地牢之主鞋子","詹力偉的鞋子",5,10,8,0,400) };

#endif