
#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>
#include<time.h>
#include"gotoxy.h";
#include"player.h"

using namespace std;

class Enemy
{
public:
	void getdetail()
	{

		gotoxy(70, 3);      cout << "  _________________________________  ";
		gotoxy(70, 4);      cout << " |       " << getname() << "     | ";
		gotoxy(70, 5);      cout << " |---------------------------------| ";
		gotoxy(70, 6);      cout << " |  HP:" << getHP() << "                      | ";
		gotoxy(70, 7);      cout << " |  ATK:" << getATK() << "  " << "DEF:" << getDEF() << "     |";
		gotoxy(70, 8);      cout << " |_________________________________| ";

	}
	string getname()
	{
		return name;
	}
	int getATK()
	{
		return ATK;
	}
	int getHP()
	{
		return HP;
	}
	int getnowHP()
	{
		return nowHP;
	}
	int getDEF()
	{
		return DEF;
	}
	void getdamage(int value)
	{
		nowHP -= value;
		if (nowHP <= 0)
		{
			nowHP = 0;
		}
	}
	void setnowHP()
	{
		this->nowHP = HP;
	}
	Enemy() {
		name = "no";
		HP = 0;
		nowHP = 0;
		ATK = 0;
		DEF = 0;
	};
	virtual void attack(Player* player) = 0;
protected:
	string name;
	int HP;
	int nowHP;
	int ATK;
	int DEF;

};
class Dragon :public Enemy
{
public:
	Dragon() {
		name = "Dragon";
		HP = 80;
		nowHP = 80;
		ATK = 20;
		DEF = 15;
	}
	void attack(Player* player)
	{
		if (getATK() - player->getDEF() <= 0)
		{
			cout << "�a�c���s�����A�y���F1�I�ˮ`";
			player->setnowHP(-1);
		}
		else
		{
			cout << "�a�c���s�����A�y���F" << getATK() - player->getDEF() << "�I�ˮ`";
			player->setnowHP(-(getATK() - player->getDEF()));
		}

	}
};
class Slime :public Enemy
{
public:
	Slime() {
		name = "Slime";
		HP = 20;
		nowHP = 20;
		ATK = 3;
		DEF = 3;
	}
	void attack(Player* player)
	{
		if (getATK() - player->getDEF() <= 0)
		{
			cout << "�v�ܩi�����A�y���F1�I�ˮ`";
			player->setnowHP(-1);
		}
		else
		{
			cout << "�v�ܩi�����A�y���F" << getATK() - player->getDEF() << "�I�ˮ`";
			player->setnowHP(-(getATK() - player->getDEF()));
		}
	}
};
class Devil :public Enemy
{
public:
	Devil() {
		name = "Devil";
		HP = 35;
		nowHP = 35;
		ATK = 10;
		DEF = 5;
	}
	void attack(Player* player)
	{
		if (getATK() - player->getDEF() <= 0)
		{
			cout << "�c�]�����A�y���F1�I�ˮ`";
			player->setnowHP(-1);
		}
		else
		{
			cout << "�c�]�����A�y���F" << getATK() - player->getDEF() << "�I�ˮ`";
			player->setnowHP(-(getATK() - player->getDEF()));
		}
	}
};
class Ghost :public Enemy
{
public:
	Ghost() {
		name = "Ghost";
		HP = 25;
		nowHP = 25;
		ATK = 6;
		DEF = 5;
	}
	void attack(Player* player)
	{
		srand(time(NULL));
		int randomnb;
		if (getATK() - player->getDEF() <= 0)
		{
			cout << "�a�c�`�F�����A�y���F1�I�ˮ`";
			player->setnowHP(-1);
		}
		else
		{
			cout << "�a�c�`�F�����A�y���F" << getATK() - player->getDEF() << "�I�ˮ`";
			player->setnowHP(-(getATK() - player->getDEF()));
		}
		randomnb = rand();
		if (randomnb % 100 <= 20)
		{
			if (player->getpoison() == 1 || player->getpoison() == 3)
			{
				player->setpoison(3);
			}
			else
			{
				player->setpoison(2);
			}
			cout << "�åB�`���������A";
		}
	}
};
class Gobulin : public Enemy
{
public:
	Gobulin() {
		name = "Gobulin";
		HP = 25;
		nowHP = 25;
		ATK = 6;
		DEF = 2;
	}

	void attack(Player* player)
	{
		if (getATK() - player->getDEF() <= 0)
		{
			cout << "�����L�����A�y���F1�I�ˮ`";
			player->setnowHP(-1);
		}
		else
		{
			cout << "�����L�����A�y���F" << getATK() - player->getDEF() << "�I�ˮ`";
			player->setnowHP(-(getATK() - player->getDEF()));
		}
	}
};
class Boss :public Enemy
{
public:
	Boss()
	{
		name = "�a�c���D";
		HP = 500;
		nowHP = 500;
		ATK = 30;
		DEF = 30;
	}
	void attack(Player* player)
	{
		if (getATK() - player->getDEF() <= 0)
		{
			cout << "�a�c���D�����A�y���F1�I�ˮ`";
			player->setnowHP(-1);
		}
		else
		{
			cout << "�a�c���D�����A�y���F" << getATK() - player->getDEF() << "�I�ˮ`";
			player->setnowHP(-(getATK() - player->getDEF()));
		}

	}
	void skill1atk(Player* player)
	{
		cout << "�a�c���D�ϥΤ`�F�Һ������A�y���F" << player->getHP() * 0.05 << "�I�ˮ`" << endl;
		player->setnowHP(-(player->getHP() * 0.05));
	}
	void skill2atk(Player* player)
	{
		cout << "�a�c���D�ϥΦ��`�Į������A�y���F" << player->getHP() * 0.1 << "�I�ˮ`" << endl;
		player->setnowHP(-(player->getHP() * 0.1));
	}

};
Boss* finalboss = new Boss();

#endif
