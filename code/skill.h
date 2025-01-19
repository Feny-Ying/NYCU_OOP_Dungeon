#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>

using namespace std;

class SKILL
{
public:
	SKILL(string name_, string depict_, double newindex, int magicost) { name = name_; depict = depict_; index = newindex; this->magicost = magicost; }
	string getdepict()
	{
		return depict;
	}
	string getname()
	{
		return name;
	}
	double getindex()
	{
		return index;
	}
	int getmagicost()
	{
		return magicost;
	}
private:
	string name;
	string depict;
	double index;
	int magicost;
};

SKILL allskill[7] = { SKILL("�L","�L",0,0),SKILL("�P�K�s����","�����x�����ۡA�A��W�r�ƻs�L�ӥΦӤw�C�ϥμQ�O�`�N�ĤH",1.1,5),SKILL("���_�ۼQ�g","�̫᪺���_�ۼQ�g�A�����A��ʰ|�C�V�Ĥ��A��������",1.4,5), SKILL("�^������","�ڷQ�����^�����A�A������a�c���I��A���ɥ��O���@��",1.8,15), SKILL("�L�q�ųB","�鮩��Ĩc�̨��I�R���·t�A�A���\����a�a�c�Ŷ�",1.8,20), SKILL("I am atomic","�^�W��v �D������v�����A���y��v���H�K�K",2,25),SKILL("�i�̤���","�i�����A�o��F�@�̪��q��0970228136",0,0) };
#endif 
