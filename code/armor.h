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

 Armor headArmor[3] = {  Armor("��ߪ��Y��","���q���w���U",2,5,2,0,50), Armor("�����h�Y��","���Өk�H���g�������Y��",5,10,5,0,150),  Armor("�a�c���D�Y��","��O�����w���U",7,13,10,0,500) };
 Armor bodyArmor[3] = {  Armor("��ߪ̲���","�ίȽc��������",5,10,2,0,100), Armor("�����h����","���Өk�H���g����������",8,15,2,0,300),  Armor("�a�c���D����","��O�����~�M",10,20,5,0,999) };
 Armor feetArmor[3] = {  Armor("��ߪ̾c�l","��F�@�~���c�l",1,3,2,10,40), Armor("�����h�c�l","���Өk�H���g�������c�l",2,7,5,15,120),  Armor("�a�c���D�c�l","��O�����c�l",5,10,8,0,400) };

#endif