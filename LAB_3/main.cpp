#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdarg.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <deque>
#include <vector>
#include <stdexcept>

using namespace std;

void enterNum(int* num) {
	*num = 0;

	int counter = 0;

	while (counter < 9) {
		char butt = _getch();
		if (butt > 47 && butt < 58) {
			*num = (*num * 10) + (butt - 48);
			printf("%c", butt);
			counter++;
		}
		else if (butt == 8 && counter != 0) {
			*num /= 10;
			if (*num == 1) {
				*num = 0;
			}
			putchar('\b');
			printf(" ");
			putchar('\b');
			if (counter > 0) counter--;
		}
		else if (butt == 13) {
			break;
		}
	}
	printf("\n");
}

void SetColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

class Menu {
	int bg = 2;
	int countParam;
	int paragraph;
	int border;
	bool running = true;

	typedef void (*voidFunctionPtr)();

	Menu* main = this, * parent = NULL;
	string* arr;
	string header;

public:

	Menu* sub;
	voidFunctionPtr* function = NULL;

	Menu() { countParam = 0; paragraph = 1; arr = NULL; border = 0; sub = NULL; }

	void CreateMenu(int num, const char* name, ...) {
		if (main->parent == NULL) main->header = "������� ����";

		main->border = num;
		va_list args;
		va_start(args, num);

		main->function = new voidFunctionPtr[num];
		for (int i = 0; i < num; i++) main->function[i] = NULL;
		main->arr = new string[num];
		main->sub = new Menu[num];
		for (int i = 0; i < num; i++) main->sub[i].parent = main;
		int i = 0;
		while (num != 0) {
			main->arr[i] = va_arg(args, char*);
			main->countParam++;
			i++;
			--num;
		}
		va_end(args);
	}

	void ShowMenu() {
		system("cls");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		string menu;
		if (main->parent != NULL) main->header = main->parent->arr[main->parent->paragraph - 1];
		menu += "\n\n\n\n\n\n\n\n\t\t\t\t\t\t+--------------------+\n\t\t\t\t\t\t|";

		for (int j = 0; j < (20 - main->header.length()) / 2; j++) menu += " ";
		menu += main->header;
		for (int j = 0; j < 20 - (main->header.length() + (20 - main->header.length()) / 2); j++) menu += " ";
		menu += "|\n\t\t\t\t\t\t+--------------------+\n";

		if (main->arr != NULL) {
			for (int i = 0; i < main->countParam; i++) {
				menu += "\t\t\t\t\t\t|";
				if (i == (main->paragraph - 1)) {
					cout << menu;
					SetColor(0, bg);
					cout << main->arr[i];
					if (main->arr[i].length() < 20) {
						for (int j = 0; j < 20 - main->arr[i].length(); j++) cout << " ";
					}
					SetColor(7, 0);
					menu.clear();
				}
				else {
					menu += main->arr[i];
					if (main->arr[i].length() < 20) {
						for (int j = 0; j < 20 - main->arr[i].length(); j++) menu += " ";
					}
				}
				menu += "|\n\t\t\t\t\t\t+--------------------+\n";
			}
			cout << menu;
		}
		else main = main->parent;

	}

	void Navigation(bool* running) {
		char keycap = _getch();

		if (keycap == 80) main->paragraph++;
		else if (keycap == 72) main->paragraph--;
		else if (keycap == 13) {
			if (main->function[main->paragraph - 1] == NULL && main->sub[main->paragraph - 1].arr != NULL) main = &main->sub[main->paragraph - 1];
			else if (main->function[main->paragraph - 1] != NULL) {
				system("cls");
				main->function[main->paragraph - 1]();
				_getch();
			}
		}
		else if (keycap == 27) {
			if (main->parent != NULL) {
				main->paragraph = 1;
				main = main->parent;
			}
			else if (main->parent == NULL) *running = false;
		}
		else if (keycap == 83) {
			vector<string> arr = { "�����", "������", "�������", "�������", "�������", "Ƹ����" };
			int paragraph = 0;
			char keycap = NULL;
			while (keycap != 27) {
				system("cls");
				SetConsoleCP(1251);
				SetConsoleOutputCP(1251);

				string menu;
				string header = "���������";
				menu += "\n\n\n\n\n\n\n\n\t\t\t\t\t\t+--------------------+\n\t\t\t\t\t\t|";

				for (int j = 0; j < (20 - header.length()) / 2; j++) menu += " ";
				menu += header;
				for (int j = 0; j < 20 - (header.length() + (20 - header.length()) / 2); j++) menu += " ";
				menu += "|\n\t\t\t\t\t\t+--------------------+\n";

				for (int i = 0; i < 6; i++) {
					menu += "\t\t\t\t\t\t|";
					if (i == paragraph) {
						cout << menu;
						SetColor(0, i + 1);
						cout << arr[i];
						if (arr[i].length() < 20) {
							for (int j = 0; j < 20 - arr[i].length(); j++) cout << " ";
						}
						SetColor(7, 0);
						menu.clear();
					}
					else {
						menu += arr[i];
						if (arr[i].length() < 20) {
							for (int j = 0; j < 20 - arr[i].length(); j++) menu += " ";
						}
					}
					menu += "|\n\t\t\t\t\t\t+--------------------+\n";
				}
				cout << menu;

				keycap = _getch();

				if (keycap == 80) paragraph++;
				else if (keycap == 72) paragraph--;
				else if (keycap == 13) {
					bg = paragraph + 1;
					keycap = 27;
				}

				if (paragraph > 5) paragraph = 0;
				else if (paragraph < 0) paragraph = 5;
			}
		}

		if (main->paragraph > main->border) main->paragraph = 1;
		else if (main->paragraph < 1) main->paragraph = main->border;
	}

	void StartMenu() {
		while (running) {
			ShowMenu();
			Navigation(&running);
		}
	}
};

class CostErr {
	int ErrCode;
public:
	CostErr() : ErrCode(0) {}
	CostErr(int num) : ErrCode(num) {}
	void what() { cout << "\n\n������ ������� �������!\n"; }
};

class CarService 
{
	int cost;
	string name;
	string _class;
	int productClass;
public:
	CarService() : cost(0), productClass(0) {}

	void SetCost(int num) { cost = num; }
	int GetCost() { return cost; }

	void SetName(string _name) { name = _name; }
	string GetName() { return name; }

	void SetProdClass(int num) 
	{
		productClass = num;
		if (num == 1) _class = "�������� ��";
		else if (num == 2) _class = "������";
		else if (num == 3) _class = "���������";
	}
	bool isPlannedMaintenance() 
	{
		if (productClass == 1) return true;
		else return false;
	}
	bool isRepair() 
	{
		if (productClass == 2) return true;
		else return false;
	}
	bool isDetailing() 
	{
		if (productClass == 3) return true;
		else return false;
	}

	friend ostream& operator<<(ostream& stream, CarService& obj) 
	{
		cout.setf(ios::right);
		cout.width(30);
		cout.setf(ios::showpos);
		cout.setf(ios::showpoint);
		cout.setf(ios::fixed);
		cout << obj._class << " " << obj.GetName() << " " << obj.GetCost() << "$" << endl;
		cout.unsetf(ios::right);
		cout.unsetf(ios::showpos);
		cout.unsetf(ios::showpoint);
		cout.unsetf(ios::fixed);
		return stream;
	}
};

class PlannedMaintenance : public CarService {
public:
	PlannedMaintenance(string name, int cost) { SetProdClass(1); SetName(name); if (cost < 0) throw 1; SetCost(cost); }
	~PlannedMaintenance() { cout << "������ ������� �������!"; }
};

class Repair : public CarService {
public:
	Repair(string name, int cost) { SetProdClass(2); SetName(name); SetCost(cost); }
};

class Detailing : public CarService {
public:
	Detailing(string name, int cost) { SetProdClass(3); SetName(name); SetCost(cost); }
};

class Cart {
	vector<CarService> cart;
	int totalCost = 0;
public:
	Cart() : cart(NULL) {}
	void AddSome(CarService* obj) {
		cart.push_back(*obj);
		totalCost += obj->GetCost();
	}
	void ShowCart() {
		if (cart.size() == 0) throw 1;
		for (int i = 0; i < cart.size(); i++) {
			cout << i + 1 << ") " << cart[i] << endl;
		}
		cout << "�������� ���������: " << totalCost;
	}
	int GetTotalCost() { return totalCost; }
};

vector<CarService> arr;
Cart cart;

template <class T> T enter() {
	T tmp;
	while (true) {
		cin >> tmp;
		if (cin.good()) {
			break;
		}
		else if (cin.fail()) {
			cin.clear();
			cin.ignore(5, '\n');
		}
	}
	return tmp;
}

void TermFunc() {
	cout << "���� ������� ������� ����������";
	exit(-1);
}

void addPlannedMaintenance() {
	PlannedMaintenance* tmp;
	string name;
	int cost;
	while (1) {
		system("cls");
		cout << "������� ����� ����: ";
		name = enter<string>();
		cout << "������� ���������: ";
		cost = enter<int>();
		try {
			tmp = new PlannedMaintenance(name, cost);
			arr.push_back(*tmp);
			break;
		}
		catch (...) {
			cout << "\n\n������ ������� �������!\n";
			char sym;
			cout << "��������� ����? (y/n): ";
			sym = enter<char>();
			if (sym == 'n') break;
		}
	}
}

void addRepair() {
	Repair* tmp;
	string name;
	int cost;
	while (1) {
		system("cls");
		cout << "������� �������� �������� ��� �������: ";
		name = enter<string>();
		cout << "������� ���������: ";
		cost = enter<int>();
		try {
			if (cost < 0) throw new CostErr(cost);
			tmp = new Repair(name, cost);
			arr.push_back(*tmp);
			break;
		}
		catch (CostErr* exeption) {
			exeption->what();
			char sym;
			cout << "��������� ����? (y/n): ";
			sym = enter<char>();
			if (sym == 'n') break;
		}
	}
}

void addDetailing() {
	Detailing* tmp;
	string name;
	int cost;
	while (1) {
		system("cls");
		cout << "������� �������� ������: ";
		name = enter<string>();
		cout << "������� ���������: ";
		cost = enter<int>();
		try {
			if (cost < 0) throw cost;
			tmp = new Detailing(name, cost);
			arr.push_back(*tmp);
			break;
		}
		catch (int exeption) {
			cout << "\n\n������ ������� ������� (��������� " << exeption << " < 0)\n";
			char sym;
			cout << "��������� ����? (y/n): ";
			sym = enter<char>();
			if (sym == 'n') break;
		}
	}
}

void ShowAll() {
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			cout << i + 1 << ") " << arr[i] << endl;
		}
	}
	catch (int) {
		cout << "��� �������!";
	}
}

void ShowPlannedMaintenance() {
	int counter = 1;
	bool exist = false;
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i].isPlannedMaintenance()) {
				cout << counter << ") " << arr[i] << endl;
				counter++;
				exist = true;
			}
		}
		if (exist == false) throw false;
	}
	catch (int) {
		cout << "��� �������!";
	}
	catch (bool) {
		cout << "��� ������� ������ ���������!";
	}
}

void ShowRepair() {
	int counter = 1;
	bool exist = false;
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i].isRepair()) {
				cout << counter << ") " << arr[i] << endl;
				counter++;
				exist = true;
			}
		}
		if (exist == false) throw false;
	}
	catch (int) {
		cout << "��� �������!";
	}
	catch (bool) {
		cout << "��� ������� ������ ���������!";
	}
}

void ShowDetailing() {
	int counter = 1;
	bool exist = false;
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i].isDetailing()) {
				cout << counter << ") " << arr[i] << endl;
				counter++;
				exist = true;
			}
		}
		if (exist == false) throw false;
	}
	catch (int) {
		cout << "��� �������!";
	}
	catch (bool) {
		cout << "��� ������� ������ ���������!";
	}
}

void SetCart() {
	while (1) {
		system("cls");
		ShowAll();

		int choise;
		cout << "������� ����� ������: ";
		cin >> choise;
		try {
			if (choise < 1 || choise > arr.size()) throw 1;
			cart.AddSome(&arr[choise - 1]);
			break;
		}
		catch (int) {
			cout << "\n\n������ ������ ���!";
			char sym;
			cout << "��������� ����? (y/n): ";
			cin >> sym;
			if (sym == 'n') break;
		}
	}
}

void ShowCart() {
	try {
		cart.ShowCart();
	}
	catch (int) {
		cout << "������� �����\n\n";
		cout << "�������� ���������: " << cart.GetTotalCost() << "$";
	}
}

int main() {
	Menu menu;
	set_terminate(TermFunc);

	menu.CreateMenu(3, "�������� �����", "����������� ������", "�������");
	{
		menu.sub[0].CreateMenu(3, "�������� ��", "������", "���������");
		{
			menu.sub[0].function[0] = addPlannedMaintenance;
			menu.sub[0].function[1] = addRepair;
			menu.sub[0].function[2] = addDetailing;
		}
		menu.sub[1].CreateMenu(4, "�������� ��", "������", "���������", "���");
		{
			menu.sub[1].function[0] = ShowPlannedMaintenance;
			menu.sub[1].function[1] = ShowRepair;
			menu.sub[1].function[2] = ShowDetailing;
			menu.sub[1].function[3] = ShowAll;
		}
		menu.sub[2].CreateMenu(2, "�������� � �������", "�������� �������");
		{
			menu.sub[2].function[0] = SetCart;
			menu.sub[2].function[1] = ShowCart;
		}
	}

	bool running = true;
	while (running)
	{
		menu.ShowMenu();
		menu.Navigation(&running);
	}
}