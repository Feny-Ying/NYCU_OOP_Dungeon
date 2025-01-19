
#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>
#include"enemy.h"
#include"npc.h"

using namespace std;

class Room
{
public:
	Room(int environment, Enemy* enemy)
	{
		this->environment = environment;
		this->enemy = enemy;
		this->npc = NULL;
	}
	Room(int environment, NPC* npc)
	{
		this->environment = environment;
		this->npc = npc;
		this->enemy = NULL;
	}
	Room(int environment)
	{
		this->environment = environment;
		this->enemy = NULL;
		this->npc = NULL;
	}
	Room()
	{
		environment = 0;
		this->enemy = NULL;
		this->npc = NULL;
	}
	int getEN()
	{
		return environment;
	}
	Enemy* getenemy()
	{
		return enemy;
	}
	NPC* getnpc()
	{
		return npc;
	}
private:
	int environment;
	Enemy* enemy;
	NPC* npc;
};

#endif
