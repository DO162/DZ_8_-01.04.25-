#include "header.h"

int main() {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));
	rand();
	system("title Bomberman");

	// cursor hide
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 100; // 1-100
	SetConsoleCursorInfo(h, &cursor);

	int health = 100;
	int coins_collected = 0;
	int total_coins = 0;
	const int HEIGHT = 25;
	const int WIDTH = 65;
	int map[HEIGHT][WIDTH] = {};
	// ASCII Table
	//for (int i = 0; i < 256; i++)
	//{
	//	cout << (char)i << " - " << i << "\n";
	//}

	// MODEL (логіка заповнення масиву)
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			map[y][x] = rand() % 5; // 0 1 2 3

			// рамка по краях
			if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
				map[y][x] = GameObject::WALL;

			// отвори для входу і виходу
			if (x == 0 && y == 2 ||
				x == 1 && y == 2 ||
				x == 2 && y == 2 ||

				x == WIDTH - 1 && y == HEIGHT - 3 ||
				x == WIDTH - 2 && y == HEIGHT - 3 ||
				x == WIDTH - 3 && y == HEIGHT - 3)
				map[y][x] = GameObject::HALL;

			if (map[y][x] == GameObject::ENEMY) {
				int r = rand() % 10; // 0 1 2 3 4 5 6 7 8 9
				if (r != 0) {
					map[y][x] = GameObject::HALL;
				}
			}

			if (map[y][x] == GameObject::MEDKIT) {
				int m = rand() % 40; // 0 1 2 3 4 5 6 7 8 9
				if (m != 0) {
					map[y][x] = GameObject::HALL;
				}
			}
		}
	}

	///////////////////////////////////////////////////////////

	// VIEW (подання - як буде виглядати ігрова локація)
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			switch (map[y][x]) {
			case GameObject::HALL: // 0
				// як показати коридор
				SetConsoleTextAttribute(h, Color::BLACK);
				cout << " ";
				break;
			case GameObject::WALL: // 1
				SetConsoleTextAttribute(h, Color::DARKGREEN);
				// cout << "#";
				cout << (char)178;
				break;
			case GameObject::COIN:
				SetConsoleTextAttribute(h, Color::YELLOW);
				cout << ".";
				total_coins++;
				break;
			case GameObject::ENEMY:
				SetConsoleTextAttribute(h, Color::RED);
				cout << "O";
				break;
			case GameObject::MEDKIT:
				SetConsoleTextAttribute(h, Color::PURPLE);
				cout << "+";
				break;
			}

		}
		cout << "\n";
	}

	////////////////////////////////////////////////////////////
	// показ ГГ
	COORD brk;
	brk.X = 45;
	brk.Y = 13;

	COORD hero;
	hero.X = 0;
	hero.Y = 2;
	SetConsoleCursorPosition(h, hero);
	SetConsoleTextAttribute(h, Color::BLUE);
	cout << "O";

	COORD coins_tot;
	coins_tot.X = WIDTH + 1;
	coins_tot.Y = 0;
	SetConsoleCursorPosition(h, coins_tot);
	SetConsoleTextAttribute(h, Color::DARKYELLOW);
	cout << "TOTAL_COINS: ";
	SetConsoleTextAttribute(h, Color::YELLOW);
	cout << total_coins;

	COORD health_info;
	health_info.X = WIDTH + 35;
	health_info.Y = 0;
	SetConsoleCursorPosition(h, health_info);
	SetConsoleTextAttribute(h, Color::RED);
	cout << "HEALTH: ";
	SetConsoleTextAttribute(h, Color::WHITE);
	cout << health;


	// ігровий двигунчик
	while (true) {
		int code = _getch(); // get character
		if (code == 224) {
			code = _getch();
		}

		COORD old_position = hero;
		bool has_been_moved = false; // false - пересування не було

		// cout << code << "\n";
		switch (code) {
		case Key::LEFT:
			if (hero.X > 0 && map[hero.Y][hero.X - 1] != GameObject::WALL) {
				has_been_moved = true;
				hero.X--;
			}
			break;
		case Key::RIGHT:
			if (map[hero.Y][hero.X + 1] != GameObject::WALL) {
				has_been_moved = true;
				hero.X++;
			}
			break;
		case Key::UP:
			if (map[hero.Y - 1][hero.X] != GameObject::WALL) {
				has_been_moved = true;
				hero.Y--;
			}
			break;
		case Key::DOWN:
			if (map[hero.Y + 1][hero.X] != GameObject::WALL) {
				has_been_moved = true;
				hero.Y++;
			}
			break;
		}

		if (has_been_moved) {
			// стирання ГГ в "старих" координатах
			SetConsoleCursorPosition(h, old_position);
			SetConsoleTextAttribute(h, Color::BLACK);
			cout << " ";
			// перемальовка ГГ в нових координатах
			SetConsoleCursorPosition(h, hero);
			SetConsoleTextAttribute(h, Color::BLUE);
			cout << "O";
		}

		// приклад перевірки на перетинання з якимось об'єктом в лабірінті

		//------
		//------
		//------
		//------
		//---------------------------------Задание 2-----------------------------------
		if (map[hero.Y][hero.X] == GameObject::MEDKIT) {
			if (health < 100) {
				health += 25;
				if (health > 100) {
					health = 100;
				}
				map[hero.Y][hero.X] = GameObject::HALL;

				// Оновити виведення здоров'я
				COORD health_info;
				health_info.X = WIDTH + 35;
				health_info.Y = 0;
				SetConsoleCursorPosition(h, health_info);
				SetConsoleTextAttribute(h, Color::RED);
				cout << "HEALTH: ";
				SetConsoleTextAttribute(h, Color::WHITE);
				cout << health;
			}
		}


		if (map[hero.Y][hero.X] == GameObject::ENEMY) {
			health -= 25;
			if (health < 0) {
				health = 0;
			}
			COORD health_info;
			health_info.X = WIDTH + 35;
			health_info.Y = 0;
			SetConsoleCursorPosition(h, health_info);
			SetConsoleTextAttribute(h, Color::RED);
			cout << "HEALTH: ";
			SetConsoleTextAttribute(h, Color::WHITE);
			cout << health << "  ";

			if (health == 0) {
				SetConsoleOutputCP(1251);
				system("cls");

				COORD health_in;
				health_in.X = 45;
				health_in.Y = 13;
				
				SetConsoleCursorPosition(h, health_in);
				SetConsoleTextAttribute(h, Color::RED);
				cout << "Поразка - здоров'я закінчилося!\n";
				break;
			}
		}
		//------
		//------
		//------
		//------


		if (map[hero.Y][hero.X] == GameObject::COIN) {
			// cout << "COIN";
			coins_collected++;
			total_coins--;
			map[hero.Y][hero.X] = GameObject::HALL;

			COORD coins_info;
			coins_info.X = WIDTH + 1;
			coins_info.Y = 2;
			SetConsoleCursorPosition(h, coins_info);
			SetConsoleTextAttribute(h, Color::DARKYELLOW);
			cout << "COINS: ";
			SetConsoleTextAttribute(h, Color::YELLOW);
			cout << coins_collected;


			//------
		    //------
		    //------
		    //------
		    //---------------------------------Задание 2-----------------------------------
			COORD coins_n;
			coins_n.X = WIDTH + 1;
			coins_n.Y = 4;
			SetConsoleOutputCP(1251);

			coins_num(total_coins, h, coins_n);

			SetConsoleOutputCP(866);
			//------
		    //------
		    //------
		    //------
		}



		//------
		//------
		//------
		//------
		//---------------------------------Задание 1-----------------------------------

		SetConsoleOutputCP(1251);

		if (brak(WIDTH, HEIGHT, hero, brk, h)) {
			break;
		}

		SetConsoleOutputCP(866);

		//------
		//------
		//------
		//------
	}


	Sleep(INFINITE);
}