#include <iostream>
#include <windows.h> // COORD HANDLE SetConsoleTextAttribute SetConsoleCursorPosition
#include <conio.h> // _getch
#include <stdlib.h>
using namespace std;

enum GameObject : short { HALL, WALL, COIN, ENEMY, MEDKIT };
enum Color : short {
	BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
	PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN,
	CYAN, RED, PINK, YELLOW, WHITE
};
enum Key : short {
	LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80,
	ENTER = 13, SPACE = 32, ESCAPE = 27, BACKSPACE = 8
};



//------
//------
//------
//------
//---------------------------------Задание 1-----------------------------------
bool brak(int WIDTH, int HEIGHT, COORD hero, COORD brk, HANDLE h) {

	if (hero.X == WIDTH - 1 && hero.Y == HEIGHT - 3) {
		system("cls"); // очистка єкрана
		SetConsoleCursorPosition(h, brk);
		SetConsoleTextAttribute(h, Color::GREEN);
		cout << "Перемога - знайдено вихід!" << "\n";
		return true;
	}
	return false;
}
//------
//------
//------
//------
//---------------------------------Задание 2-----------------------------------
void coins_num(int total_coins, HANDLE h, COORD coins_n) {
	if (total_coins == 100) { // здесь написано 100 чтобы знать что код работает, а так тут 0(некоторые монеты нельзя подобрать)
		SetConsoleCursorPosition(h, coins_n);
		SetConsoleTextAttribute(h, Color::YELLOW);
		cout << "Перемога - монети зібрано!" << "\n";
	}
}