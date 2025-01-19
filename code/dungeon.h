#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include<fcntl.h>
#include<process.h>
#include <ctime>
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
#include"player.h"
#include"enemy.h"
#include"npc.h"


using namespace std;

void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

class Dungeon :public Room
{
private:
	vector<vector<Room>> dungen;
	Player* player1;

public:
	Dungeon()
	{
		string name;
		gotoxy(55, 15); cout << "請輸入你的名字:";
		cin >> name;
		player1 = new Player(name);
		dungen = { {Room(),Room(0,new Gobulin()),Room(0,&AllarmorNPC[0]),Room(1,new Slime()),Room(1,new Ghost())},{Room(3,&AllItemNPC[0]),Room(0,new Slime()),Room(),Room(1,new Devil()),Room(1)},{Room(3,new Gobulin()),Room(0,&AllarmorNPC[1]),Room(),Room(0,new Slime()),Room(0,new Dragon())},{Room(0,new Devil()),Room(2),Room(2,new Ghost()),Room(0,&AllItemNPC[1]),Room()},{Room(),Room(2,new Gobulin()),Room(2),Room(0,new Dragon()),Room(0,new Boss())} };

	}

	void startgame()
	{
		PlaySound(TEXT("開頭bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		preface();
		PlaySound(TEXT("walk.wav"), NULL, SND_FILENAME | SND_SYNC);
		procedure(player1);
		PlaySound(TEXT("結尾bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		ending();
	}

	bool retreatornot = 0;
	int* linepoint = new int(21);
	void map(Player* player)
	{
		gotoxy(0, 0);      cout << "  _____________________________________________________________________________________________________________________";
		gotoxy(0, 1);      cout << " |Lev." << player->getLevel() << "           " << "name:" << player->getName() << "                                                         "; gotoxy(95, 1); cout << " gold:" << player->getGold() << "    "; gotoxy(105, 1); cout << "     save"; gotoxy(119, 1); cout << "| ";
		gotoxy(0, 2);      cout << " |                                                                                                                     | ";
		gotoxy(0, 3);      cout << " |                                                                                                                     | ";
		gotoxy(0, 4);      cout << " |                                                                                                                     | ";
		gotoxy(0, 5);      cout << " |                                                                                                                     | ";
		gotoxy(0, 6);      cout << " |                                                                                                                     | ";
		gotoxy(0, 7);      cout << " |                                                                                                                     | ";
		gotoxy(0, 8);      cout << " |                                                                                                                     | ";
		gotoxy(0, 9);      cout << " |                                                                                                                     | ";
		gotoxy(0, 10);     cout << " |                                                                                                                     | ";
		gotoxy(0, 11);     cout << " |                                                                                                                     | ";
		gotoxy(0, 12);     cout << " |                                                                                                                     | ";
		gotoxy(0, 13);     cout << " |                                                                                                                     | ";
		gotoxy(0, 14);     cout << " |                                                                                                                     | ";
		gotoxy(0, 15);     cout << " |                                                                                                                     | ";
		gotoxy(0, 16);     cout << " |                                                                                                                     | ";
		gotoxy(0, 17);     cout << " |                                                                                                                     | ";
		gotoxy(0, 18);     cout << " |                                                                                                                     | ";
		gotoxy(0, 19);     cout << " |                                                                                                                     | ";
		gotoxy(0, 20);     cout << " |---------------------------------------------------------------------------------------------------------------------| ";
		gotoxy(0, 21);     cout << " | EXP:";
		SetColor(170);
		for (int h = 0; h < 20; h++)
		{
			if (h >= (float)player->getnowEXP() / ((float)player->getEXP() / 20))
			{
				SetColor();
			}
			cout << " ";
		}
		SetColor();
		cout << " " << player->getnowEXP() << "/" << player->getEXP();
		gotoxy(82, 21);
		cout << "|   HP:";
		//gotoxy(0, 21);     cout << " |                                                                                |   HP:";
		SetColor(204);
		for (int h = 0; h < 20; h++)
		{
			if (h >= (float)player->getnowHP() / ((float)player->getHP() / 20))
			{
				SetColor();
			}
			cout << " ";
		}
		SetColor();
		cout << " " << setw(3) << setfill(' ') << player->getnowHP() << "/" << setw(3) << setfill(' ') << player->getHP();
		gotoxy(119, 21);
		cout << "|";
		gotoxy(0, 22);     cout << " |";
		gotoxy(40, 22);    cout << "被動:" << player->getownskill().getname();
		gotoxy(82, 22); cout << "|   MP:";
		SetColor(17);
		for (int h = 0; h < 20; h++)
		{
			if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
			{
				SetColor();
			}
			cout << " ";
		}
		SetColor();
		cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
		gotoxy(119, 22);
		cout << "|";
		gotoxy(0, 23);     cout << " |                                                                                |                                    | ";
		gotoxy(0, 24);     cout << " |    裝備(請按g鍵)";
		gotoxy(40, 24);    cout << "技能一:" << player->getskill1().getname();
		gotoxy(82, 24);
		cout << "|"; cout << "   ATK: " << player->getATK(); gotoxy(101, 24); cout << "DEF : " << player->getDEF(); gotoxy(119, 24); cout << "|";
		gotoxy(0, 25);     cout << " |                                                                                |                                    | ";
		gotoxy(0, 26);     cout << " |    道具(請按h鍵)";
		gotoxy(40, 26);    cout << "技能二:" << player->getskill2().getname();
		gotoxy(82, 26);
		cout << "|"; cout << "   LUK: " << player->getLUK(); gotoxy(101, 26); cout << "AGI: " << player->getAGI(); gotoxy(119, 26); cout << "|";
		gotoxy(0, 27);     cout << " |                                      (檢視技能請按s鍵)                         |                                    | ";
		gotoxy(0, 28);     cout << " |________________________________________________________________________________|____________________________________| ";
		gotoxy(62, 22);
		cout << "飽食度:" << setw(3) << setfill('0') << player->gethunger() << "/100";
		gotoxy(62, 24);
		cout << "水分:" << setw(3) << setfill('0') << player->getthirsty() << "/100";
		gotoxy(62, 26);
		cout << "狀態:";
		if (player->getpoison() == 1)
		{
			cout << "中毒";
		}
		else if (player->getpoison() == 2)
		{
			cout << "失智";
		}
		else if (player->getpoison() == 3)
		{
			cout << "中毒+失智";
		}
		else if (player->getpoison() == 0)
		{
			cout << "無";
		}

	}
	void death(Player* player)
	{
		if (player->getnowHP() <= 0)
		{
			PlaySound(TEXT("死亡音效.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(0, 15);   cout << "                                   視線慢慢的模糊，你的生命到了盡頭永遠的沉眠在地下城中" << endl;
			Sleep(10000);
			exit(0);
		}
	}
	void showskill(Player* player)
	{
		system("cls");
		cout << "被動：" << player->getownskill().getname() << endl;
		cout << player->getownskill().getdepict() << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "技能一：" << player->getskill1().getname() << endl;
		cout << player->getskill1().getdepict() << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "技能二：" << player->getskill2().getname() << endl;
		cout << player->getskill2().getdepict() << endl;

	}
	void showitem(Player* player)
	{
		gotoxy(30, 3);      cout << "                                                             ";
		gotoxy(30, 4);      cout << "  |--------------------------------------------------------|  ";
		gotoxy(30, 5);      cout << "  |                                                        |  ";
		gotoxy(30, 6);      cout << "  |                                                        |  ";
		gotoxy(30, 7);      cout << "  |                                                        |  ";
		gotoxy(30, 8);      cout << "  |                                                        |  ";
		gotoxy(30, 9);      cout << "  |                                                        |  ";
		gotoxy(30, 10);     cout << "  |                                                        |  ";
		gotoxy(30, 11);     cout << "  |                                                        |  ";
		gotoxy(30, 12);     cout << "  |                                                        |  ";
		gotoxy(30, 13);     cout << "  |                                                        |  ";
		gotoxy(30, 14);     cout << "  |                                                        |  ";
		gotoxy(30, 15);     cout << "  |                                                        |  ";
		gotoxy(30, 16);     cout << "  |                                                        |  ";
		gotoxy(30, 17);     cout << "  |                                                        |  ";
		gotoxy(30, 18);     cout << "  |                                                        |  ";
		gotoxy(30, 19);     cout << "  |                                                        |  ";
		gotoxy(30, 20);     cout << "  |                                                        |  ";
		gotoxy(30, 21);     cout << "  |                                                        |  ";
		gotoxy(30, 22);     cout << "  |                                                        |  ";
		gotoxy(30, 23);     cout << "  |                                                        |  ";
		gotoxy(30, 24);     cout << "  |--------------------------------------------------------|  ";
		gotoxy(30, 25);     cout << "                                                              ";
		for (int i = 0; i < player->item.size(); i++)
		{
			gotoxy(33, 2 * i + 5); cout << "[" << i << "]|" << player->item[i].getname() << "|輸入" << i << "取得更詳細的資料"; gotoxy(80, 2 * i + 5); cout << "數量 | " << player->item[i].getstack() << " | ";
			gotoxy(30, 2 * i + 6); cout << "  |--------------------------------------------------------|  ";
		}
	}
	void showarmor(Player* player)
	{
		gotoxy(50, 4);      cout << "                                             ";
		gotoxy(50, 5);      cout << "   __________________________________________  ";
		gotoxy(50, 6);      cout << "  |" << player->armor[0].getname(); gotoxy(67, 6); cout << "|                      |頭部| ";
		gotoxy(50, 7);      cout << "  |------------------------------------------| ";
		gotoxy(50, 8);      cout << "  |" << player->armor[0].getdetail(); gotoxy(95, 8); cout << "| ";
		gotoxy(50, 9);      cout << "  |------------------------------------------| ";
		gotoxy(50, 10);     cout << "  |" << player->armor[1].getname(); gotoxy(67, 10); cout << "|                      |軀幹| ";
		gotoxy(50, 11);     cout << "  |------------------------------------------| ";
		gotoxy(50, 12);     cout << "  |" << player->armor[1].getdetail(); gotoxy(95, 12); cout << "| ";
		gotoxy(50, 13);     cout << "  |------------------------------------------| ";
		gotoxy(50, 14);     cout << "  |" << player->armor[2].getname(); gotoxy(67, 14); cout << "|                      |鞋子| ";
		gotoxy(50, 15);     cout << "  |------------------------------------------| ";
		gotoxy(50, 16);     cout << "  |" << player->armor[2].getdetail(); gotoxy(95, 16); cout << "| ";
		gotoxy(50, 17);     cout << "  |__________________________________________|  ";
		gotoxy(50, 18);      cout << "                                             ";
	}
	void linedetect(int* linepoint)
	{
		*linepoint += 1;
	}
	void preface()
	{
		system("cls");
		gotoxy(0, 10);   cout << "                                           我:我是誰?怎麼會躺在這裡?                                               ";
		Sleep(3000);
		gotoxy(0, 11);   cout << "                                       不知名的男人:我已經等候你多時了                                                              ";
		Sleep(3000);
		gotoxy(0, 12);   cout << "                                                   我:你是誰?                                                   ";
		Sleep(3000);
		gotoxy(0, 13);   cout << "                                       不知名的男人:我叫詹力偉，是這座地下城的守門員                                                        ";
		Sleep(3000);
		gotoxy(0, 14);   cout << "                          詹力偉:你唯有通關這座地下城，並把這座地下城的秘密公諸於世，才能逃離這裡                                                           ";
		Sleep(3000);
		gotoxy(0, 15);   cout << "                                            我:我之前都沒打(code)過地下城啊!                                                           ";
		Sleep(3000);
		gotoxy(0, 16);   cout << "                                      詹力偉:這裡有一套新手裝備給你，去吧勇者!                                                      ";
		Sleep(3000);
		gotoxy(0, 17);   cout << "                                            我:幹!根本不聽我講話啊                                                          ";
		Sleep(3000);
		gotoxy(0, 18);   cout << "                                            我:好吧看來要逃離這裡，只能通關這裡                                                           ";
		Sleep(3000);
		gotoxy(0, 19);   cout << "                                            我:上吧，這學期的成績就看這個地下城了!                                                         ";
		Sleep(3000);
		system("cls");
		gotoxy(0, 0);      cout << "  ____________         __             __   __   _________          ________          __________      _________                          ";
		gotoxy(0, 1);      cout << " |   ________  \\      |  |           |  | |  | /         \\       /         |       /   _______|    /          \\       ";
		gotoxy(0, 2);      cout << " |  |        \\  \\     |  |           |  | |  |/ /-----\\   \\     /   -------       |  |            /  /----- \\  \\   ";
		gotoxy(0, 3);      cout << " |  |         \\  \\    |  |           |  | |    /       \\   \\   /  /               |  |           /  /        \\  \\      ";
		gotoxy(0, 4);      cout << " |  |          \\  \\   |  |           |  | |   /         \\  |  |  |                |  |           |  |         |  |    ";
		gotoxy(0, 5);      cout << " |  |           |  |  |  |           |  | |  |          |  |  |  |                |  ---------   |  |         |  |       ";
		gotoxy(0, 6);     cout << " |  |           |  |  |  |           |  | |  |          |  |  |  |                |           |  |  |         |  | ";
		gotoxy(0, 7);     cout << " |  |           |  |  |  |           |  | |  |          |  |  |  |                |  ---------   |  |         |  |   ";
		gotoxy(0, 8);     cout << " |  |          /  /   |  |           |  | |  |          |  |  |  |      _______   |  |           |  |         |  |  ";
		gotoxy(0, 9);     cout << " |  |         /  /     \\  \\         /  /  |  |          |  |  \\  \\     |__     |  |  |           |  |         |  |               ";
		gotoxy(0, 10);     cout << " |  |        /  /       \\  \\       /  /   |  |          |  |   \\  \\      /  /| |  |  |_________   \\  \\       /  /  ";
		gotoxy(0, 11);     cout << " |   --------  /         \\  -------  /    |  |          |  |    \\  ------  / |_|  |            |   \\  ------   /            ";
		gotoxy(0, 12);     cout << "  ------------             ----------      --            --      ---------         \\-----------     ----------         ";
		gotoxy(0, 13);     cout << "                                                                                                                                       ";
		gotoxy(0, 15);     cout << "                                                                                             __   _________                               ";
		gotoxy(0, 16);     cout << "                                                                                            |  | /         \\                                            ";
		gotoxy(0, 17);     cout << "                                                                                            |  |/ /-----\\   \\                                       ";
		gotoxy(0, 18);     cout << "                                                                                            |    /       \\   \\                                      ";
		gotoxy(0, 19);     cout << "                                                                                            |   /         \\   |                                       ";
		gotoxy(0, 20);     cout << "                                                            Welcome                         |  |           |  |                                       ";
		gotoxy(0, 21);     cout << "                                                                                            |  |           |  |                                         ";
		gotoxy(0, 22);     cout << "                                                                                            |  |           |  |                                      ";
		gotoxy(0, 23);     cout << "                                                                                            |  |           |  |                                      ";
		gotoxy(0, 24);     cout << "                                                                                            |  |           |  |                                ";
		gotoxy(0, 25);     cout << "                                                                                            |  |           |  |                               ";
		gotoxy(0, 26);     cout << "                                                                                             --             --                               ";
		gotoxy(0, 27);     cout << "                                                                                                                                        ";
		Sleep(10000);
		system("cls");
		gotoxy(0, 15);   cout << "                                            就這樣你慢步得走進陰暗的地下城裡                                                         ";
		Sleep(3000);
		system("cls");
	}
	void ending()
	{
		system("cls");
		gotoxy(0, 5);   cout << "                                             系統:地下城之主已被打敗                                               ";
		Sleep(3000);
		gotoxy(0, 6);   cout << "                                               我:終於通關了                                                              ";
		Sleep(3000);
		gotoxy(0, 7);   cout << "                                          我:這樣終於可以逃離這裡了吧                                                   ";
		Sleep(3000);
		gotoxy(0, 8);   cout << "                                             從王座深處傳出腳步聲....                                                        ";
		Sleep(3000);
		gotoxy(0, 9);   cout << "                                               我:你怎麼在這裡??!!! 詹....                                                         ";
		Sleep(3000);
		gotoxy(0, 10);   cout << "                                            我:不，我應該叫你學分大魔王對吧!                                                           ";
		Sleep(3000);
		gotoxy(0, 11);   cout << "                                     詹力偉:哼哼，沒想到吧，就算你通關地下城我還是可以把你當掉喔 哈哈哈哈!!                                                      ";
		Sleep(3000);
		gotoxy(0, 12);   cout << "                                              我:nooooooooooooooooo!!!!!!                                                          ";
		Sleep(3000);
		//PlaySound(NULL, NULL, NULL);
		gotoxy(0, 13);   cout << "                                                 從鍵盤上突然驚醒                                                          ";
		Sleep(3000);
		gotoxy(0, 14);   cout << "                                              我:原來這些都是夢阿                                                         ";
		Sleep(3000);
		gotoxy(0, 15);   cout << "                                              我:不，我的地下城code還沒寫完                                                         ";
		Sleep(3000);
		gotoxy(0, 16);   cout << "                                              我:原來這才是真正的噩夢阿....                                                         ";
		Sleep(3000);
		system("cls");
		gotoxy(0, 0);      cout << "  ____________         __             __   __   _________          ________          __________      _________                          ";
		gotoxy(0, 1);      cout << " |   ________  \\      |  |           |  | |  | /         \\       /         |       /   _______|    /          \\       ";
		gotoxy(0, 2);      cout << " |  |        \\  \\     |  |           |  | |  |/ /-----\\   \\     /   -------       |  |            /  /----- \\  \\   ";
		gotoxy(0, 3);      cout << " |  |         \\  \\    |  |           |  | |    /       \\   \\   /  /               |  |           /  /        \\  \\      ";
		gotoxy(0, 4);      cout << " |  |          \\  \\   |  |           |  | |   /         \\  |  |  |                |  |           |  |         |  |    ";
		gotoxy(0, 5);      cout << " |  |           |  |  |  |           |  | |  |          |  |  |  |                |  ---------   |  |         |  |       ";
		gotoxy(0, 6);     cout << " |  |           |  |  |  |           |  | |  |          |  |  |  |                |           |  |  |         |  | ";
		gotoxy(0, 7);     cout << " |  |           |  |  |  |           |  | |  |          |  |  |  |                |  ---------   |  |         |  |   ";
		gotoxy(0, 8);     cout << " |  |          /  /   |  |           |  | |  |          |  |  |  |      _______   |  |           |  |         |  |  ";
		gotoxy(0, 9);     cout << " |  |         /  /     \\  \\         /  /  |  |          |  |  \\  \\     |__     |  |  |           |  |         |  |               ";
		gotoxy(0, 10);     cout << " |  |        /  /       \\  \\       /  /   |  |          |  |   \\  \\      /  /| |  |  |_________   \\  \\       /  /  ";
		gotoxy(0, 11);     cout << " |   --------  /         \\  -------  /    |  |          |  |    \\  ------  / |_|  |            |   \\  ------   /            ";
		gotoxy(0, 12);     cout << "  ------------             ----------      --            --      ---------         \\-----------     ----------         ";
		gotoxy(0, 13);     cout << "                                                                                                                                       ";
		gotoxy(0, 15);     cout << "                                                                                             __   _________                               ";
		gotoxy(0, 16);     cout << "                                                                                            |  | /         \\                                            ";
		gotoxy(0, 17);     cout << "                                                                                            |  |/ /-----\\   \\                                       ";
		gotoxy(0, 18);     cout << "                                                                                            |    /       \\   \\                                      ";
		gotoxy(0, 19);     cout << "                                                                                            |   /         \\   |                                       ";
		gotoxy(0, 20);     cout << "                                        Thanks For Playing                                  |  |           |  |                                       ";
		gotoxy(0, 21);     cout << "                                                                                            |  |           |  |                                         ";
		gotoxy(0, 22);     cout << "                                                                                            |  |           |  |                                      ";
		gotoxy(0, 23);     cout << "                                                                                            |  |           |  |                                      ";
		gotoxy(0, 24);     cout << "                                                                                            |  |           |  |                                ";
		gotoxy(0, 25);     cout << "                                                                                            |  |           |  |                               ";
		gotoxy(0, 26);     cout << "                                                                                             --             --                               ";
		gotoxy(0, 27);     cout << "                                                                                                                                        ";
		Sleep(10000);
	}
	void mainscence(Player* player)
	{
		map(player);
		if (dungen[player->getx()][player->gety()].getnpc() == NULL)
		{
			if (dungen[player->getx()][player->gety()].getEN() == 1)
			{
				PlaySound(TEXT("沙漠bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 2)
			{
				PlaySound(TEXT("森林bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 3)
			{
				PlaySound(TEXT("沼澤bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else
			{
				PlaySound(TEXT("地牢bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
		}

		char st = 'A';
		while (st != 'u' && st != 'd' && st != 'r' && st != 'l')
		{
			map(player);
			movementmap(player);
			st = _getche();
			//map(player1);
			if (st == 'h')
			{
				system("cls");
				map(player);
				showitem(player);
				gotoxy(30, 26); cout << "                          ";
				gotoxy(30, 25); cout << "   輸入e離開此頁面";
				int itemnum = -1;
				st = _getche();
				while (st != 'e')
				{
					if (st == '0' && player->item.size() >= 1)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[0].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 0;
								player->setnowHP(player->item[0].gethealth());
								player->setnowMP(player->item[0].getmagi());
								player->sethunger(player->item[0].getaddhunger());
								player->setthirsty(player->item[0].getaddthirsty());
								break;
							}
						}
					}
					if (st == '1' && player->item.size() >= 2)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[1].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 1;
								player->setnowHP(player->item[1].gethealth());
								player->setnowMP(player->item[1].getmagi());
								player->sethunger(player->item[1].getaddhunger());
								player->setthirsty(player->item[1].getaddthirsty());
								break;
							}
						}
					}
					if (st == '2' && player->item.size() >= 3)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[2].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入exit離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 2;
								player->setnowHP(player->item[2].gethealth());
								player->setnowMP(player->item[2].getmagi());
								player->sethunger(player->item[2].getaddhunger());
								player->setthirsty(player->item[2].getaddthirsty());
								break;
							}
						}
					}
					if (st == '3' && player->item.size() >= 4)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[3].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 3;
								player->setnowHP(player->item[3].gethealth());
								player->setnowMP(player->item[3].getmagi());
								player->sethunger(player->item[3].getaddhunger());
								player->setthirsty(player->item[3].getaddthirsty());
								break;
							}
						}
					}
					if (st == '4' && player->item.size() >= 5)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[4].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 4;
								player->setnowHP(player->item[4].gethealth());
								player->setnowMP(player->item[4].getmagi());
								player->sethunger(player->item[4].getaddhunger());
								player->setthirsty(player->item[4].getaddthirsty());
								break;
							}
						}
					}
					if (st == '5' && player->item.size() >= 6)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[5].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{

								itemnum = 5;
								player->setnowHP(player->item[5].gethealth());
								player->setnowMP(player->item[5].getmagi());
								player->sethunger(player->item[5].getaddhunger());
								player->setthirsty(player->item[5].getaddthirsty());
								break;
							}
						}

					}
					if (st == '6' && player->item.size() >= 7)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[6].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 6;
								player->setnowHP(player->item[6].gethealth());
								player->setnowMP(player->item[6].getmagi());
								player->sethunger(player->item[6].getaddhunger());
								player->setthirsty(player->item[6].getaddthirsty());
								break;
							}
						}
					}
					if (st == '7' && player->item.size() >= 8)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[7].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 7;
								player->setnowHP(player->item[7].gethealth());
								player->setnowMP(player->item[7].getmagi());
								player->sethunger(player->item[7].getaddhunger());
								player->setthirsty(player->item[7].getaddthirsty());
								break;
							}
						}
					}
					if (st == '8' && player->item.size() >= 9)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[8].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 8;
								player->setnowHP(player->item[8].gethealth());
								player->setnowMP(player->item[8].getmagi());
								player->sethunger(player->item[8].getaddhunger());
								player->setthirsty(player->item[8].getaddthirsty());
								break;
							}
						}
					}
					if (st == '9' && player->item.size() >= 10)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[9].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 9;
								player->setnowHP(player->item[9].gethealth());
								player->setnowMP(player->item[9].getmagi());
								player->sethunger(player->item[9].getaddhunger());
								player->setthirsty(player->item[9].getaddthirsty());
								break;
							}
						}
					}
					if (st == 'y')
					{
						if (player->item[itemnum].getname() == "交大學餐")
						{
							player->setpoison(0);
						}

						itemuse(player, itemnum);
					}
					system("cls");
					map(player);
					showitem(player);
					gotoxy(30, 26); cout << "                         ";
					gotoxy(30, 25); cout << "   輸入e離開此頁面";
					st = _getche();
				}

			}
			else if (st == 'g')
			{
				system("cls");
				map(player);
				showarmor(player);
				gotoxy(50, 19); cout << "                     ";
				gotoxy(50, 18); cout << "   輸入e離開此頁面";
				st = _getche();
				while (st != 'e')
				{
					system("cls");
					map(player);
					showarmor(player);
					gotoxy(50, 19); cout << "                     ";
					gotoxy(50, 18); cout << "   輸入e離開此頁面";

					st = _getche();
				}
			}
			else if (st == 's')
			{
				showskill(player);
				gotoxy(0, 14); cout << "輸入e離開此頁面";
				st = _getche();
				while (st != 'e')
				{
					system("cls");
					showskill(player);
					gotoxy(0, 14); cout << "輸入e離開此頁面";
					st = _getche();
				}
			}
			else if (st == 'u')
			{
				if (player->getx() == 0)
				{
					system("cls");
					gotoxy(0, 15); cout << "                                 不能往上走";
					st = 'A';
					Sleep(1000);
				}
				else
				{
					statesystem(player);
					death(player);
					player->setlocation(-1, 0);
				}

			}
			else if (st == 'd')
			{
				if (player->getx() == 4)
				{
					system("cls");
					gotoxy(0, 15); cout << "                                 不能往下走";
					st = 'A';
					Sleep(1000);
				}
				else
				{
					statesystem(player);
					death(player);
					player->setlocation(1, 0);
				}

			}
			else if (st == 'r')
			{
				if (player->gety() == 4)
				{
					system("cls");
					gotoxy(0, 15); cout << "                                 不能往右走";
					st = 'A';
					Sleep(1000);
				}
				else
				{
					statesystem(player);
					death(player);
					player->setlocation(0, 1);
				}
			}
			else if (st == 'l')
			{
				if (player->gety() == 0)
				{
					system("cls");
					gotoxy(0, 15); cout << "                                 不能往左走";
					st = 'A';
					Sleep(1000);
				}
				else
				{
					statesystem(player);
					death(player);
					player->setlocation(0, -1);
				}
			}
			system("cls");
		}
		mciSendString(TEXT("play walk.wav"), NULL, 0, NULL);
	}
	void Fight(Player* player, Enemy* enemy)
	{

		srand(time(NULL));
		int randomnb;
		Fightscence(player, enemy);
		char action;
		while (player->getnowHP() > 0 && enemy->getnowHP() > 0)
		{

			gotoxy(4, 25);
			action = _getche();
			gotoxy(4, 25);
			cout << "                       ";
			if (action == 'a')
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				gotoxy(4, *linepoint); cout << "你使用普通攻擊對敵人造成了";
				if (player->getATK() - enemy->getDEF() <= 0)
				{
					cout << "1點傷害          ";
					enemy->getdamage(1);
				}
				else
				{
					randomnb = rand();
					if (randomnb % 100 <= player->getLUK())
					{
						cout << player->getATK() * 1.35 - enemy->getDEF() << "點暴擊傷害       ";
						enemy->getdamage(player->getATK() * 1.35 - enemy->getDEF());
					}
					else
					{
						cout << player->getATK() - enemy->getDEF() << "點傷害          ";
						enemy->getdamage(player->getATK() - enemy->getDEF());
					}
				}
				linedetect(linepoint);
				gotoxy(0, 2);      cout << " |                             "; cout << enemy->getname() << "  HP:" << setw(3) << setfill(' ') << enemy->getnowHP() << "/" << setw(3) << setfill(' ') << enemy->getHP(); gotoxy(119, 2); cout << "|";
				if (enemy->getnowHP() <= 0)
				{
					if (*linepoint == 25)
					{
						gotoxy(0, 21); cout << " |                                                       ";
						gotoxy(0, 22); cout << " |                                                       ";
						gotoxy(0, 23); cout << " |                                                       ";
						//gotoxy(0, 24); cout << " |                                          ";
						*linepoint = 21;
					}
					gotoxy(4, *linepoint); cout << "你成功擊敗" << enemy->getname() << "了              ";
					linedetect(linepoint);
					if (*linepoint == 25)
					{
						gotoxy(0, 21); cout << " |                                                       ";
						gotoxy(0, 22); cout << " |                                                       ";
						gotoxy(0, 23); cout << " |                                                       ";
						//gotoxy(0, 24); cout << " |                                          ";
						*linepoint = 21;
					}
					gotoxy(4, *linepoint);
					enemygood(player, enemy);
					*linepoint = 21;
				}
			}
			else if (action == '1')
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                            ";
					*linepoint = 21;
				}
				if (player->getnowMP() < player->getskill1().getmagicost() || player->getskill1().getname() == "無")
				{
					if (player->getskill1().getname() == "無")
					{
						gotoxy(4, *linepoint); cout << "你還未學習技能                      ";
						linedetect(linepoint);

					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP值不足                             ";
						linedetect(linepoint);
					}
					continue;
				}
				else
				{
					gotoxy(4, *linepoint); cout << "你使用" << player->getskill1().getname() << "對敵人造成了";
					if (player->getATK() * player->getskill1().getindex() - enemy->getDEF() <= 0)
					{
						cout << "1點傷害              ";
						enemy->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill1().getindex() * 1.35 - enemy->getDEF() << "點暴擊傷害              ";
							enemy->getdamage(player->getATK() * player->getskill1().getindex() * 1.35 - enemy->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill1().getindex() - enemy->getDEF() << "點傷害                ";
							enemy->getdamage(player->getATK() * player->getskill1().getindex() - enemy->getDEF());
						}

					}
					linedetect(linepoint);
					gotoxy(0, 2);      cout << " |                             "; cout << enemy->getname() << "  HP:" << setw(3) << setfill(' ') << enemy->getnowHP() << "/" << setw(3) << setfill(' ') << enemy->getHP(); gotoxy(119, 2); cout << "|";
					player->setnowMP(-(player->getskill1().getmagicost()));
					gotoxy(0, 22);
					cout << " |";
					gotoxy(82, 22); cout << "|   MP:";
					SetColor(17);
					for (int h = 0; h < 20; h++)
					{
						if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
						{
							SetColor();
						}
						cout << " ";
					}
					SetColor();
					cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
					gotoxy(119, 22);
					cout << "|";
					if (enemy->getnowHP() <= 0)
					{
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						gotoxy(4, *linepoint); cout << "你成功擊敗" << enemy->getname() << "了             ";
						linedetect(linepoint);
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						gotoxy(4, *linepoint);
						enemygood(player, enemy);
						*linepoint = 21;
					}
				}

			}
			else if (action == '2')
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				if (player->getnowMP() < player->getskill2().getmagicost() || player->getskill2().getname() == "無")
				{
					if (player->getskill2().getname() == "無")
					{
						gotoxy(4, *linepoint); cout << "你還未學習技能                   ";
						linedetect(linepoint);
					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP值不足                        ";
						linedetect(linepoint);
					}
					continue;
				}
				else
				{
					if (player->getskill2().getname() == "I am atomic")
					{
						PlaySound(NULL, NULL, NULL);
						system("cls");
						gotoxy(0, 7);   cout << "                                                     我曾想過                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                        即使我再強，一旦核彈砸下來我就會消失不見                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          有一天我想明白了，想要打敗核彈很簡單                                                         ";
						Sleep(3000);
						gotoxy(0, 10);   cout << "                                                 只要成為核彈就可以了!!!!                                                           ";
						Sleep(2000);
						PlaySound(TEXT("i am atomic.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(1700);
						gotoxy(0, 11);   cout << "                                                     I....                                                       ";
						Sleep(1700);
						gotoxy(0, 12);   cout << "                                                     AM.....                                                           ";
						Sleep(2200);
						gotoxy(0, 13);   cout << "                                                     ATOMIC                                                           ";
						Sleep(3000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					else if (player->getskill2().getname() == "英雄憧憬")
					{
						system("cls");
						PlaySound(TEXT("英雄憧憬.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(11800);
						gotoxy(0, 7);   cout << "                                              面對絕對強大而蠻橫的力量                                                   ";
						Sleep(3300);
						gotoxy(0, 8);   cout << "                                            只靠一點點微小的力量與之對抗                                                         ";
						Sleep(3100);
						gotoxy(0, 9);   cout << "                                                       那就是...                                                         ";
						Sleep(4800);
						gotoxy(0, 10);   cout << "                                                   !!英雄的一擊!!                                                           ";
						Sleep(2000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					else if (player->getskill2().getname() == "無量空處")
					{
						PlaySound(NULL, NULL, NULL);
						system("cls");
						gotoxy(0, 7);   cout << "                                                   讓我來教你一課                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                                如何在別人的領域裡獲勝呢?                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          答案很簡單，再開一個比敵人強的領域就行了                                                         ";
						Sleep(2000);
						PlaySound(TEXT("無量空處.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(1300);
						gotoxy(0, 10);   cout << "                                                     領域展開                                                       ";
						Sleep(3000);
						gotoxy(0, 11);   cout << "                                                     無量空處!!                                                           ";
						Sleep(6000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					gotoxy(4, *linepoint); cout << "你使用" << player->getskill2().getname() << "對敵人造成了";
					if (player->getATK() * player->getskill2().getindex() - enemy->getDEF() <= 0)
					{
						cout << "1點傷害                       ";
						enemy->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill2().getindex() * 1.35 - enemy->getDEF() << "點暴擊傷害                       ";
							enemy->getdamage(player->getATK() * player->getskill2().getindex() * 1.35 - enemy->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill2().getindex() - enemy->getDEF() << "點傷害                            ";
							enemy->getdamage(player->getATK() * player->getskill2().getindex() - enemy->getDEF());
						}

					}
					linedetect(linepoint);
					gotoxy(0, 2);      cout << " |                             "; cout << enemy->getname() << "  HP:" << setw(3) << setfill(' ') << enemy->getnowHP() << "/" << setw(3) << setfill(' ') << enemy->getHP(); gotoxy(119, 2); cout << "|";
					player->setnowMP(-(player->getskill2().getmagicost()));
					gotoxy(0, 22);
					cout << " |";
					gotoxy(82, 22); cout << "|   MP:";
					SetColor(17);
					for (int h = 0; h < 20; h++)
					{
						if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
						{
							SetColor();
						}
						cout << " ";
					}
					SetColor();
					cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
					gotoxy(119, 22);
					cout << "|";
					if (enemy->getnowHP() <= 0)
					{
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						gotoxy(4, *linepoint); cout << "你成功擊敗" << enemy->getname() << "了                         ";
						linedetect(linepoint);
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						gotoxy(4, *linepoint);
						enemygood(player, enemy);
						*linepoint = 21;
					}
				}
				PlaySound(TEXT("一般戰鬥bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (action == 'h')
			{
				showitem(player);
				gotoxy(30, 26); cout << "                          ";
				gotoxy(30, 25); cout << "   輸入e離開此頁面";
				char st;
				int itemnum = -1;
				st = _getche();
				while (st != 'e')
				{
					if (st == '0' && player->item.size() >= 1)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[0].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 0;
								player->setnowHP(player->item[0].gethealth());
								player->setnowMP(player->item[0].getmagi());
								player->sethunger(player->item[0].getaddhunger());
								player->setthirsty(player->item[0].getaddthirsty());
								break;
							}
						}
					}
					if (st == '1' && player->item.size() >= 2)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[1].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 1;
								player->setnowHP(player->item[1].gethealth());
								player->setnowMP(player->item[1].getmagi());
								player->sethunger(player->item[1].getaddhunger());
								player->setthirsty(player->item[1].getaddthirsty());
								break;
							}
						}
					}
					if (st == '2' && player->item.size() >= 3)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[2].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入exit離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 2;
								player->setnowHP(player->item[2].gethealth());
								player->setnowMP(player->item[2].getmagi());
								player->sethunger(player->item[2].getaddhunger());
								player->setthirsty(player->item[2].getaddthirsty());
								break;
							}
						}
					}
					if (st == '3' && player->item.size() >= 4)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[3].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 3;
								player->setnowHP(player->item[3].gethealth());
								player->setnowMP(player->item[3].getmagi());
								player->sethunger(player->item[3].getaddhunger());
								player->setthirsty(player->item[3].getaddthirsty());
								break;
							}
						}
					}
					if (st == '4' && player->item.size() >= 5)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[4].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 4;
								player->setnowHP(player->item[4].gethealth());
								player->setnowMP(player->item[4].getmagi());
								player->sethunger(player->item[4].getaddhunger());
								player->setthirsty(player->item[4].getaddthirsty());
								break;
							}
						}
					}
					if (st == '5' && player->item.size() >= 6)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[5].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{

								itemnum = 5;
								player->setnowHP(player->item[5].gethealth());
								player->setnowMP(player->item[5].getmagi());
								player->sethunger(player->item[5].getaddhunger());
								player->setthirsty(player->item[5].getaddthirsty());
								break;
							}
						}

					}
					if (st == '6' && player->item.size() >= 7)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[6].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 6;
								player->setnowHP(player->item[6].gethealth());
								player->setnowMP(player->item[6].getmagi());
								player->sethunger(player->item[6].getaddhunger());
								player->setthirsty(player->item[6].getaddthirsty());
								break;
							}
						}
					}
					if (st == '7' && player->item.size() >= 8)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[7].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 7;
								player->setnowHP(player->item[7].gethealth());
								player->setnowMP(player->item[7].getmagi());
								player->sethunger(player->item[7].getaddhunger());
								player->setthirsty(player->item[7].getaddthirsty());
								break;
							}
						}
					}
					if (st == '8' && player->item.size() >= 9)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[8].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 8;
								player->setnowHP(player->item[8].gethealth());
								player->setnowMP(player->item[8].getmagi());
								player->sethunger(player->item[8].getaddhunger());
								player->setthirsty(player->item[8].getaddthirsty());
								break;
							}
						}
					}
					if (st == '9' && player->item.size() >= 10)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[9].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 9;
								player->setnowHP(player->item[9].gethealth());
								player->setnowMP(player->item[9].getmagi());
								player->sethunger(player->item[9].getaddhunger());
								player->setthirsty(player->item[9].getaddthirsty());
								break;
							}
						}
					}
					if (st == 'y')
					{

						system("cls");
						Fightscence(player, enemy);
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						if (player->item[itemnum].getname() == "交大學餐")
						{
							player->setpoison(0);
						}
						gotoxy(4, *linepoint); cout << "成功使用" << player->item[itemnum].getname() << "                     ";
						linedetect(linepoint);
						itemuse(player, itemnum);
						break;
					}
					system("cls");
					Fightscence(player, enemy);
					showitem(player);
					gotoxy(30, 26); cout << "                        ";
					gotoxy(30, 25); cout << "   輸入e離開此頁面";
					st = _getche();
				}

				if (st == 'e')
				{
					system("cls");
					Fightscence(player, enemy);
					continue;
				}
			}
			else if (action == 'r')
			{
				randomnb = rand();
				if (randomnb % 100 <= player->getAGI())
				{
					if (*linepoint == 25)
					{
						gotoxy(0, 21); cout << " |                                                       ";
						gotoxy(0, 22); cout << " |                                                       ";
						gotoxy(0, 23); cout << " |                                                       ";
						//gotoxy(0, 24); cout << " |                                          ";
						*linepoint = 21;
					}
					gotoxy(4, *linepoint);
					cout << "逃跑成功                             ";
					*linepoint = 21;
					retreatornot = 1;
					player->setx(player->getlastx());
					player->sety(player->getlasty());
					enemy->setnowHP();
					Sleep(2000);
					return;
				}
				else
				{
					if (*linepoint == 25)
					{
						gotoxy(0, 21); cout << " |                                                       ";
						gotoxy(0, 22); cout << " |                                                       ";
						gotoxy(0, 23); cout << " |                                                       ";
						//gotoxy(0, 24); cout << " |                                          ";
						*linepoint = 21;
					}
					gotoxy(4, *linepoint);
					cout << "逃跑失敗                            ";
					linedetect(linepoint);
				}
			}
			else
			{
				continue;
			}
			Sleep(1000);
			LevelUp(player);
			if (enemy->getnowHP() > 0)
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				gotoxy(4, *linepoint);
				randomnb = rand();
				if (randomnb % 100 <= player->getAGI())
				{
					cout << "你滑溜的身法躲掉了敵人的攻擊                 ";
				}
				else
				{
					enemy->attack(player);
				}
				linedetect(linepoint);
				//即時顯示血量與魔力
				gotoxy(0, 2);      cout << " |                             "; cout << enemy->getname() << "  HP:" << setw(3) << setfill(' ') << enemy->getnowHP() << "/" << setw(3) << setfill(' ') << enemy->getHP(); gotoxy(119, 2); cout << "|";
				gotoxy(82, 21); cout << "|   HP:";
				SetColor(204);
				for (int h = 0; h < 20; h++)
				{
					if (h > player->getnowHP() / (player->getHP() / 20))
					{
						SetColor();
					}
					cout << " ";
				}
				SetColor();
				cout << " " << setw(3) << setfill(' ') << player->getnowHP() << "/" << setw(3) << setfill(' ') << player->getHP();
				gotoxy(119, 21);
				cout << "|";
				gotoxy(0, 22);
				cout << " |";
				gotoxy(82, 22); cout << "|   MP:";
				SetColor(17);
				for (int h = 0; h < 20; h++)
				{
					if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
					{
						SetColor();
					}
					cout << " ";
				}
				SetColor();
				cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
				gotoxy(119, 22);
				cout << "|";
			}
			death(player);
		}


		enemy->setnowHP();
		Sleep(3000);
	}
	void Fightscence(Player* player, Enemy* enemy)
	{
		gotoxy(0, 0);      cout << "  _____________________________________________________________________________________________________________________";
		gotoxy(0, 1);      cout << " |Lev." << player->getLevel() << "           " << "name:" << player->getName() << "                                                         "; gotoxy(95, 1); cout << " gold:" << player->getGold() << "    "; gotoxy(105, 1); cout << "     save"; gotoxy(119, 1); cout << "| ";
		gotoxy(0, 2);      cout << " |                             "; cout << enemy->getname() << "  HP:" << setw(3) << setfill(' ') << enemy->getnowHP() << "/" << setw(3) << setfill(' ') << enemy->getHP(); gotoxy(119, 2); cout << "|";
		gotoxy(0, 3);      cout << " |                                                                                                                     | ";
		gotoxy(0, 4);      cout << " |                                                                                                                     | ";
		gotoxy(0, 5);      cout << " |                                                                                                                     | ";
		gotoxy(0, 6);      cout << " |                                                                                                                     | ";
		gotoxy(0, 7);      cout << " |                                                                                                                     | ";
		gotoxy(0, 8);      cout << " |                                                                                                                     | ";
		gotoxy(0, 9);      cout << " |                                                                                                                     | ";
		gotoxy(0, 10);     cout << " |                                                                                                                     | ";
		gotoxy(0, 11);     cout << " |                                                                                                                     | ";
		gotoxy(0, 12);     cout << " |                                                                                                                     | ";
		gotoxy(0, 13);     cout << " |                                                                                                                     | ";
		gotoxy(0, 14);     cout << " |                                                                                                                     | ";
		gotoxy(0, 15);     cout << " |                                                                                                                     | ";
		gotoxy(0, 16);     cout << " |                                                                                                                     | ";
		gotoxy(0, 17);     cout << " |                                                                                                                     | ";
		gotoxy(0, 18);     cout << " |                                                                                                                     | ";
		gotoxy(0, 19);     cout << " |                                                                                                                     | ";
		gotoxy(0, 20);     cout << " |---------------------------------------------------------------------------------------------------------------------| ";
		gotoxy(0, 21);     cout << " |                                                                                ";
		gotoxy(82, 21); cout << "|   HP:";
		SetColor(204);
		for (int h = 0; h < 20; h++)
		{
			if (h > player->getnowHP() / (player->getHP() / 20))
			{
				SetColor();
			}
			cout << " ";
		}
		SetColor();
		cout << " " << setw(3) << setfill(' ') << player->getnowHP() << "/" << setw(3) << setfill(' ') << player->getHP();
		gotoxy(119, 21);
		cout << "|";
		gotoxy(0, 22);
		cout << " |";
		gotoxy(82, 22); cout << "|   MP:";
		SetColor(17);
		for (int h = 0; h < 20; h++)
		{
			if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
			{
				SetColor();
			}
			cout << " ";
		}
		SetColor();
		cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
		gotoxy(119, 22);
		cout << "|";
		gotoxy(0, 23);     cout << " |                                                                                |                                    | ";
		gotoxy(0, 24);     cout << " |                                                                                |   ATK: " << player->getATK(); gotoxy(101, 24); cout << "DEF: " << player->getDEF(); gotoxy(119, 24); cout << "|";
		gotoxy(0, 25);     cout << " |                                                                                |                                    | ";
		gotoxy(0, 26);     cout << " |--------------------------------------------------------------------------------|   LUK: " << player->getLUK(); gotoxy(101, 26); cout << "AGI: " << player->getAGI(); gotoxy(119, 26); cout << "|";
		gotoxy(0, 27);     cout << " |   ATK(請輸入a)   S1(請輸入1)   S2(請輸入2)   Item(使用請按h)  逃跑請輸入r      |                                    | ";
		gotoxy(0, 28);     cout << " |_____________________________________________________________________________________________________________________| ";

	}
	void enemygood(Player* player, Enemy* enemy)
	{
		srand(time(NULL));
		int randomnb;
		if (enemy->getname() == "Gobulin")
		{
			cout << "獲得60經驗、100金幣   ";
			player->setnowEXP(60);
			player->setgold(100);
			randomnb = rand();
			if (randomnb % 100 <= 50)
			{
				cout << "戰利品:哥布林水袋           ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "哥布林水袋")
					{
						player->item[i].setstack(1);
						haveornot = 1;
					}
				}
				if (!haveornot)
				{
					player->item.push_back(allItem[0]);
					player->item[player->item.size() - 1].setstack(1);
				}
			}
			else
			{
				cout << "戰利品:無";
			}
		}
		else if (enemy->getname() == "Dragon")
		{
			cout << "獲得500經驗、1000金幣   ";
			player->setnowEXP(500);
			player->setgold(1000);
			randomnb = rand();
			if (randomnb % 100 <= 70)
			{
				cout << "戰利品:龍肉            ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "龍肉")
					{
						player->item[i].setstack(1);
						haveornot = 1;
					}
				}
				if (!haveornot)
				{
					player->item.push_back(allItem[1]);
					player->item[player->item.size() - 1].setstack(1);
				}
			}
			else
			{
				cout << "戰利品:無";
			}
		}
		else if (enemy->getname() == "Devil")
		{
			cout << "獲得120經驗、200金幣   ";
			player->setnowEXP(120);
			player->setgold(200);
			randomnb = rand();
			if (randomnb % 100 <= 30)
			{
				cout << "戰利品:惡魔獠牙            ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "惡魔獠牙")
					{
						player->item[i].setstack(1);
						haveornot = 1;
					}
				}
				if (!haveornot)
				{
					player->item.push_back(allItem[3]);
					player->item[player->item.size() - 1].setstack(1);
				}
			}
			else
			{
				cout << "戰利品:無";
			}
		}
		else if (enemy->getname() == "Ghost")
		{
			cout << "獲得200經驗、150金幣   ";
			player->setnowEXP(200);
			player->setgold(150);
			randomnb = rand();
			if (randomnb % 100 <= 50)
			{
				cout << "戰利品:幽靈寒氣          ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "幽靈寒氣")
					{
						player->item[i].setstack(1);
						haveornot = 1;
					}
				}
				if (!haveornot)
				{
					player->item.push_back(allItem[4]);
					player->item[player->item.size() - 1].setstack(1);
				}
			}
			else
			{
				cout << "戰利品:無";
			}
		}
		else if (enemy->getname() == "Slime")
		{
			cout << "獲得50經驗、50金幣   ";
			player->setnowEXP(50);
			player->setgold(50);
			randomnb = rand();
			if (randomnb % 100 <= 50)
			{
				cout << "戰利品:史萊姆黏液        ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "史萊姆黏液")
					{
						player->item[i].setstack(1);
						haveornot = 1;
					}
				}
				if (!haveornot)
				{
					player->item.push_back(allItem[2]);
					player->item[player->item.size() - 1].setstack(1);
				}
			}
		}
		else
		{
			cout << "戰利品:無";
		}
		//LevelUp(player);
	}
	void shopscence(NPC* shopkeeper, Player* player)
	{
		gotoxy(0, 0);      cout << "  _____________________________________________________________________________________________________________________";
		gotoxy(0, 1);      cout << " |Lev." << player->getLevel() << "           " << "name:" << player->getName() << "                                                         "; gotoxy(95, 1); cout << " gold:" << player->getGold() << "    "; gotoxy(105, 1); cout << "     save"; gotoxy(119, 1); cout << "| ";
		gotoxy(0, 2);      cout << " |                                                                                                                     | ";
		gotoxy(0, 3);      cout << " |                                                                                                                     | ";
		gotoxy(0, 4);      cout << " |                                                                                                                     | ";
		gotoxy(0, 5);      cout << " |                                                                                                                     | ";
		gotoxy(0, 6);      cout << " |                                                                                                                     | ";
		gotoxy(0, 7);      cout << " |                                                                                                                     | ";
		gotoxy(0, 8);      cout << " |                                                                                                                     | ";
		gotoxy(0, 9);      cout << " |                                                                                                                     | ";
		gotoxy(0, 10);     cout << " |                                                                                                                     | ";
		gotoxy(0, 11);     cout << " |                                                                                                                     | ";
		gotoxy(0, 12);     cout << " |                                                                                                                     | ";
		gotoxy(0, 13);     cout << " |                                                                                                                     | ";
		gotoxy(0, 14);     cout << " |                                                                                                                     | ";
		gotoxy(0, 15);     cout << " |                                                                                                                     | ";
		gotoxy(0, 16);     cout << " |                                                                                                                     | ";
		gotoxy(0, 17);     cout << " |                                                                                                                     | ";
		gotoxy(0, 18);     cout << " |                                                                                                                     | ";
		gotoxy(0, 19);     cout << " |                                                                                                                     | ";
		gotoxy(0, 20);     cout << " |---------------------------------------------------------------------------------------------------------------------| ";
		gotoxy(0, 21);     cout << " |                                                                                |   HP:";
		SetColor(204);
		for (int h = 0; h < 20; h++)
		{
			if (h > player->getnowHP() / (player->getHP() / 20))
			{
				SetColor();
			}
			cout << " ";
		}
		SetColor();
		cout << " " << player->getnowHP() << "/" << player->getHP();
		gotoxy(119, 21);
		cout << "|";

		gotoxy(0, 22);
		cout << " |          ";
		if (shopkeeper->getindex() == 1)
		{
			gotoxy(10, 22);
			cout << shopkeeper->getshopArmor()[0].getname();
			gotoxy(32, 22);
			cout << shopkeeper->getshopArmor()[1].getname();
			gotoxy(59, 22);
			cout << shopkeeper->getshopArmor()[2].getname();
		}
		else if (shopkeeper->getindex() == 2)
		{
			gotoxy(10, 22);
			cout << shopkeeper->getshopitem()[0].getname();
			gotoxy(32, 22);
			cout << shopkeeper->getshopitem()[1].getname();
			gotoxy(59, 22);
			cout << shopkeeper->getshopitem()[2].getname();
		}
		gotoxy(82, 22); cout << "|   MP:";
		SetColor(17);
		for (int h = 0; h < 20; h++)
		{
			if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
			{
				SetColor();
			}
			cout << " ";
		}
		SetColor();
		cout << " " << player->getnowMP() << "/" << player->getMP();
		gotoxy(119, 22);
		cout << "|";
		gotoxy(0, 23);     cout << " |   |------------------|     |------------------|     |------------------|"; gotoxy(82, 23); cout << "|"; gotoxy(119, 23); cout << "|";
		if (shopkeeper->getindex() == 1)
		{
			gotoxy(0, 24); cout << " |   |輸入1購買 花費:" << setw(3) << setfill('0') << shopkeeper->getshopArmor()[0].getcost() << "|     |輸入2購買 花費:" << setw(3) << setfill('0') << shopkeeper->getshopArmor()[1].getcost() << "|     |輸入3購買 花費:" << setw(3) << setfill('0') << shopkeeper->getshopArmor()[2].getcost() << "|"; gotoxy(82, 24); cout << "|   ATK: " << player->getATK(); gotoxy(101, 24); cout << "DEF: " << player->getDEF(); gotoxy(119, 24); cout << "|";
		}
		else if (shopkeeper->getindex() == 2)
		{
			gotoxy(0, 24); cout << " |   |輸入1購買 花費:" << setw(3) << setfill('0') << shopkeeper->getshopitem()[0].getcost() << "|     |輸入2購買 花費:" << setw(3) << setfill('0') << shopkeeper->getshopitem()[1].getcost() << "|     |輸入3購買 花費:" << setw(3) << setfill('0') << shopkeeper->getshopitem()[2].getcost() << "|"; gotoxy(82, 24); cout << "|   ATK: " << player->getATK(); gotoxy(101, 24); cout << "DEF: " << player->getDEF(); gotoxy(119, 24); cout << "|";

		}
		gotoxy(0, 25);     cout << " |   |------------------|     |------------------|     |------------------|"; gotoxy(82, 25); cout << "|"; gotoxy(119, 25); cout << "|";
		gotoxy(0, 26);     cout << " |--------------------------------------------------------------------------------"; gotoxy(82, 26); cout << "|   LUK: " << player->getLUK(); gotoxy(101, 26); cout << "AGI: " << player->getAGI(); gotoxy(119, 26); cout << "|";
		gotoxy(0, 27);     cout << " |                                                                                |                                    | ";
		gotoxy(0, 28);     cout << " |_____________________________________________________________________________________________________________________| ";

	}
	void shopsystem(NPC* shopkeeper, Player* player)
	{

		shopscence(shopkeeper, player);
		char purchase;
		gotoxy(0, 27); cout << " |                                                   如果不購買請輸入 0";
		gotoxy(2, 27);
		purchase = _getche();
		while (purchase != '0')
		{

			if (shopkeeper->getindex() == 1)
			{
				if (purchase == '1')
				{
					if (player->getGold() < shopkeeper->getshopArmor()[0].getcost())
					{
						gotoxy(0, 27); cout << " |你的錢錢好像不夠               ";
						Sleep(2000);
					}
					else
					{
						player->setgold(-(shopkeeper->getshopArmor()[0].getcost()));
						//設定盔甲值
						player->setarmorcharacter(0, shopkeeper->getshopArmor()[0].getatk(), shopkeeper->getshopArmor()[0].getdef(), shopkeeper->getshopArmor()[0].getagi(), shopkeeper->getshopArmor()[0].getluk());
						player->armor[0] = shopkeeper->getshopArmor()[0];
						//shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |購買成功，歡迎再來          ";
						mciSendString(TEXT("play 商店購買音效.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '2')
				{

					if (player->getGold() < shopkeeper->getshopArmor()[1].getcost())
					{
						gotoxy(0, 27); cout << " |你的錢錢好像不夠           ";
						Sleep(2000);
					}
					else
					{
						player->setgold(-(shopkeeper->getshopArmor()[1].getcost()));
						player->setarmorcharacter(1, shopkeeper->getshopArmor()[1].getatk(), shopkeeper->getshopArmor()[1].getdef(), shopkeeper->getshopArmor()[1].getagi(), shopkeeper->getshopArmor()[1].getluk());
						player->armor[1] = shopkeeper->getshopArmor()[1];
						shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |購買成功，歡迎再來              ";
						mciSendString(TEXT("play 商店購買音效.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '3')
				{

					if (player->getGold() < shopkeeper->getshopArmor()[2].getcost())
					{
						gotoxy(0, 27); cout << " |你的錢錢好像不夠            ";
						Sleep(2000);
					}
					else
					{
						player->setgold(-(shopkeeper->getshopArmor()[2].getcost()));
						player->setarmorcharacter(2, shopkeeper->getshopArmor()[2].getatk(), shopkeeper->getshopArmor()[2].getdef(), shopkeeper->getshopArmor()[2].getagi(), shopkeeper->getshopArmor()[2].getluk());
						player->armor[2] = shopkeeper->getshopArmor()[2];
						shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |購買成功，歡迎再來           ";
						mciSendString(TEXT("play 商店購買音效.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
			}
			else if (shopkeeper->getindex() == 2)
			{
				if (purchase == '1')
				{
					if (player->getGold() < shopkeeper->getshopitem()[0].getcost())
					{
						gotoxy(0, 27); cout << " |你的錢錢好像不夠                     ";
						Sleep(2000);
					}
					else
					{
						bool haveornot = 0;
						for (int i = 0; i < player->item.size(); i++)
						{
							if (player->item[i].getname() == shopkeeper->getshopitem()[0].getname())
							{
								player->item[i].setstack(1);
								haveornot = 1;
							}
						}
						if (!haveornot)
						{
							player->item.push_back(shopkeeper->getshopitem()[0]);
							player->item[player->item.size() - 1].setstack(1);
						}
						player->setgold(-(shopkeeper->getshopitem()[0].getcost()));
						shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |購買成功，歡迎再來           ";
						mciSendString(TEXT("play 商店購買音效.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '2')
				{

					if (player->getGold() < shopkeeper->getshopitem()[1].getcost())
					{
						gotoxy(0, 27); cout << " |你的錢錢好像不夠           ";
						Sleep(2000);
					}
					else
					{
						bool haveornot = 0;
						for (int i = 0; i < player->item.size(); i++)
						{
							if (player->item[i].getname() == shopkeeper->getshopitem()[1].getname())
							{
								player->item[i].setstack(1);
								haveornot = 1;
							}
						}
						if (!haveornot)
						{
							player->item.push_back(shopkeeper->getshopitem()[1]);
							player->item[player->item.size() - 1].setstack(1);
						}
						player->setgold(-(shopkeeper->getshopitem()[1].getcost()));
						shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |購買成功，歡迎再來        ";
						mciSendString(TEXT("play 商店購買音效.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '3')
				{
					if (player->getGold() < shopkeeper->getshopitem()[2].getcost())
					{
						gotoxy(0, 27); cout << " |你的錢錢好像不夠      ";
						Sleep(2000);
					}
					else
					{
						bool haveornot = 0;
						for (int i = 0; i < player->item.size(); i++)
						{
							if (player->item[i].getname() == shopkeeper->getshopitem()[2].getname())
							{
								player->item[i].setstack(1);
								haveornot = 1;
							}
						}
						if (!haveornot)
						{
							player->item.push_back(shopkeeper->getshopitem()[2]);
							player->item[player->item.size() - 1].setstack(1);
						}
						player->setgold(-(shopkeeper->getshopitem()[2].getcost()));
						shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |購買成功，歡迎再來                              ";
						mciSendString(TEXT("play 商店購買音效.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
			}
			system("cls");
			shopscence(shopkeeper, player);
			gotoxy(0, 27); cout << " |                                                   如果不購買請輸入 0";
			gotoxy(2, 27);
			purchase = _getche();
		}

	}
	void movementmap(Player* player)
	{
		if (player->getx() == 0 && player->gety() == 0)
		{
			gotoxy(0, 2);      cout << " |                                                                                                                     | ";
			gotoxy(0, 3);      cout << " |                                                                                                                     | ";
			gotoxy(0, 4);      cout << " |                                                                                                                     | ";
			gotoxy(0, 5);      cout << " |                                                                                                                     | ";
			gotoxy(0, 6);      cout << " |                                                                                                                     | ";
			gotoxy(0, 7);      cout << " |                                                                                                                     | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |                                                                                                         \\           | ";
			gotoxy(0, 10);     cout << " |                                                請輸入要往哪個方向走 r                             ------ \\          | ";
			gotoxy(0, 11);     cout << " |                                                         d                                         ------ /          | ";
			gotoxy(0, 12);     cout << " |                                                                                                         /           | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 15);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 16);     cout << " |                                                     \\ |  | /                                                        | ";
			gotoxy(0, 17);     cout << " |                                                      \\    /                                                         | ";
			gotoxy(0, 18);     cout << " |                                                       \\  /                                                          | ";
			gotoxy(0, 19);     cout << " |                                                        \\/                                                           | ";
		}
		else if (player->getx() == 0 && player->gety() != 0 && player->gety() != 4)
		{
			gotoxy(0, 2);      cout << " |                                                                                                                     | ";
			gotoxy(0, 3);      cout << " |                                                                                                                     | ";
			gotoxy(0, 4);      cout << " |                                                                                                                     | ";
			gotoxy(0, 5);      cout << " |                                                                                                                     | ";
			gotoxy(0, 6);      cout << " |                                                                                                                     | ";
			gotoxy(0, 7);      cout << " |                                                                                                                     | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |           /                                                                                             \\           | ";
			gotoxy(0, 10);     cout << " |          / ------                            l 請輸入要往哪個方向走 r                             ------ \\          | ";
			gotoxy(0, 11);     cout << " |          \\ ------                                       d                                         ------ /          | ";
			gotoxy(0, 12);     cout << " |           \\                                                                                             /           | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 15);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 16);     cout << " |                                                     \\ |  | /                                                        | ";
			gotoxy(0, 17);     cout << " |                                                      \\    /                                                         | ";
			gotoxy(0, 18);     cout << " |                                                       \\  /                                                          | ";
			gotoxy(0, 19);     cout << " |                                                        \\/                                                           | ";
		}
		else if (player->getx() == 0 && player->gety() == 4)
		{
			gotoxy(0, 2);      cout << " |                                                                                                                     | ";
			gotoxy(0, 3);      cout << " |                                                                                                                     | ";
			gotoxy(0, 4);      cout << " |                                                                                                                     | ";
			gotoxy(0, 5);      cout << " |                                                                                                                     | ";
			gotoxy(0, 6);      cout << " |                                                                                                                     | ";
			gotoxy(0, 7);      cout << " |                                                                                                                     | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |           /                                                                                                         | ";
			gotoxy(0, 10);     cout << " |          / ------                            l 請輸入要往哪個方向走                                                 | ";
			gotoxy(0, 11);     cout << " |          \\ ------                                       d                                                           | ";
			gotoxy(0, 12);     cout << " |           \\                                                                                                         | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 15);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 16);     cout << " |                                                     \\ |  | /                                                        | ";
			gotoxy(0, 17);     cout << " |                                                      \\    /                                                         | ";
			gotoxy(0, 18);     cout << " |                                                       \\  /                                                          | ";
			gotoxy(0, 19);     cout << " |                                                        \\/                                                           | ";

		}
		else if (player->getx() != 0 && player->gety() == 4 && player->getx() != 4)
		{
			gotoxy(0, 2);      cout << " |                                                        /\\                                                           | ";
			gotoxy(0, 3);      cout << " |                                                       /  \\                                                          | ";
			gotoxy(0, 4);      cout << " |                                                      /    \\                                                         | ";
			gotoxy(0, 5);      cout << " |                                                     / |  | \\                                                        | ";
			gotoxy(0, 6);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 7);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |           /                                             u                                                           | ";
			gotoxy(0, 10);     cout << " |          / ------                            l 請輸入要往哪個方向走                                                 | ";
			gotoxy(0, 11);     cout << " |          \\ ------                                       d                                                           | ";
			gotoxy(0, 12);     cout << " |           \\                                                                                                         | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 15);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 16);     cout << " |                                                     \\ |  | /                                                        | ";
			gotoxy(0, 17);     cout << " |                                                      \\    /                                                         | ";
			gotoxy(0, 18);     cout << " |                                                       \\  /                                                          | ";
			gotoxy(0, 19);     cout << " |                                                        \\/                                                           | ";

		}
		else if (player->getx() == 4 && player->gety() != 4 && player->gety() != 0)
		{
			gotoxy(0, 2);      cout << " |                                                        /\\                                                           | ";
			gotoxy(0, 3);      cout << " |                                                       /  \\                                                          | ";
			gotoxy(0, 4);      cout << " |                                                      /    \\                                                         | ";
			gotoxy(0, 5);      cout << " |                                                     / |  | \\                                                        | ";
			gotoxy(0, 6);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 7);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |           /                                             u                                               \\           | ";
			gotoxy(0, 10);     cout << " |          / ------                            l 請輸入要往哪個方向走 r                             ------ \\          | ";
			gotoxy(0, 11);     cout << " |          \\ ------                                                                                 ------ /          | ";
			gotoxy(0, 12);     cout << " |           \\                                                                                             /           | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                                                                                     | ";
			gotoxy(0, 15);     cout << " |                                                                                                                     | ";
			gotoxy(0, 16);     cout << " |                                                                                                                     | ";
			gotoxy(0, 17);     cout << " |                                                                                                                     | ";
			gotoxy(0, 18);     cout << " |                                                                                                                     | ";
			gotoxy(0, 19);     cout << " |                                                                                                                     | ";

		}
		else if (player->getx() == 4 && player->gety() == 0)
		{
			gotoxy(0, 2);      cout << " |                                                        /\\                                                           | ";
			gotoxy(0, 3);      cout << " |                                                       /  \\                                                          | ";
			gotoxy(0, 4);      cout << " |                                                      /    \\                                                         | ";
			gotoxy(0, 5);      cout << " |                                                     / |  | \\                                                        | ";
			gotoxy(0, 6);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 7);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |                                                         u                                               \\           | ";
			gotoxy(0, 10);     cout << " |                                                請輸入要往哪個方向走 r                             ------ \\          | ";
			gotoxy(0, 11);     cout << " |                                                                                                   ------ /          | ";
			gotoxy(0, 12);     cout << " |                                                                                                         /           | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                                                                                     | ";
			gotoxy(0, 15);     cout << " |                                                                                                                     | ";
			gotoxy(0, 16);     cout << " |                                                                                                                     | ";
			gotoxy(0, 17);     cout << " |                                                                                                                     | ";
			gotoxy(0, 18);     cout << " |                                                                                                                     | ";
			gotoxy(0, 19);     cout << " |                                                                                                                     | ";

		}
		else if (player->getx() != 4 && player->getx() != 0 && player->gety() == 0)
		{
			gotoxy(0, 2);      cout << " |                                                        /\\                                                           | ";
			gotoxy(0, 3);      cout << " |                                                       /  \\                                                          | ";
			gotoxy(0, 4);      cout << " |                                                      /    \\                                                         | ";
			gotoxy(0, 5);      cout << " |                                                     / |  | \\                                                        | ";
			gotoxy(0, 6);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 7);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |                                                         u                                               \\           | ";
			gotoxy(0, 10);     cout << " |                                                請輸入要往哪個方向走 r                             ------ \\          | ";
			gotoxy(0, 11);     cout << " |                                                         d                                         ------ /          | ";
			gotoxy(0, 12);     cout << " |                                                                                                         /           | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 15);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 16);     cout << " |                                                     \\ |  | /                                                        | ";
			gotoxy(0, 17);     cout << " |                                                      \\    /                                                         | ";
			gotoxy(0, 18);     cout << " |                                                       \\  /                                                          | ";
			gotoxy(0, 19);     cout << " |                                                        \\/                                                           | ";

		}
		else
		{
			gotoxy(0, 2);      cout << " |                                                        /\\                                                           | ";
			gotoxy(0, 3);      cout << " |                                                       /  \\                                                          | ";
			gotoxy(0, 4);      cout << " |                                                      /    \\                                                         | ";
			gotoxy(0, 5);      cout << " |                                                     / |  | \\                                                        | ";
			gotoxy(0, 6);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 7);      cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 8);      cout << " |                                                                                                                     | ";
			gotoxy(0, 9);      cout << " |           /                                             u                                               \\           | ";
			gotoxy(0, 10);     cout << " |          / ------                            l 請輸入要往哪個方向走 r                             ------ \\          | ";
			gotoxy(0, 11);     cout << " |          \\ ------                                       d                                         ------ /          | ";
			gotoxy(0, 12);     cout << " |           \\                                                                                             /           | ";
			gotoxy(0, 13);     cout << " |                                                                                                                     | ";
			gotoxy(0, 14);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 15);     cout << " |                                                       |  |                                                          | ";
			gotoxy(0, 16);     cout << " |                                                     \\ |  | /                                                        | ";
			gotoxy(0, 17);     cout << " |                                                      \\    /                                                         | ";
			gotoxy(0, 18);     cout << " |                                                       \\  /                                                          | ";
			gotoxy(0, 19);     cout << " |                                                        \\/                                                           | ";

		}
	}
	void procedure(Player* player)
	{
		srand(time(NULL));
		int randomnb;
		while (player->getnowHP() > 0 && dungen[4][4].getenemy()->getnowHP() > 0)
		{
			system("cls");
			player->setlastposition();
			
			if (retreatornot == 1)
			{
				retreatornot = 0;
			if (dungen[player->getx()][player->gety()].getEN() == 1)
			{
				PlaySound(TEXT("沙漠bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 2)
			{
				PlaySound(TEXT("森林bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 3)
			{
				PlaySound(TEXT("沼澤bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else
			{
				PlaySound(TEXT("地牢bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			}
			mainscence(player);
			system("cls");
			if (dungen[player->getx()][player->gety()].getEN() == 1)
			{
				gotoxy(0, 15);   cout << "                                                          你身處在一片沙漠                                     ";
				Sleep(2000);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 2)
			{
				gotoxy(0, 15);   cout << "                                                          你身處在一片森林                                     ";
				Sleep(2000);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 3)
			{
				gotoxy(0, 15);   cout << "                                                          你身處在一片沼澤地                                   ";
				Sleep(2000);
			}
			else
			{
				gotoxy(0, 15);   cout << "                                                          你身處在普通的地牢環境                               ";
				Sleep(2000);
			}

			if (player->getx() == 4 && player->gety() == 4)
			{
				bossfight(player);
				return;
			}
			else
			{
				if (dungen[player->getx()][player->gety()].getnpc() != NULL)
				{
					system("cls");
					gotoxy(0, 15);   cout << "                                                          你遇到了"; cout << dungen[player->getx()][player->gety()].getnpc()->getname();
					if (dungen[player->getx()][player->gety()].getEN() == 1)
					{
						PlaySound(TEXT("沙漠bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					else if (dungen[player->getx()][player->gety()].getEN() == 2)
					{
						PlaySound(TEXT("森林bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					else if (dungen[player->getx()][player->gety()].getEN() == 3)
					{
						PlaySound(TEXT("沼澤bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					else
					{
						PlaySound(TEXT("地牢bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					Sleep(1500);
					shopsystem(dungen[player->getx()][player->gety()].getnpc(), player);
				}
				else if (dungen[player->getx()][player->gety()].getenemy() != NULL && retreatornot == 0)
				{
					system("cls");
					gotoxy(0, 15);   cout << "                                                          你遇到了"; cout << dungen[player->getx()][player->gety()].getenemy()->getname();
					PlaySound(TEXT("一般戰鬥bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					Sleep(1500);
					Fight(player, dungen[player->getx()][player->gety()].getenemy());
				}

				if (dungen[player->getx()][player->gety()].getEN() == 1 && retreatornot == 0)
				{
					PlaySound(TEXT("沙漠bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					randomnb = rand();
					if (randomnb % 100 <= 10)//碰到沙塵暴
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          你碰到了沙塵暴                              ";
						Sleep(2000);
						player->sethunger(-10);
						player->setthirsty(-10);
					}
					randomnb = rand();
					if (randomnb % 100 <= 30)//找到綠洲
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          你碰到了綠洲                              ";
						Sleep(2000);
						player->setthirsty(50);
					}
				}
				else if (dungen[player->getx()][player->gety()].getEN() == 2 && retreatornot == 0)
				{
					PlaySound(TEXT("森林bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					randomnb = rand();
					if (randomnb % 100 <= 50)//找到水源
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          你在森林裡找到一處水源                    ";
						Sleep(2000);
						player->setthirsty(50);
					}
					randomnb = rand();
					if (randomnb % 100 >= 50)//遇到動物
					{
						char action;
						system("cls");
						gotoxy(0, 15);   cout << "                                                          你在森林裡遇到一隻兔子                    ";
						gotoxy(0, 16);   cout << "                                                        還一邊發出peko~peko~的叫聲                    ";
						gotoxy(0, 17);   cout << "                                                        輸入c來捕捉，若不捕捉則輸入0                    ";
						
						while (1) {
							action = _getche();
							if (action == 'c')
							{
								randomnb = rand();
								if (randomnb % 100 <= 40)
								{
									gotoxy(0, 18);   cout << "                                                        捕捉成功!                    ";
									gotoxy(0, 18);   cout << "                                                      飽食度提升10                    ";
									player->sethunger(10);
								}
								else
								{
									gotoxy(0, 18);   cout << "                                                        捕捉失敗!                    ";
								}
								break;
							}
							else if (action == '0')
							{
								break;
							}
						}
						randomnb = rand();
						if (randomnb % 100 <= 10)
						{
							system("cls");
							int times = 0;
							char num;
							system("cls");
							gotoxy(0, 15);   cout << "                                                          你在森林裡遇到一隻熊                    ";
							Sleep(500);
							gotoxy(0, 16);   cout << "                                               那隻熊一直講著""兄弟，有急事，可以轉一下身嗎?""                   ";
							Sleep(1000);
							gotoxy(0, 17);   cout << "                                                      你感覺生命受到了威脅，趕快按a逃脫                    ";

							gotoxy(50, 18);
							SetColor(17);

							for (int h = 0; h < 20; h++)
							{
								if (h >= (float)times / ((float)50 / 20))
								{
									SetColor();
								}
								cout << " ";
							}
							SetColor();
							cout << " " << setw(3) << setfill(' ') << times << "/50";


							std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
							std::chrono::steady_clock::time_point end;
							double elapsed_seconds;

							std::string input;
							int count = 0;


							while (true) {
								end = std::chrono::steady_clock::now();
								elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

								if (elapsed_seconds >= 5.0) {
									break;
								}

								num = _getche();
								gotoxy(50, 18);
								SetColor(17);
								for (int h = 0; h < 20; h++)
								{
									if (h >= (float)times / ((float)50 / 20))
									{
										SetColor();
									}
									cout << " ";
								}
								SetColor();
								cout << " " << setw(3) << setfill(' ') << times << "/50";

								times++;
								if (times >= 51)
								{
									break;
								}
							}
							if (times >= 50)
							{
								gotoxy(50, 19);
								cout << "成功掙脫";
							}
							else
							{
								gotoxy(50, 19);
								cout << "掙脫失敗，扣5生命";
								player->setnowHP(-5);
							}

							Sleep(1000);

						}
						Sleep(2000);
						player->setthirsty(50);
					}
				}
				else if (dungen[player->getx()][player->gety()].getEN() == 3 && retreatornot == 0)
				{
				PlaySound(TEXT("沼澤bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					randomnb = rand();
					if (randomnb % 100 >= 50)///毒氣沼澤特性
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          你碰到了沼澤毒氣                              ";
						if (player->getpoison() == 2|| player->getpoison()==3)
						{
							player->setpoison(3);
						}
						else
						{
							player->setpoison(1);
						}

						Sleep(2000);
						player->setnowHP(-5);
					}
				}

			}

		}

	}
	void hungersystem(Player* player)
	{
		if (dungen[player->getx()][player->gety()].getEN() == 1)
		{
			if (player->gethunger() > 30)
			{
				player->sethunger(-30);
			}
			else
			{
				player->sethunger(-30);
				player->setnowHP(-5);
			}
		}
		else
		{
			if (player->gethunger() > 20)
			{
				player->sethunger(-20);
			}
			else
			{
				player->sethunger(-20);
				player->setnowHP(-5);
			}

		}
	}
	void thirstysystem(Player* player)
	{
		if (dungen[player->getx()][player->gety()].getEN() == 2)
		{
			if (player->getthirsty() > 30)
			{
				player->setthirsty(-30);
			}
			else
			{
				player->setthirsty(-30);
				player->setnowHP(-5);
				player->setnowMP(-1);
			}
		}
		else
		{
			if (player->getthirsty() > 20)
			{
				player->setthirsty(-20);
			}
			else
			{
				player->setthirsty(-20);
				player->setnowHP(-5);
				player->setnowMP(-1);
			}
		}
	}
	void poisonsystem(Player* player)
	{
		if (player->getpoison() == 1)
		{
			player->setnowHP(-5);

		}
		else if (player->getpoison() == 2)
		{
			player->setnowMP(-2);
		}
		else if (player->getpoison() == 3)
		{
			player->setnowHP(-5);
			player->setnowMP(-2);
		}

	}
	void statesystem(Player* player)
	{
		hungersystem(player);
		thirstysystem(player);
		poisonsystem(player);
	}
	void itemuse(Player* player, int indicate)
	{
		player->item[indicate].setstack(-1);
		if (player->item[indicate].getstack() == 0)
		{
			player->item.erase(player->item.begin() + indicate);
		}
	}
	void bossfight(Player* player)
	{
		srand(time(NULL));
		int randomnb;
		system("cls");
		gotoxy(0, 7);   cout << "                                             系統提示:你已進入BOSS房                                                   ";
		Sleep(3000);
		gotoxy(0, 8);   cout << "                                             我:你就是地下城之主嗎?                                                        ";
		Sleep(3000);
		gotoxy(0, 9);   cout << "                                                魔王:勇者來吧!!!                                                         ";
		Sleep(3000);
		gotoxy(0, 10);   cout << "                                           一場激烈的戰鬥即將上演                                                          ";
		Sleep(1500);
		system("cls");
		int bossstate = 1;
		PlaySound(TEXT("boss戰鬥bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Fightscence(player, finalboss);
		char action;
		while (player->getnowHP() > 0 && finalboss->getnowHP() > 0)
		{
			gotoxy(4, 25);
			action = _getche();
			gotoxy(4, 25);
			cout << "                       ";
			if (action == 'a')
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				gotoxy(4, *linepoint); cout << "你使用普通攻擊對敵人造成了";
				if (player->getATK() - finalboss->getDEF() <= 0)
				{
					cout << "1點傷害";
					finalboss->getdamage(1);
				}
				else
				{
					randomnb = rand();
					if (randomnb % 100 <= player->getLUK())
					{
						cout << player->getATK() * 1.35 - finalboss->getDEF() << "點暴擊傷害";
						finalboss->getdamage(player->getATK() * 1.35 - finalboss->getDEF());
					}
					else
					{
						cout << player->getATK() - finalboss->getDEF() << "點傷害";
						finalboss->getdamage(player->getATK() - finalboss->getDEF());
					}
				}
				linedetect(linepoint);
				gotoxy(0, 2);      cout << " |                             "; cout << finalboss->getname() << "  HP:" << setw(3) << setfill(' ') << finalboss->getnowHP() << "/" << setw(3) << setfill(' ') << finalboss->getHP(); gotoxy(119, 2); cout << "|";
				if (finalboss->getnowHP() <= 0)
				{
					if (*linepoint == 25)
					{
						gotoxy(0, 21); cout << " |                                                       ";
						gotoxy(0, 22); cout << " |                                                       ";
						gotoxy(0, 23); cout << " |                                                       ";
						//gotoxy(0, 24); cout << " |                                          ";
						*linepoint = 21;
					}
					gotoxy(4, *linepoint); cout << "你成功擊敗" << finalboss->getname() << "了";
					linedetect(linepoint);
					if (*linepoint == 25)
					{
						gotoxy(0, 21); cout << " |                                                       ";
						gotoxy(0, 22); cout << " |                                                       ";
						gotoxy(0, 23); cout << " |                                                       ";
						//gotoxy(0, 24); cout << " |                                          ";
						*linepoint = 21;
					}
				}
			}
			else if (action == '1')
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				if (player->getnowMP() < player->getskill1().getmagicost() || player->getskill1().getname() == "無")
				{
					if (player->getskill1().getname() == "無")
					{
						gotoxy(4, *linepoint); cout << "你還未學習技能                          ";
						linedetect(linepoint);

					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP值不足                             ";
						linedetect(linepoint);
					}
					continue;
				}
				else
				{

					gotoxy(4, *linepoint); cout << "你使用" << player->getskill1().getname() << "對敵人造成了";
					if (player->getATK() * player->getskill1().getindex() - finalboss->getDEF() <= 0)
					{
						cout << "1點傷害";
						finalboss->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill1().getindex() * 1.35 - finalboss->getDEF() << "點暴擊傷害";
							finalboss->getdamage(player->getATK() * player->getskill1().getindex() * 1.35 - finalboss->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill1().getindex() - finalboss->getDEF() << "點傷害";
							finalboss->getdamage(player->getATK() * player->getskill1().getindex() - finalboss->getDEF());
						}

					}
					linedetect(linepoint);
					gotoxy(0, 2);      cout << " |                             "; cout << finalboss->getname() << "  HP:" << setw(3) << setfill(' ') << finalboss->getnowHP() << "/" << setw(3) << setfill(' ') << finalboss->getHP(); gotoxy(119, 2); cout << "|";
					player->setnowMP(-(player->getskill1().getmagicost()));
					gotoxy(0, 22);
					cout << " |";
					gotoxy(82, 22); cout << "|   MP:";
					SetColor(17);
					for (int h = 0; h < 20; h++)
					{
						if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
						{
							SetColor();
						}
						cout << " ";
					}
					SetColor();
					cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
					gotoxy(119, 22);
					cout << "|";
					if (finalboss->getnowHP() <= 0)
					{
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						gotoxy(4, *linepoint); cout << "你成功擊敗" << finalboss->getname() << "了";
						linedetect(linepoint);
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
					}
				}

			}
			else if (action == '2')
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				if (player->getnowMP() < player->getskill2().getmagicost() || player->getskill2().getname() == "無")
				{
					if (player->getskill2().getname() == "無")
					{
						gotoxy(4, *linepoint); cout << "你還未學習技能                                 ";
						linedetect(linepoint);
					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP值不足                                   ";
						linedetect(linepoint);
					}
					continue;
				}
				else
				{
					if (player->getskill2().getname() == "I am atomic")
					{
						PlaySound(NULL, NULL, NULL);
						system("cls");
						gotoxy(0, 7);   cout << "                                                     我曾想過                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                        即使我再強，一旦核彈砸下來我就會消失不見                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          有一天我想明白了，想要打敗核彈很簡單                                                         ";
						Sleep(3000);
						gotoxy(0, 10);   cout << "                                                 只要成為核彈就可以了!!!!                                                           ";
						Sleep(2000);
						PlaySound(TEXT("i am atomic.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(1700);
						gotoxy(0, 11);   cout << "                                                     I....                                                       ";
						Sleep(1700);
						gotoxy(0, 12);   cout << "                                                     AM.....                                                           ";
						Sleep(2200);
						gotoxy(0, 13);   cout << "                                                     ATOMIC                                                           ";
						Sleep(3000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					else if (player->getskill2().getname() == "英雄憧憬")
					{
						system("cls");
						PlaySound(TEXT("英雄憧憬.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(11800);
						gotoxy(0, 7);   cout << "                                              面對絕對強大而蠻橫的力量                                                   ";
						Sleep(3300);
						gotoxy(0, 8);   cout << "                                            只靠一點點微小的力量與之對抗                                                         ";
						Sleep(3100);
						gotoxy(0, 9);   cout << "                                                       那就是...                                                         ";
						Sleep(4800);
						gotoxy(0, 10);   cout << "                                                   !!英雄的一擊!!                                                           ";
						Sleep(2000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					else if (player->getskill2().getname() == "無量空處")
					{
						PlaySound(NULL, NULL, NULL);
						system("cls");
						gotoxy(0, 7);   cout << "                                                   讓我來教你一課                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                                如何在別人的領域裡獲勝呢?                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          答案很簡單，再開一個比敵人強的領域就行了                                                         ";
						Sleep(2000);
						PlaySound(TEXT("無量空處.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(1300);
						gotoxy(0, 10);   cout << "                                                     領域展開                                                       ";
						Sleep(3000);
						gotoxy(0, 11);   cout << "                                                     無量空處!!                                                           ";
						Sleep(6000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					gotoxy(4, *linepoint); cout << "你使用" << player->getskill2().getname() << "對敵人造成了";
					if (player->getATK() * player->getskill2().getindex() - finalboss->getDEF() <= 0)
					{
						cout << "1點傷害";
						finalboss->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill2().getindex() * 1.35 - finalboss->getDEF() << "點暴擊傷害";
							finalboss->getdamage(player->getATK() * player->getskill2().getindex() * 1.35 - finalboss->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill2().getindex() - finalboss->getDEF() << "點傷害";
							finalboss->getdamage(player->getATK() * player->getskill2().getindex() - finalboss->getDEF());
						}

					}
					linedetect(linepoint);
					gotoxy(0, 2);      cout << " |                             "; cout << finalboss->getname() << "  HP:" << setw(3) << setfill(' ') << finalboss->getnowHP() << "/" << setw(3) << setfill(' ') << finalboss->getHP(); gotoxy(119, 2); cout << "|";
					player->setnowMP(-(player->getskill2().getmagicost()));
					gotoxy(0, 22);
					cout << " |";
					gotoxy(82, 22); cout << "|   MP:";
					SetColor(17);
					for (int h = 0; h < 20; h++)
					{
						if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
						{
							SetColor();
						}
						cout << " ";
					}
					SetColor();
					cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
					gotoxy(119, 22);
					cout << "|";
					if (finalboss->getnowHP() <= 0)
					{
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						gotoxy(4, *linepoint); cout << "你成功擊敗" << finalboss->getname() << "了";
						linedetect(linepoint);
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}

					}
				}
				PlaySound(TEXT("boss戰鬥bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (action == 'h')
			{
				showitem(player);
				gotoxy(30, 26); cout << "                          ";
				gotoxy(30, 25); cout << "   輸入e離開此頁面";
				char st;
				int itemnum = -1;
				st = _getche();
				while (st != 'e')
				{
					if (st == '0' && player->item.size() >= 1)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[0].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 0;
								player->setnowHP(player->item[0].gethealth());
								player->setnowMP(player->item[0].getmagi());
								player->sethunger(player->item[0].getaddhunger());
								player->setthirsty(player->item[0].getaddthirsty());
								break;
							}
						}
					}
					if (st == '1' && player->item.size() >= 2)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[1].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 1;
								player->setnowHP(player->item[1].gethealth());
								player->setnowMP(player->item[1].getmagi());
								player->sethunger(player->item[1].getaddhunger());
								player->setthirsty(player->item[1].getaddthirsty());
								break;
							}
						}
					}
					if (st == '2' && player->item.size() >= 3)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[2].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 yes" << "輸入exit離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 2;
								player->setnowHP(player->item[2].gethealth());
								player->setnowMP(player->item[2].getmagi());
								player->sethunger(player->item[2].getaddhunger());
								player->setthirsty(player->item[2].getaddthirsty());
								break;
							}
						}
					}
					if (st == '3' && player->item.size() >= 4)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[3].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 3;
								player->setnowHP(player->item[3].gethealth());
								player->setnowMP(player->item[3].getmagi());
								player->sethunger(player->item[3].getaddhunger());
								player->setthirsty(player->item[3].getaddthirsty());
								break;
							}
						}
					}
					if (st == '4' && player->item.size() >= 5)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[4].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 4;
								player->setnowHP(player->item[4].gethealth());
								player->setnowMP(player->item[4].getmagi());
								player->sethunger(player->item[4].getaddhunger());
								player->setthirsty(player->item[4].getaddthirsty());
								break;
							}
						}
					}
					if (st == '5' && player->item.size() >= 6)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[5].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{

								itemnum = 5;
								player->setnowHP(player->item[5].gethealth());
								player->setnowMP(player->item[5].getmagi());
								player->sethunger(player->item[5].getaddhunger());
								player->setthirsty(player->item[5].getaddthirsty());
								break;
							}
						}

					}
					if (st == '6' && player->item.size() >= 7)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[6].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 6;
								player->setnowHP(player->item[6].gethealth());
								player->setnowMP(player->item[6].getmagi());
								player->sethunger(player->item[6].getaddhunger());
								player->setthirsty(player->item[6].getaddthirsty());
								break;
							}
						}
					}
					if (st == '7' && player->item.size() >= 8)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[7].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 7;
								player->setnowHP(player->item[7].gethealth());
								player->setnowMP(player->item[7].getmagi());
								player->sethunger(player->item[7].getaddhunger());
								player->setthirsty(player->item[7].getaddthirsty());
								break;
							}
						}
					}
					if (st == '8' && player->item.size() >= 9)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[8].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 8;
								player->setnowHP(player->item[8].gethealth());
								player->setnowMP(player->item[8].getmagi());
								player->sethunger(player->item[8].getaddhunger());
								player->setthirsty(player->item[8].getaddthirsty());
								break;
							}
						}
					}
					if (st == '9' && player->item.size() >= 10)
					{
						while (st != 'e')
						{
							system("cls");
							player->item[9].getdetail();
							gotoxy(0, 14); cout << "使用請輸入 y" << "輸入e離開此頁面" << endl;
							st = _getche();
							if (st == 'y')
							{
								itemnum = 9;
								player->setnowHP(player->item[9].gethealth());
								player->setnowMP(player->item[9].getmagi());
								player->sethunger(player->item[9].getaddhunger());
								player->setthirsty(player->item[9].getaddthirsty());
								break;
							}
						}
					}
					if (st == 'y')
					{
						system("cls");
						Fightscence(player, finalboss);
						if (*linepoint == 25)
						{
							gotoxy(0, 21); cout << " |                                                       ";
							gotoxy(0, 22); cout << " |                                                       ";
							gotoxy(0, 23); cout << " |                                                       ";
							//gotoxy(0, 24); cout << " |                                          ";
							*linepoint = 21;
						}
						if (player->item[itemnum].getname() == "交大學餐")
						{
							player->setpoison(0);
						}
						gotoxy(4, *linepoint); cout << "成功使用" << player->item[itemnum].getname() << "                                 ";
						linedetect(linepoint);
						itemuse(player, itemnum);
						break;
					}
					system("cls");
					Fightscence(player, finalboss);
					showitem(player);
					gotoxy(30, 26); cout << "                        ";
					gotoxy(30, 25); cout << "   輸入exit離開此頁面";
					st = _getche();
				}

				if (st == 'e')
				{
					system("cls");
					Fightscence(player, finalboss);
					continue;
				}
			}
			else if (action == 'r')
			{

				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				gotoxy(4, *linepoint);
				cout << "BOSS戰不能逃跑                              ";
				linedetect(linepoint);
			}
			else
			{
				continue;
			}
			Sleep(1000);
			if (finalboss->getnowHP() > 0)
			{
				if (*linepoint == 25)
				{
					gotoxy(0, 21); cout << " |                                                       ";
					gotoxy(0, 22); cout << " |                                                       ";
					gotoxy(0, 23); cout << " |                                                       ";
					//gotoxy(0, 24); cout << " |                                          ";
					*linepoint = 21;
				}
				if (bossstate == 1)
				{
					gotoxy(4, *linepoint);
					finalboss->attack(player);
					linedetect(linepoint);
				}
				if (bossstate == 2)
				{
					gotoxy(4, *linepoint);
					finalboss->attack(player);
					linedetect(linepoint);
				}
				if (bossstate == 3)
				{
					gotoxy(4, *linepoint);
					finalboss->skill1atk(player);
					linedetect(linepoint);
				}
				if (bossstate == 4)
				{
					gotoxy(4, *linepoint);
					finalboss->attack(player);
					linedetect(linepoint);
				}
				if (bossstate == 5)
				{
					system("cls");
					gotoxy(0, 7);   cout << "                                             頓時間黑暗從四周襲來                                                   ";
					Sleep(3000);
					gotoxy(0, 8);   cout << "                                        宛如死亡般的氣息瀰漫整個空間                                                        ";
					Sleep(3000);
					gotoxy(0, 9);   cout << "                                              魔王:嘗嘗我的絕招吧!!!                                                         ";
					Sleep(3000);
					gotoxy(0, 10);   cout << "                                              !!!死亡嘆息!!!                                                           ";
					mciSendString(TEXT("play boss技能音效.wav"), NULL, 0, NULL);
					Sleep(1000);
					*linepoint = 21;
					system("cls");
					Fightscence(player, finalboss);
					gotoxy(4, *linepoint);
					finalboss->skill2atk(player);
					linedetect(linepoint);
				}

				//即時顯示血量與魔力
				gotoxy(0, 2);      cout << " |                             "; cout << finalboss->getname() << "  HP:" << setw(3) << setfill(' ') << finalboss->getnowHP() << "/" << setw(3) << setfill(' ') << finalboss->getHP(); gotoxy(119, 2); cout << "|";
				gotoxy(82, 21); cout << "|   HP:";
				SetColor(204);
				for (int h = 0; h < 20; h++)
				{
					if (h > player->getnowHP() / (player->getHP() / 20))
					{
						SetColor();
					}
					cout << " ";
				}
				SetColor();
				cout << " " << setw(3) << setfill(' ') << player->getnowHP() << "/" << setw(3) << setfill(' ') << player->getHP();
				gotoxy(119, 21);
				cout << "|";
				gotoxy(0, 22);
				cout << " |";
				gotoxy(82, 22); cout << "|   MP:";
				SetColor(17);
				for (int h = 0; h < 20; h++)
				{
					if (h >= (float)player->getnowMP() / ((float)player->getMP() / 20))
					{
						SetColor();
					}
					cout << " ";
				}
				SetColor();
				cout << " " << setw(3) << setfill(' ') << player->getnowMP() << "/" << setw(3) << setfill(' ') << player->getMP();
				gotoxy(119, 22);
				cout << "|";
			}
			death(player);
			bossstate++;
			if (bossstate == 6)
			{
				bossstate = 1;
			}
		}
	}
	void LevelUp(Player* player)
	{
		while (player->getnowEXP() >= player->getEXP())
		{
			player->setnowEXP(-(player->getEXP()));
			player->levelup();
			player->setEXP();
		}
	}

	

};


#endif
