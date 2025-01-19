
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>
#include<vector>
#include"item.h"
#include"armor.h"
#include"skill.h"
#include"gotoxy.h"


using namespace std;

class Player
{
public:

	int getLevel()
	{
		return Level;
	}
	string getName()
	{
		return name;
	}
	int getGold() {
		return gold;
	}
	int getHP()
	{
		return HP;
	}
	int getMP()
	{
		return MP;
	}
	int getATK()
	{
		return ATK;
	}
	int getDEF()
	{
		return DEF;
	}
	int getLUK()
	{
		return LUK;
	}
	int getAGI()
	{
		return AGI;
	}
	int getnowHP() {
		return nowHP;
	}
	int getnowMP() {
		return nowMP;
	}
	int getnowEXP()
	{
		return nowEXP;
	}
	int getEXP() {
		return EXP;
	}
	int getx()
	{
		return x;
	}
	int getlastx()
	{
		return lastx;
	}
	int gety()
	{
		return y;
	}
	int getlasty()
	{
		return lasty;
	}
	int gethunger()
	{
		return hunger;
	}
	int getthirsty()
	{
		return thirsty;
	}
	int getpoison()
	{
		return poison;
	}
	void setnowHP(int value)
	{
		nowHP += value;
		if (nowHP > HP)
		{
			nowHP = HP;
		}
		if (nowHP <= 0)
		{
			nowHP = 0;
		}
	}
	void setHP()
	{
		HP = (Level - 1) * 10 + 20;
	}
	void setnowMP(int value)
	{
		nowMP += value;
		if (nowMP > MP)
		{
			nowMP = MP;
		}
		if (nowMP <= 0)
		{
			nowMP = 0;
		}
	}
	void setMP()
	{
		MP = (Level - 1) * 5 + 8;
	}
	void setnowEXP(int value)
	{
		nowEXP += value;
	}
	void setEXP()
	{
		EXP = EXP + 20;
		ATK = ATK + 5;
		HP = HP + 20;
		DEF = DEF + 5;
		AGI = AGI + 5;
		if (AGI >= 50)
		{
			AGI = 50;
		}
		MP = MP + 6;
		LUK = LUK + 5;
		if (LUK >= 50)
		{
			LUK = 50;
		}
	}
	void setarmorcharacter(int part, int newatk, int newdef, int newagi, int newluk)
	{
		ATK = ATK - armor[part].getatk() + newatk;
		DEF = DEF - armor[part].getdef() + newdef;
		AGI = AGI - armor[part].getagi() + newagi;
		LUK = LUK - armor[part].getluk() + newluk;
	}
	void levelup()
	{
		srand(time(NULL));
		int randomnb;
		Level += 1;
		if (Level == 5)
		{
			randomnb = rand();
			if (randomnb % 2 == 0)
			{
				skill1 = allskill[1];
				system("cls");
				gotoxy(0, 15); cout << "                                           你學習到了新技能[烈焰龍捲風]";
				Sleep(2500);
			}
			else
			{
				skill1 = allskill[2];
				system("cls");
				gotoxy(0, 15); cout << "                                           你學習到了新技能[綠寶石噴射]";
				Sleep(2500);
			}
		}
		if (Level == 10)
		{
			randomnb = rand();
			if (randomnb % 10 < 4)
			{
				skill2 = allskill[3];
				system("cls");
				gotoxy(0, 15); cout << "                                            你學習到了新技能[英雄憧憬]";
				Sleep(2500);
			}
			else if (randomnb % 10 >= 4 && randomnb % 10 < 8)
			{
				skill2 = allskill[4];
				system("cls");
				gotoxy(0, 15); cout << "                                            你學習到了新技能[無量空處]";
				Sleep(2500);
			}
			else
			{
				skill2 = allskill[5];
				system("cls");
				gotoxy(0, 15); cout << "                                            你學習到了新技能[I am atomic]";
				Sleep(2500);
			}
		}
	}
	void setgold(int value)
	{
		gold += value;
	}
	void setlocation(int x, int y)
	{
		this->x += x;
		this->y += y;
	}
	void setx(int value)
	{
		this->x = value;
	}
	void sety(int value)
	{
		this->y = value;
	}
	void sethunger(int value)
	{
		this->hunger += value;
		if (this->hunger > 100)
		{
			this->hunger = 100;
		}
		if (this->hunger < 0)
		{
			this->hunger = 0;
		}
	}
	void setthirsty(int value)
	{
		this->thirsty += value;
		if (this->thirsty > 100)
		{
			this->thirsty = 100;
		}
		if (this->thirsty < 0)
		{
			this->thirsty = 0;
		}
	}
	void setpoison(int value)
	{
		this->poison = value;
	}
	void setlastposition()
	{
		lastx = x;
		lasty = y;
	}
	SKILL getskill1()
	{
		return skill1;
	}
	SKILL getskill2()
	{
		return skill2;
	}
	SKILL getownskill()
	{
		return ownskill;
	}
	Player(string name_) { name = name_; }
	vector<Armor> armor = { headArmor[0],bodyArmor[0],feetArmor[0] };
	vector<Item> item = {};

private:
	string name;
	int Level = 1;
	int nowHP = 10;
	int nowMP = 30;
	int HP = 999;
	int MP = 30;
	int ATK = 20;
	int DEF = 20;
	int LUK = 10;
	int AGI = 15;
	int gold = 1000;
	int nowEXP = 0;
	int EXP = 100;
	int x = 0;
	int lastx = 0;
	int y = 0;
	int lasty = 0;
	int hunger = 100;
	int thirsty = 100;
	int poison = 0;
	SKILL skill1 = allskill[0];
	SKILL skill2 = allskill[0];
	SKILL ownskill = allskill[6];
};

#endif
