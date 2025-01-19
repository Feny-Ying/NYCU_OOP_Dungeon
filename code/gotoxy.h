#ifndef GOTOXY_H_INCLUDED
#define GOTOXY_H_INCLUDED

#include <iostream>
#include<fcntl.h>
#include<process.h>
#include <cstdlib> 
#include <cmath>
#include <chrono>
#include <list> 
#include <conio.h> 
#include <windows.h> 
#include <iomanip>
#include<time.h>
using namespace std;



//void gotoxy(double x, double y); // allows to move inside the terminal using coordinates // the type is double, so objects can move less than 1 unit 

void gotoxy(double x, double y) // allows to move inside the terminal using coordinates 
{	// the type is double, so objects can move less than 1 unit 
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x; // start from 0
	dwPos.Y = y; // start from 0
	SetConsoleCursorPosition(hCon, dwPos);
}

#endif
