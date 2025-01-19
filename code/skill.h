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

SKILL allskill[7] = { SKILL("無","無",0,0),SKILL("烈焰龍捲風","豪炎寺的絕招，你把名字複製過來用而已。使用噴燈灼燒敵人",1.1,5),SKILL("綠寶石噴射","最後的綠寶石噴射，嗚嗚嗚嗚，花京院。向敵方丟你的尿結石",1.4,5), SKILL("英雄憧憬","夢想成為英雄的你，接受到地牢的呼喚，極盡全力的一擊",1.8,15), SKILL("無量空處","體悟到第牢裡那寂靜的黑暗，你成功能操縱地牢空間",1.8,20), SKILL("I am atomic","吾名闇影 乃潛伏於闇影之中，狩獵闇影之人……",2,25),SKILL("勇者之心","勇敢的你得到了作者的電話0970228136",0,0) };
#endif 
