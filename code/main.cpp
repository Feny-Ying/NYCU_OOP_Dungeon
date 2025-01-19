#include <iostream>
#include<fcntl.h>
#include <ctime>
#include<process.h>
#include <cstdlib> 
#include <cmath>
#include <chrono>
#include <list> 
#include <conio.h> 
#include <windows.h> 
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <vector>
#include <iomanip>
#include<time.h>

#include"item.h"
#include"armor.h"
#include"skill.h"
#include"gotoxy.h"
#include"room.h"
#include"enemy.h"
#include"npc.h"
#include"player.h"
#include"dungeon.h"
using namespace std;




int main()
{
	Dungeon dungeon = Dungeon();
	dungeon.startgame();
	return 0;
}
