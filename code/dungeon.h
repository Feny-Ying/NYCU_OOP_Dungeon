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
		gotoxy(55, 15); cout << "�п�J�A���W�r:";
		cin >> name;
		player1 = new Player(name);
		dungen = { {Room(),Room(0,new Gobulin()),Room(0,&AllarmorNPC[0]),Room(1,new Slime()),Room(1,new Ghost())},{Room(3,&AllItemNPC[0]),Room(0,new Slime()),Room(),Room(1,new Devil()),Room(1)},{Room(3,new Gobulin()),Room(0,&AllarmorNPC[1]),Room(),Room(0,new Slime()),Room(0,new Dragon())},{Room(0,new Devil()),Room(2),Room(2,new Ghost()),Room(0,&AllItemNPC[1]),Room()},{Room(),Room(2,new Gobulin()),Room(2),Room(0,new Dragon()),Room(0,new Boss())} };

	}

	void startgame()
	{
		PlaySound(TEXT("�}�Ybgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		preface();
		PlaySound(TEXT("walk.wav"), NULL, SND_FILENAME | SND_SYNC);
		procedure(player1);
		PlaySound(TEXT("����bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
		gotoxy(40, 22);    cout << "�Q��:" << player->getownskill().getname();
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
		gotoxy(0, 24);     cout << " |    �˳�(�Ы�g��)";
		gotoxy(40, 24);    cout << "�ޯ�@:" << player->getskill1().getname();
		gotoxy(82, 24);
		cout << "|"; cout << "   ATK: " << player->getATK(); gotoxy(101, 24); cout << "DEF : " << player->getDEF(); gotoxy(119, 24); cout << "|";
		gotoxy(0, 25);     cout << " |                                                                                |                                    | ";
		gotoxy(0, 26);     cout << " |    �D��(�Ы�h��)";
		gotoxy(40, 26);    cout << "�ޯ�G:" << player->getskill2().getname();
		gotoxy(82, 26);
		cout << "|"; cout << "   LUK: " << player->getLUK(); gotoxy(101, 26); cout << "AGI: " << player->getAGI(); gotoxy(119, 26); cout << "|";
		gotoxy(0, 27);     cout << " |                                      (�˵��ޯ�Ы�s��)                         |                                    | ";
		gotoxy(0, 28);     cout << " |________________________________________________________________________________|____________________________________| ";
		gotoxy(62, 22);
		cout << "������:" << setw(3) << setfill('0') << player->gethunger() << "/100";
		gotoxy(62, 24);
		cout << "����:" << setw(3) << setfill('0') << player->getthirsty() << "/100";
		gotoxy(62, 26);
		cout << "���A:";
		if (player->getpoison() == 1)
		{
			cout << "���r";
		}
		else if (player->getpoison() == 2)
		{
			cout << "����";
		}
		else if (player->getpoison() == 3)
		{
			cout << "���r+����";
		}
		else if (player->getpoison() == 0)
		{
			cout << "�L";
		}

	}
	void death(Player* player)
	{
		if (player->getnowHP() <= 0)
		{
			PlaySound(TEXT("���`����.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			gotoxy(0, 15);   cout << "                                   ���u�C�C���ҽk�A�A���ͩR��F���Y�û����I�v�b�a�U����" << endl;
			Sleep(10000);
			exit(0);
		}
	}
	void showskill(Player* player)
	{
		system("cls");
		cout << "�Q�ʡG" << player->getownskill().getname() << endl;
		cout << player->getownskill().getdepict() << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "�ޯ�@�G" << player->getskill1().getname() << endl;
		cout << player->getskill1().getdepict() << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "�ޯ�G�G" << player->getskill2().getname() << endl;
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
			gotoxy(33, 2 * i + 5); cout << "[" << i << "]|" << player->item[i].getname() << "|��J" << i << "���o��ԲӪ����"; gotoxy(80, 2 * i + 5); cout << "�ƶq | " << player->item[i].getstack() << " | ";
			gotoxy(30, 2 * i + 6); cout << "  |--------------------------------------------------------|  ";
		}
	}
	void showarmor(Player* player)
	{
		gotoxy(50, 4);      cout << "                                             ";
		gotoxy(50, 5);      cout << "   __________________________________________  ";
		gotoxy(50, 6);      cout << "  |" << player->armor[0].getname(); gotoxy(67, 6); cout << "|                      |�Y��| ";
		gotoxy(50, 7);      cout << "  |------------------------------------------| ";
		gotoxy(50, 8);      cout << "  |" << player->armor[0].getdetail(); gotoxy(95, 8); cout << "| ";
		gotoxy(50, 9);      cout << "  |------------------------------------------| ";
		gotoxy(50, 10);     cout << "  |" << player->armor[1].getname(); gotoxy(67, 10); cout << "|                      |�߷F| ";
		gotoxy(50, 11);     cout << "  |------------------------------------------| ";
		gotoxy(50, 12);     cout << "  |" << player->armor[1].getdetail(); gotoxy(95, 12); cout << "| ";
		gotoxy(50, 13);     cout << "  |------------------------------------------| ";
		gotoxy(50, 14);     cout << "  |" << player->armor[2].getname(); gotoxy(67, 14); cout << "|                      |�c�l| ";
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
		gotoxy(0, 10);   cout << "                                           ��:�ڬO��?���|���b�o��?                                               ";
		Sleep(3000);
		gotoxy(0, 11);   cout << "                                       �����W���k�H:�ڤw�g���ԧA�h�ɤF                                                              ";
		Sleep(3000);
		gotoxy(0, 12);   cout << "                                                   ��:�A�O��?                                                   ";
		Sleep(3000);
		gotoxy(0, 13);   cout << "                                       �����W���k�H:�ڥs��O���A�O�o�y�a�U�����u����                                                        ";
		Sleep(3000);
		gotoxy(0, 14);   cout << "                          ��O��:�A�ߦ��q���o�y�a�U���A�ç�o�y�a�U�������K���ѩ�@�A�~��k���o��                                                           ";
		Sleep(3000);
		gotoxy(0, 15);   cout << "                                            ��:�ڤ��e���S��(code)�L�a�U����!                                                           ";
		Sleep(3000);
		gotoxy(0, 16);   cout << "                                      ��O��:�o�̦��@�M�s��˳Ƶ��A�A�h�a�i��!                                                      ";
		Sleep(3000);
		gotoxy(0, 17);   cout << "                                            ��:�F!�ڥ���ť�����ܰ�                                                          ";
		Sleep(3000);
		gotoxy(0, 18);   cout << "                                            ��:�n�a�ݨӭn�k���o�̡A�u��q���o��                                                           ";
		Sleep(3000);
		gotoxy(0, 19);   cout << "                                            ��:�W�a�A�o�Ǵ������Z�N�ݳo�Ӧa�U���F!                                                         ";
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
		gotoxy(0, 15);   cout << "                                            �N�o�˧A�C�B�o���i���t���a�U����                                                         ";
		Sleep(3000);
		system("cls");
	}
	void ending()
	{
		system("cls");
		gotoxy(0, 5);   cout << "                                             �t��:�a�U�����D�w�Q����                                               ";
		Sleep(3000);
		gotoxy(0, 6);   cout << "                                               ��:�ש�q���F                                                              ";
		Sleep(3000);
		gotoxy(0, 7);   cout << "                                          ��:�o�˲ש�i�H�k���o�̤F�a                                                   ";
		Sleep(3000);
		gotoxy(0, 8);   cout << "                                             �q���y�`�B�ǥX�}�B�n....                                                        ";
		Sleep(3000);
		gotoxy(0, 9);   cout << "                                               ��:�A���b�o��??!!! ��....                                                         ";
		Sleep(3000);
		gotoxy(0, 10);   cout << "                                            ��:���A�����ӥs�A�Ǥ��j�]����a!                                                           ";
		Sleep(3000);
		gotoxy(0, 11);   cout << "                                     ��O��:���A�S�Q��a�A�N��A�q���a�U�����٬O�i�H��A���� ��������!!                                                      ";
		Sleep(3000);
		gotoxy(0, 12);   cout << "                                              ��:nooooooooooooooooo!!!!!!                                                          ";
		Sleep(3000);
		//PlaySound(NULL, NULL, NULL);
		gotoxy(0, 13);   cout << "                                                 �q��L�W��M���                                                          ";
		Sleep(3000);
		gotoxy(0, 14);   cout << "                                              ��:��ӳo�ǳ��O�ڪ�                                                         ";
		Sleep(3000);
		gotoxy(0, 15);   cout << "                                              ��:���A�ڪ��a�U��code�٨S�g��                                                         ";
		Sleep(3000);
		gotoxy(0, 16);   cout << "                                              ��:��ӳo�~�O�u�������ڪ�....                                                         ";
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
				PlaySound(TEXT("�F�zbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 2)
			{
				PlaySound(TEXT("�˪Lbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 3)
			{
				PlaySound(TEXT("�h�Abgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else
			{
				PlaySound(TEXT("�a�cbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
				gotoxy(30, 25); cout << "   ��Je���}������";
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Jexit���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
						if (player->item[itemnum].getname() == "��j���\")
						{
							player->setpoison(0);
						}

						itemuse(player, itemnum);
					}
					system("cls");
					map(player);
					showitem(player);
					gotoxy(30, 26); cout << "                         ";
					gotoxy(30, 25); cout << "   ��Je���}������";
					st = _getche();
				}

			}
			else if (st == 'g')
			{
				system("cls");
				map(player);
				showarmor(player);
				gotoxy(50, 19); cout << "                     ";
				gotoxy(50, 18); cout << "   ��Je���}������";
				st = _getche();
				while (st != 'e')
				{
					system("cls");
					map(player);
					showarmor(player);
					gotoxy(50, 19); cout << "                     ";
					gotoxy(50, 18); cout << "   ��Je���}������";

					st = _getche();
				}
			}
			else if (st == 's')
			{
				showskill(player);
				gotoxy(0, 14); cout << "��Je���}������";
				st = _getche();
				while (st != 'e')
				{
					system("cls");
					showskill(player);
					gotoxy(0, 14); cout << "��Je���}������";
					st = _getche();
				}
			}
			else if (st == 'u')
			{
				if (player->getx() == 0)
				{
					system("cls");
					gotoxy(0, 15); cout << "                                 ���੹�W��";
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
					gotoxy(0, 15); cout << "                                 ���੹�U��";
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
					gotoxy(0, 15); cout << "                                 ���੹�k��";
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
					gotoxy(0, 15); cout << "                                 ���੹����";
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
				gotoxy(4, *linepoint); cout << "�A�ϥδ��q������ĤH�y���F";
				if (player->getATK() - enemy->getDEF() <= 0)
				{
					cout << "1�I�ˮ`          ";
					enemy->getdamage(1);
				}
				else
				{
					randomnb = rand();
					if (randomnb % 100 <= player->getLUK())
					{
						cout << player->getATK() * 1.35 - enemy->getDEF() << "�I�����ˮ`       ";
						enemy->getdamage(player->getATK() * 1.35 - enemy->getDEF());
					}
					else
					{
						cout << player->getATK() - enemy->getDEF() << "�I�ˮ`          ";
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
					gotoxy(4, *linepoint); cout << "�A���\����" << enemy->getname() << "�F              ";
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
				if (player->getnowMP() < player->getskill1().getmagicost() || player->getskill1().getname() == "�L")
				{
					if (player->getskill1().getname() == "�L")
					{
						gotoxy(4, *linepoint); cout << "�A�٥��ǲߧޯ�                      ";
						linedetect(linepoint);

					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP�Ȥ���                             ";
						linedetect(linepoint);
					}
					continue;
				}
				else
				{
					gotoxy(4, *linepoint); cout << "�A�ϥ�" << player->getskill1().getname() << "��ĤH�y���F";
					if (player->getATK() * player->getskill1().getindex() - enemy->getDEF() <= 0)
					{
						cout << "1�I�ˮ`              ";
						enemy->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill1().getindex() * 1.35 - enemy->getDEF() << "�I�����ˮ`              ";
							enemy->getdamage(player->getATK() * player->getskill1().getindex() * 1.35 - enemy->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill1().getindex() - enemy->getDEF() << "�I�ˮ`                ";
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
						gotoxy(4, *linepoint); cout << "�A���\����" << enemy->getname() << "�F             ";
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
				if (player->getnowMP() < player->getskill2().getmagicost() || player->getskill2().getname() == "�L")
				{
					if (player->getskill2().getname() == "�L")
					{
						gotoxy(4, *linepoint); cout << "�A�٥��ǲߧޯ�                   ";
						linedetect(linepoint);
					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP�Ȥ���                        ";
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
						gotoxy(0, 7);   cout << "                                                     �ڴ��Q�L                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                        �Y�ϧڦA�j�A�@���ּu�{�U�ӧڴN�|��������                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          ���@�ѧڷQ���դF�A�Q�n���Ѯּu��²��                                                         ";
						Sleep(3000);
						gotoxy(0, 10);   cout << "                                                 �u�n�����ּu�N�i�H�F!!!!                                                           ";
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
					else if (player->getskill2().getname() == "�^������")
					{
						system("cls");
						PlaySound(TEXT("�^������.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(11800);
						gotoxy(0, 7);   cout << "                                              ���ﵴ��j�j���Z��O�q                                                   ";
						Sleep(3300);
						gotoxy(0, 8);   cout << "                                            �u�a�@�I�I�L�p���O�q�P�����                                                         ";
						Sleep(3100);
						gotoxy(0, 9);   cout << "                                                       ���N�O...                                                         ";
						Sleep(4800);
						gotoxy(0, 10);   cout << "                                                   !!�^�����@��!!                                                           ";
						Sleep(2000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					else if (player->getskill2().getname() == "�L�q�ųB")
					{
						PlaySound(NULL, NULL, NULL);
						system("cls");
						gotoxy(0, 7);   cout << "                                                   ���ڨӱЧA�@��                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                                �p��b�O�H��������өO?                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          ���׫�²��A�A�}�@�Ӥ�ĤH�j�����N��F                                                         ";
						Sleep(2000);
						PlaySound(TEXT("�L�q�ųB.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(1300);
						gotoxy(0, 10);   cout << "                                                     ���i�}                                                       ";
						Sleep(3000);
						gotoxy(0, 11);   cout << "                                                     �L�q�ųB!!                                                           ";
						Sleep(6000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					gotoxy(4, *linepoint); cout << "�A�ϥ�" << player->getskill2().getname() << "��ĤH�y���F";
					if (player->getATK() * player->getskill2().getindex() - enemy->getDEF() <= 0)
					{
						cout << "1�I�ˮ`                       ";
						enemy->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill2().getindex() * 1.35 - enemy->getDEF() << "�I�����ˮ`                       ";
							enemy->getdamage(player->getATK() * player->getskill2().getindex() * 1.35 - enemy->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill2().getindex() - enemy->getDEF() << "�I�ˮ`                            ";
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
						gotoxy(4, *linepoint); cout << "�A���\����" << enemy->getname() << "�F                         ";
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
				PlaySound(TEXT("�@��԰�bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (action == 'h')
			{
				showitem(player);
				gotoxy(30, 26); cout << "                          ";
				gotoxy(30, 25); cout << "   ��Je���}������";
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Jexit���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
						if (player->item[itemnum].getname() == "��j���\")
						{
							player->setpoison(0);
						}
						gotoxy(4, *linepoint); cout << "���\�ϥ�" << player->item[itemnum].getname() << "                     ";
						linedetect(linepoint);
						itemuse(player, itemnum);
						break;
					}
					system("cls");
					Fightscence(player, enemy);
					showitem(player);
					gotoxy(30, 26); cout << "                        ";
					gotoxy(30, 25); cout << "   ��Je���}������";
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
					cout << "�k�]���\                             ";
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
					cout << "�k�]����                            ";
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
					cout << "�A�ƷȪ����k�����F�ĤH������                 ";
				}
				else
				{
					enemy->attack(player);
				}
				linedetect(linepoint);
				//�Y����ܦ�q�P�]�O
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
		gotoxy(0, 27);     cout << " |   ATK(�п�Ja)   S1(�п�J1)   S2(�п�J2)   Item(�ϥνЫ�h)  �k�]�п�Jr      |                                    | ";
		gotoxy(0, 28);     cout << " |_____________________________________________________________________________________________________________________| ";

	}
	void enemygood(Player* player, Enemy* enemy)
	{
		srand(time(NULL));
		int randomnb;
		if (enemy->getname() == "Gobulin")
		{
			cout << "��o60�g��B100����   ";
			player->setnowEXP(60);
			player->setgold(100);
			randomnb = rand();
			if (randomnb % 100 <= 50)
			{
				cout << "�ԧQ�~:�����L���U           ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "�����L���U")
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
				cout << "�ԧQ�~:�L";
			}
		}
		else if (enemy->getname() == "Dragon")
		{
			cout << "��o500�g��B1000����   ";
			player->setnowEXP(500);
			player->setgold(1000);
			randomnb = rand();
			if (randomnb % 100 <= 70)
			{
				cout << "�ԧQ�~:�s��            ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "�s��")
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
				cout << "�ԧQ�~:�L";
			}
		}
		else if (enemy->getname() == "Devil")
		{
			cout << "��o120�g��B200����   ";
			player->setnowEXP(120);
			player->setgold(200);
			randomnb = rand();
			if (randomnb % 100 <= 30)
			{
				cout << "�ԧQ�~:�c�]�y��            ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "�c�]�y��")
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
				cout << "�ԧQ�~:�L";
			}
		}
		else if (enemy->getname() == "Ghost")
		{
			cout << "��o200�g��B150����   ";
			player->setnowEXP(200);
			player->setgold(150);
			randomnb = rand();
			if (randomnb % 100 <= 50)
			{
				cout << "�ԧQ�~:���F�H��          ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "���F�H��")
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
				cout << "�ԧQ�~:�L";
			}
		}
		else if (enemy->getname() == "Slime")
		{
			cout << "��o50�g��B50����   ";
			player->setnowEXP(50);
			player->setgold(50);
			randomnb = rand();
			if (randomnb % 100 <= 50)
			{
				cout << "�ԧQ�~:�v�ܩi�H�G        ";
				bool haveornot = 0;
				for (int i = 0; i < player->item.size(); i++)
				{
					if (player->item[i].getname() == "�v�ܩi�H�G")
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
			cout << "�ԧQ�~:�L";
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
			gotoxy(0, 24); cout << " |   |��J1�ʶR ��O:" << setw(3) << setfill('0') << shopkeeper->getshopArmor()[0].getcost() << "|     |��J2�ʶR ��O:" << setw(3) << setfill('0') << shopkeeper->getshopArmor()[1].getcost() << "|     |��J3�ʶR ��O:" << setw(3) << setfill('0') << shopkeeper->getshopArmor()[2].getcost() << "|"; gotoxy(82, 24); cout << "|   ATK: " << player->getATK(); gotoxy(101, 24); cout << "DEF: " << player->getDEF(); gotoxy(119, 24); cout << "|";
		}
		else if (shopkeeper->getindex() == 2)
		{
			gotoxy(0, 24); cout << " |   |��J1�ʶR ��O:" << setw(3) << setfill('0') << shopkeeper->getshopitem()[0].getcost() << "|     |��J2�ʶR ��O:" << setw(3) << setfill('0') << shopkeeper->getshopitem()[1].getcost() << "|     |��J3�ʶR ��O:" << setw(3) << setfill('0') << shopkeeper->getshopitem()[2].getcost() << "|"; gotoxy(82, 24); cout << "|   ATK: " << player->getATK(); gotoxy(101, 24); cout << "DEF: " << player->getDEF(); gotoxy(119, 24); cout << "|";

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
		gotoxy(0, 27); cout << " |                                                   �p�G���ʶR�п�J 0";
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
						gotoxy(0, 27); cout << " |�A�������n������               ";
						Sleep(2000);
					}
					else
					{
						player->setgold(-(shopkeeper->getshopArmor()[0].getcost()));
						//�]�w���ҭ�
						player->setarmorcharacter(0, shopkeeper->getshopArmor()[0].getatk(), shopkeeper->getshopArmor()[0].getdef(), shopkeeper->getshopArmor()[0].getagi(), shopkeeper->getshopArmor()[0].getluk());
						player->armor[0] = shopkeeper->getshopArmor()[0];
						//shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |�ʶR���\�A�w��A��          ";
						mciSendString(TEXT("play �ө��ʶR����.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '2')
				{

					if (player->getGold() < shopkeeper->getshopArmor()[1].getcost())
					{
						gotoxy(0, 27); cout << " |�A�������n������           ";
						Sleep(2000);
					}
					else
					{
						player->setgold(-(shopkeeper->getshopArmor()[1].getcost()));
						player->setarmorcharacter(1, shopkeeper->getshopArmor()[1].getatk(), shopkeeper->getshopArmor()[1].getdef(), shopkeeper->getshopArmor()[1].getagi(), shopkeeper->getshopArmor()[1].getluk());
						player->armor[1] = shopkeeper->getshopArmor()[1];
						shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |�ʶR���\�A�w��A��              ";
						mciSendString(TEXT("play �ө��ʶR����.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '3')
				{

					if (player->getGold() < shopkeeper->getshopArmor()[2].getcost())
					{
						gotoxy(0, 27); cout << " |�A�������n������            ";
						Sleep(2000);
					}
					else
					{
						player->setgold(-(shopkeeper->getshopArmor()[2].getcost()));
						player->setarmorcharacter(2, shopkeeper->getshopArmor()[2].getatk(), shopkeeper->getshopArmor()[2].getdef(), shopkeeper->getshopArmor()[2].getagi(), shopkeeper->getshopArmor()[2].getluk());
						player->armor[2] = shopkeeper->getshopArmor()[2];
						shopscence(shopkeeper, player);
						gotoxy(0, 27); cout << " |�ʶR���\�A�w��A��           ";
						mciSendString(TEXT("play �ө��ʶR����.wav"), NULL, 0, NULL);
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
						gotoxy(0, 27); cout << " |�A�������n������                     ";
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
						gotoxy(0, 27); cout << " |�ʶR���\�A�w��A��           ";
						mciSendString(TEXT("play �ө��ʶR����.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '2')
				{

					if (player->getGold() < shopkeeper->getshopitem()[1].getcost())
					{
						gotoxy(0, 27); cout << " |�A�������n������           ";
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
						gotoxy(0, 27); cout << " |�ʶR���\�A�w��A��        ";
						mciSendString(TEXT("play �ө��ʶR����.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
				else if (purchase == '3')
				{
					if (player->getGold() < shopkeeper->getshopitem()[2].getcost())
					{
						gotoxy(0, 27); cout << " |�A�������n������      ";
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
						gotoxy(0, 27); cout << " |�ʶR���\�A�w��A��                              ";
						mciSendString(TEXT("play �ө��ʶR����.wav"), NULL, 0, NULL);
						Sleep(2000);
					}
				}
			}
			system("cls");
			shopscence(shopkeeper, player);
			gotoxy(0, 27); cout << " |                                                   �p�G���ʶR�п�J 0";
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
			gotoxy(0, 10);     cout << " |                                                �п�J�n�����Ӥ�V�� r                             ------ \\          | ";
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
			gotoxy(0, 10);     cout << " |          / ------                            l �п�J�n�����Ӥ�V�� r                             ------ \\          | ";
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
			gotoxy(0, 10);     cout << " |          / ------                            l �п�J�n�����Ӥ�V��                                                 | ";
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
			gotoxy(0, 10);     cout << " |          / ------                            l �п�J�n�����Ӥ�V��                                                 | ";
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
			gotoxy(0, 10);     cout << " |          / ------                            l �п�J�n�����Ӥ�V�� r                             ------ \\          | ";
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
			gotoxy(0, 10);     cout << " |                                                �п�J�n�����Ӥ�V�� r                             ------ \\          | ";
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
			gotoxy(0, 10);     cout << " |                                                �п�J�n�����Ӥ�V�� r                             ------ \\          | ";
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
			gotoxy(0, 10);     cout << " |          / ------                            l �п�J�n�����Ӥ�V�� r                             ------ \\          | ";
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
				PlaySound(TEXT("�F�zbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 2)
			{
				PlaySound(TEXT("�˪Lbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 3)
			{
				PlaySound(TEXT("�h�Abgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else
			{
				PlaySound(TEXT("�a�cbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			}
			mainscence(player);
			system("cls");
			if (dungen[player->getx()][player->gety()].getEN() == 1)
			{
				gotoxy(0, 15);   cout << "                                                          �A���B�b�@���F�z                                     ";
				Sleep(2000);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 2)
			{
				gotoxy(0, 15);   cout << "                                                          �A���B�b�@���˪L                                     ";
				Sleep(2000);
			}
			else if (dungen[player->getx()][player->gety()].getEN() == 3)
			{
				gotoxy(0, 15);   cout << "                                                          �A���B�b�@���h�A�a                                   ";
				Sleep(2000);
			}
			else
			{
				gotoxy(0, 15);   cout << "                                                          �A���B�b���q���a�c����                               ";
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
					gotoxy(0, 15);   cout << "                                                          �A�J��F"; cout << dungen[player->getx()][player->gety()].getnpc()->getname();
					if (dungen[player->getx()][player->gety()].getEN() == 1)
					{
						PlaySound(TEXT("�F�zbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					else if (dungen[player->getx()][player->gety()].getEN() == 2)
					{
						PlaySound(TEXT("�˪Lbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					else if (dungen[player->getx()][player->gety()].getEN() == 3)
					{
						PlaySound(TEXT("�h�Abgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					else
					{
						PlaySound(TEXT("�a�cbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					Sleep(1500);
					shopsystem(dungen[player->getx()][player->gety()].getnpc(), player);
				}
				else if (dungen[player->getx()][player->gety()].getenemy() != NULL && retreatornot == 0)
				{
					system("cls");
					gotoxy(0, 15);   cout << "                                                          �A�J��F"; cout << dungen[player->getx()][player->gety()].getenemy()->getname();
					PlaySound(TEXT("�@��԰�bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					Sleep(1500);
					Fight(player, dungen[player->getx()][player->gety()].getenemy());
				}

				if (dungen[player->getx()][player->gety()].getEN() == 1 && retreatornot == 0)
				{
					PlaySound(TEXT("�F�zbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					randomnb = rand();
					if (randomnb % 100 <= 10)//�I��F�м�
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          �A�I��F�F�м�                              ";
						Sleep(2000);
						player->sethunger(-10);
						player->setthirsty(-10);
					}
					randomnb = rand();
					if (randomnb % 100 <= 30)//����w
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          �A�I��F��w                              ";
						Sleep(2000);
						player->setthirsty(50);
					}
				}
				else if (dungen[player->getx()][player->gety()].getEN() == 2 && retreatornot == 0)
				{
					PlaySound(TEXT("�˪Lbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					randomnb = rand();
					if (randomnb % 100 <= 50)//������
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          �A�b�˪L�̧��@�B����                    ";
						Sleep(2000);
						player->setthirsty(50);
					}
					randomnb = rand();
					if (randomnb % 100 >= 50)//�J��ʪ�
					{
						char action;
						system("cls");
						gotoxy(0, 15);   cout << "                                                          �A�b�˪L�̹J��@���ߤl                    ";
						gotoxy(0, 16);   cout << "                                                        �٤@��o�Xpeko~peko~���s�n                    ";
						gotoxy(0, 17);   cout << "                                                        ��Jc�Ӯ����A�Y�������h��J0                    ";
						
						while (1) {
							action = _getche();
							if (action == 'c')
							{
								randomnb = rand();
								if (randomnb % 100 <= 40)
								{
									gotoxy(0, 18);   cout << "                                                        �������\!                    ";
									gotoxy(0, 18);   cout << "                                                      �����״���10                    ";
									player->sethunger(10);
								}
								else
								{
									gotoxy(0, 18);   cout << "                                                        ��������!                    ";
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
							gotoxy(0, 15);   cout << "                                                          �A�b�˪L�̹J��@����                    ";
							Sleep(500);
							gotoxy(0, 16);   cout << "                                               �������@������""�S�̡A����ơA�i�H��@�U����?""                   ";
							Sleep(1000);
							gotoxy(0, 17);   cout << "                                                      �A�Pı�ͩR����F�¯١A���֫�a�k��                    ";

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
								cout << "���\�ò�";
							}
							else
							{
								gotoxy(50, 19);
								cout << "�ò楢�ѡA��5�ͩR";
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
				PlaySound(TEXT("�h�Abgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					randomnb = rand();
					if (randomnb % 100 >= 50)///�r��h�A�S��
					{
						system("cls");
						gotoxy(0, 15);   cout << "                                                          �A�I��F�h�A�r��                              ";
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
		gotoxy(0, 7);   cout << "                                             �t�δ���:�A�w�i�JBOSS��                                                   ";
		Sleep(3000);
		gotoxy(0, 8);   cout << "                                             ��:�A�N�O�a�U�����D��?                                                        ";
		Sleep(3000);
		gotoxy(0, 9);   cout << "                                                �]��:�i�̨ӧa!!!                                                         ";
		Sleep(3000);
		gotoxy(0, 10);   cout << "                                           �@���E�P���԰��Y�N�W�t                                                          ";
		Sleep(1500);
		system("cls");
		int bossstate = 1;
		PlaySound(TEXT("boss�԰�bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
				gotoxy(4, *linepoint); cout << "�A�ϥδ��q������ĤH�y���F";
				if (player->getATK() - finalboss->getDEF() <= 0)
				{
					cout << "1�I�ˮ`";
					finalboss->getdamage(1);
				}
				else
				{
					randomnb = rand();
					if (randomnb % 100 <= player->getLUK())
					{
						cout << player->getATK() * 1.35 - finalboss->getDEF() << "�I�����ˮ`";
						finalboss->getdamage(player->getATK() * 1.35 - finalboss->getDEF());
					}
					else
					{
						cout << player->getATK() - finalboss->getDEF() << "�I�ˮ`";
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
					gotoxy(4, *linepoint); cout << "�A���\����" << finalboss->getname() << "�F";
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
				if (player->getnowMP() < player->getskill1().getmagicost() || player->getskill1().getname() == "�L")
				{
					if (player->getskill1().getname() == "�L")
					{
						gotoxy(4, *linepoint); cout << "�A�٥��ǲߧޯ�                          ";
						linedetect(linepoint);

					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP�Ȥ���                             ";
						linedetect(linepoint);
					}
					continue;
				}
				else
				{

					gotoxy(4, *linepoint); cout << "�A�ϥ�" << player->getskill1().getname() << "��ĤH�y���F";
					if (player->getATK() * player->getskill1().getindex() - finalboss->getDEF() <= 0)
					{
						cout << "1�I�ˮ`";
						finalboss->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill1().getindex() * 1.35 - finalboss->getDEF() << "�I�����ˮ`";
							finalboss->getdamage(player->getATK() * player->getskill1().getindex() * 1.35 - finalboss->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill1().getindex() - finalboss->getDEF() << "�I�ˮ`";
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
						gotoxy(4, *linepoint); cout << "�A���\����" << finalboss->getname() << "�F";
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
				if (player->getnowMP() < player->getskill2().getmagicost() || player->getskill2().getname() == "�L")
				{
					if (player->getskill2().getname() == "�L")
					{
						gotoxy(4, *linepoint); cout << "�A�٥��ǲߧޯ�                                 ";
						linedetect(linepoint);
					}
					else
					{
						gotoxy(4, *linepoint); cout << "MP�Ȥ���                                   ";
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
						gotoxy(0, 7);   cout << "                                                     �ڴ��Q�L                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                        �Y�ϧڦA�j�A�@���ּu�{�U�ӧڴN�|��������                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          ���@�ѧڷQ���դF�A�Q�n���Ѯּu��²��                                                         ";
						Sleep(3000);
						gotoxy(0, 10);   cout << "                                                 �u�n�����ּu�N�i�H�F!!!!                                                           ";
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
					else if (player->getskill2().getname() == "�^������")
					{
						system("cls");
						PlaySound(TEXT("�^������.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(11800);
						gotoxy(0, 7);   cout << "                                              ���ﵴ��j�j���Z��O�q                                                   ";
						Sleep(3300);
						gotoxy(0, 8);   cout << "                                            �u�a�@�I�I�L�p���O�q�P�����                                                         ";
						Sleep(3100);
						gotoxy(0, 9);   cout << "                                                       ���N�O...                                                         ";
						Sleep(4800);
						gotoxy(0, 10);   cout << "                                                   !!�^�����@��!!                                                           ";
						Sleep(2000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					else if (player->getskill2().getname() == "�L�q�ųB")
					{
						PlaySound(NULL, NULL, NULL);
						system("cls");
						gotoxy(0, 7);   cout << "                                                   ���ڨӱЧA�@��                                                   ";
						Sleep(3000);
						gotoxy(0, 8);   cout << "                                                �p��b�O�H��������өO?                                                         ";
						Sleep(3000);
						gotoxy(0, 9);   cout << "                                          ���׫�²��A�A�}�@�Ӥ�ĤH�j�����N��F                                                         ";
						Sleep(2000);
						PlaySound(TEXT("�L�q�ųB.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(1300);
						gotoxy(0, 10);   cout << "                                                     ���i�}                                                       ";
						Sleep(3000);
						gotoxy(0, 11);   cout << "                                                     �L�q�ųB!!                                                           ";
						Sleep(6000);
						*linepoint = 21;
						system("cls");
						Fightscence(player, finalboss);
					}
					gotoxy(4, *linepoint); cout << "�A�ϥ�" << player->getskill2().getname() << "��ĤH�y���F";
					if (player->getATK() * player->getskill2().getindex() - finalboss->getDEF() <= 0)
					{
						cout << "1�I�ˮ`";
						finalboss->getdamage(1);
					}
					else
					{
						randomnb = rand();
						if (randomnb % 100 <= player->getLUK())
						{
							cout << player->getATK() * player->getskill2().getindex() * 1.35 - finalboss->getDEF() << "�I�����ˮ`";
							finalboss->getdamage(player->getATK() * player->getskill2().getindex() * 1.35 - finalboss->getDEF());
						}
						else
						{
							cout << player->getATK() * player->getskill2().getindex() - finalboss->getDEF() << "�I�ˮ`";
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
						gotoxy(4, *linepoint); cout << "�A���\����" << finalboss->getname() << "�F";
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
				PlaySound(TEXT("boss�԰�bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (action == 'h')
			{
				showitem(player);
				gotoxy(30, 26); cout << "                          ";
				gotoxy(30, 25); cout << "   ��Je���}������";
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J yes" << "��Jexit���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
							gotoxy(0, 14); cout << "�ϥνп�J y" << "��Je���}������" << endl;
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
						if (player->item[itemnum].getname() == "��j���\")
						{
							player->setpoison(0);
						}
						gotoxy(4, *linepoint); cout << "���\�ϥ�" << player->item[itemnum].getname() << "                                 ";
						linedetect(linepoint);
						itemuse(player, itemnum);
						break;
					}
					system("cls");
					Fightscence(player, finalboss);
					showitem(player);
					gotoxy(30, 26); cout << "                        ";
					gotoxy(30, 25); cout << "   ��Jexit���}������";
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
				cout << "BOSS�Ԥ���k�]                              ";
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
					gotoxy(0, 7);   cout << "                                             �y�ɶ��·t�q�|�Pŧ��                                                   ";
					Sleep(3000);
					gotoxy(0, 8);   cout << "                                        �{�p���`�몺���j����ӪŶ�                                                        ";
					Sleep(3000);
					gotoxy(0, 9);   cout << "                                              �]��:�����ڪ����ۧa!!!                                                         ";
					Sleep(3000);
					gotoxy(0, 10);   cout << "                                              !!!���`�Į�!!!                                                           ";
					mciSendString(TEXT("play boss�ޯ୵��.wav"), NULL, 0, NULL);
					Sleep(1000);
					*linepoint = 21;
					system("cls");
					Fightscence(player, finalboss);
					gotoxy(4, *linepoint);
					finalboss->skill2atk(player);
					linedetect(linepoint);
				}

				//�Y����ܦ�q�P�]�O
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
