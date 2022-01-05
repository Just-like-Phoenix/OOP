#include <iostream>
#include <conio.h>
#include <stdarg.h>
#include <fstream>
#include <Windows.h>

using namespace std;

int keyget(int num)
{
	char button = 0;
	button = _getch();
	if (button == 27) return 69;
	if (button == 13) return 27;
	if (button == 72)  num--; // КОД 72 соответсвует Стрелке вверх
	if (button == 80)  num++; // КОД 80 соответсвует Стрелке вниз
	return num;
}

template<class type>
type Max(type a, type b) {
	const type_info& t = typeid(type); //получение ссылки t на
	const char* s = t.name();
	if (!strcmp(s, "char *")) {
		int i = 0, j = 0;
		while ((char)(a + i) != '\0') {
			i++;
		}
		while ((char)(b + j) != '\0') {
			j++;
		}
		if (i > j) return a;
		else return b;
	}
	if (a > b) return a;
	else return b;
}

void main_menu(int num)
{

	char a[] = { "12\0" };
	char b[] = { '1', '2', '3' , '\0' };

	int c, d;
	c = 5, d = 10;

	int key = 0;
	int buff = 0;
	const int SIZE = 2;
	do
	{
		system("cls");

		if (buff == 27)
		{
			switch (key)
			{
			case 0:
				cout << "Большая строка - " << Max(a, b) << endl;
				system("pause");
				break;
			case 1:
				cout << "Больший элемент - " << Max(c, d) << endl;
				system("pause");
				break;
			}

			system("cls");
		}
		if (buff < 0)
			key = SIZE - 1;
		else
			key = buff % SIZE;
		char** title;
		title = new char* [SIZE] {(char*)"Большая строка", (char*)"Больший элемент"};
		for (int i = 0; i < SIZE; i++)
		{
			if (key == i)
			{
				std::cout << ">" << title[i] << "<\n";
			}
			else
			{
				std::cout << title[i] << "\n";
			}
		}
		buff = keyget(key);
	} while (buff != 69);
	return;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	main_menu(0);
}