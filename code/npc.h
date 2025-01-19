
#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>
#include<vector>
#include"item.h"
#include"armor.h"

using namespace std;

class NPC {
public:
	string getname() {
		return name;
	}
	NPC(string name, int index) : name(name), index(index) {}
	NPC() : name("no"), index(0) {}
	virtual vector<Armor>& getshopArmor() = 0;
	virtual vector<Item>& getshopitem() = 0;
	int getindex() {
		return index;
	}

protected:
	string name;
	int index;
	vector<Armor> shopArmor;
	vector<Item> shopitem;
};

class armorNPC :public NPC {
public:
	armorNPC(string name, Armor a1, Armor a2, Armor a3) : NPC(name, 1) {
		shopArmor.push_back(a1);
		shopArmor.push_back(a2);
		shopArmor.push_back(a3);
	}
	vector<Armor>& getshopArmor() override {
		return shopArmor;
	}
	vector<Item>& getshopitem() override {
		return shopitem;
	}
};

vector<armorNPC> AllarmorNPC = { armorNPC("»A¶·",headArmor[1],bodyArmor[1],feetArmor[1]),armorNPC("ªî¥²ª®",headArmor[2],bodyArmor[2],feetArmor[2]) };

class ItemNPC :public NPC {
public:
	ItemNPC(string name, Item I1, Item I2, Item I3) : NPC(name, 2) {
		shopitem.push_back(I1);
		shopitem.push_back(I2);
		shopitem.push_back(I3);
	}
	vector<Item>& getshopitem() override {
		return shopitem;
	}
	vector<Armor>& getshopArmor() override {
		return shopArmor;
	}
};

vector<ItemNPC> AllItemNPC = { ItemNPC("ºÑ¦±",allItem[0],allItem[8],allItem[6]),ItemNPC("ºû¥§",allItem[3],allItem[7],allItem[9]) };
#endif
