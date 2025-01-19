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
Item allItem[10] = { Item("�����L���U","�����L�����ϥΪ����U�A�ϥΥi��_����","����",0,0,20,0,30),Item("�s��","�a�c���s���סA�Y�ϻG�ѤF���٬O�i�H�ɥR���j��","����",0,0,50,30,0) ,Item("�v�ܩi�H�G","�㦳�]�O���H�G�Ať���i�H���Ѥk�ʪ��窫�A�ϥΫ�i�^�_�]�O","�^�]",0,10,50,0,0) ,Item("�c�]�y��","��b�a�c���c�]���y���A���G�u��ӷ�˹�?","�˹�",0,0,100,0,0) ,Item("���F�H��","���G�୰�C�P��ūסA�a�y���ϤF!!","�L��",0,0,125,0,0) ,Item("�s����]","�s�ڸg�~�֤��ϥͦb�餺���_�]�A�ϥΫ�i�H�^��","�^��",75,0,250,0,0) ,Item("�����W���į�","������B���į�A���M�����Y�����G���_��","�^�_",25,10,75,0,0) ,Item("�i�R�p�ڲ�������","�����D������a�c�̦��o�ӪF��","����",0,0,500,0,0) ,Item("��O����OOP�ҵ{","��q�j�Ǫ����_�A�Ʊ�б¯����ڥ[��","??",0,0,999,0,0) ,Item("��j���\","���M�����Y���]�S�]�n�Y����̥h�A�Y�F�i�H�^�_���j�ȸ�����æ��Ѭr�ĪG","�^�_",0,0,80,50,50) };

#endif