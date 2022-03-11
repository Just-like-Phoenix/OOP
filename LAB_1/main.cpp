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
		if (main->parent == NULL) main->header = "Главное меню";

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
			vector<string> arr = { "Синий", "Зелёный", "Голубой", "Красный", "Розовый", "Жёлтый" };
			int paragraph = 0;
			char keycap = NULL;
			while (keycap != 27) {
				system("cls");
				SetConsoleCP(1251);
				SetConsoleOutputCP(1251);

				string menu;
				string header = "НАСТРОЙКА";
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

class Person
{
	int TicketNum;
	double BYN = rand() % 100000;
	string name;

public:
	Person() : TicketNum(0) {}
	Person(Person& obj) :TicketNum (obj.TicketNum) {}

	double MAX_CASH_IN_LEGAL = 100000, MAX_CASH_OUT_LEGAL=1000000;
	double MAX_CASH_IN_PHY = 1500, MAX_CASH_OUT_PHY = 5000;

	double GetCash() { return BYN; }
	void SetCash(double cash) { BYN = cash; }

	int GetTicket() { return TicketNum; }
	void SetTicket(int _tickNum) { TicketNum = _tickNum; }

	string GetName() { return name; }
	void SetName(string _name) { name = _name; }

	virtual void ConfirmTicket()  = 0;
};

class phy_entity : public Person
{
public:
	phy_entity() { }
	
	void ConfirmTicket() {
		string tmp;

		cout << "Введите инициалы ( Фамилия И.О.): ";
		cin >> tmp;
		Person::SetName(tmp);
	}
};

class legal_entity : public Person
{
public:
	legal_entity() { }

	void ConfirmTicket() {
		string tmp;

		cout << "Введите название организации: ";
		cin >> tmp;
		Person::SetName(tmp);
	}
};

template <class T>
struct Status {
	T* ptr;
	int counter;
};

template <class T>
class SmartPtr {
	Status<T>* smartPtr;
public:
	SmartPtr(T* ptr) {
		if (!ptr)
			smartPtr = NULL;
		else {
			smartPtr = new Status<T>();
			smartPtr->ptr = ptr;
			smartPtr->counter = 1;
		}
	}

	SmartPtr(const SmartPtr& obj) : smartPtr(obj.smartPtr) {
		if (smartPtr) smartPtr->counter++;
	}

	~SmartPtr() {
		if (smartPtr) {
			smartPtr->counter--;
			if (smartPtr->counter == 0) {
				delete smartPtr->ptr;
				delete smartPtr;
			}
		}
	}

	SmartPtr& operator=(const SmartPtr& obj) {
		if (smartPtr) {
			smartPtr->counter--;
			if (smartPtr->counter == 0) {
				delete smartPtr->ptr;
				delete smartPtr;
			}
		}
		smartPtr = obj.smartPtr;

		if (smartPtr) smartPtr->counter++;
		return *this;
	}

	T* operator->() {
		if (smartPtr) return smartPtr->ptr;
		else return NULL;
	}

	void showCounter() {
		cout << "Значение счетчика для объекта " << smartPtr->ptr << " равно: " << smartPtr->counter << endl;
	}
};

template <class T>
class Transaction {
public:
	T* currentState;
	T* prevState;

	Transaction() : prevState(NULL), currentState(new T) {}
	Transaction(const Transaction& obj) : currentState(new T(*(obj.currentState))), prevState(NULL) {}
	~Transaction() {
		delete currentState;
		delete prevState;
	}

	Transaction& operator=(const Transaction& obj) {
		if (this != &obj) {
			delete currentState;
			currentState = new T(*(obj.currentState));
		}
		return *this;
	}

	void BeginTransactions() {
		delete prevState;
		prevState = currentState;
		currentState = new T(*prevState);
	}

	void Commit() {
		delete prevState;
		prevState = NULL;
	}

	void deleteTransactions() {
		if (prevState != NULL) {
			delete currentState;
			currentState = prevState;
			prevState = NULL;
		}
	}

	T* operator->() {
		return currentState;
	}
};

int phy_counter = 1;
int leg_counter = 1;
vector<SmartPtr<Transaction<legal_entity>>> leg;
vector<SmartPtr<Transaction<phy_entity>>> phy;

void add_phy()
{
	SmartPtr<Transaction<phy_entity>> tmp(new Transaction<phy_entity>);
	tmp->currentState->ConfirmTicket();
	phy.push_back(tmp);
	tmp->currentState->SetTicket(phy_counter);
	tmp->Commit();
	phy_counter++;
}

void add_leg()
{
	SmartPtr<Transaction<legal_entity>> tmp(new Transaction<legal_entity>);
	tmp->currentState->ConfirmTicket();
	leg.push_back(tmp);
	tmp->currentState->SetTicket(leg_counter);
	tmp->Commit();
	leg_counter++;
}

void show_phy()
{
	if (phy.size() == 0)
	{
		cout << "EMPTY" << endl;
	}
	else
	{
		for (int i = 0; i < phy.size(); i++)
		{
			cout << phy[i]->currentState->GetTicket() << " " << phy[i]->currentState->GetName() << endl;
		}
	}
}

void show_leg()
{
	if (leg.size() == 0)
	{
		cout << "EMPTY" << endl;
	}
	else
	{
		for (int i = 0; i < leg.size(); i++)
		{
			cout << leg[i]->currentState->GetTicket() << " " << leg[i]->currentState->GetName() << endl;
		}
	}
}

void cash_in_phy()
{
	int cash;

	if (phy.size() == 0)
	{
		cout << "EMPTY" << endl;
	}
	else
	{
		phy[0]->BeginTransactions();
		cout << "Введите сумму: ";
		enterNum(&cash);
		phy[0]->currentState->SetCash(phy[0]->currentState->GetCash() + cash);
		if ((double)cash <= phy[0]->currentState->MAX_CASH_IN_PHY)
		{
			phy[0]->Commit();
			phy.erase(phy.begin() + 0);
		}
		else {
			system("cls");
			cout << "Сумма превышает допустимую!";
			phy[0]->deleteTransactions();
		}
	}
}

void cash_in_leg()
{
	int cash;

	if (leg.size() == 0)
	{
		cout << "EMPTY" << endl;
	}
	else
	{
		leg[0]->BeginTransactions();
		cout << "Введите сумму: ";
		enterNum(&cash);
		leg[0]->currentState->SetCash(leg[0]->currentState->GetCash() + cash);
		if ((double)cash <= leg[0]->currentState->MAX_CASH_IN_LEGAL)
		{
			leg[0]->Commit();
			leg.erase(leg.begin() + 0);
		}
		else {
			system("cls");
			cout << "Сумма превышает допустимую!";
			leg[0]->deleteTransactions();
		}
	}
}

void cash_out_phy()
{
	int cash;

	if (phy.size() == 0)
	{
		cout << "EMPTY" << endl;
	}
	else
	{
		phy[0]->BeginTransactions();
		cout << "Введите сумму: ";
		enterNum(&cash);
		phy[0]->currentState->SetCash(phy[0]->currentState->GetCash() - cash);
		
		if (phy[0]->currentState->GetCash() - cash < 0)
		{
			system("cls");
			cout << "На карте недостаточно средств!";
			phy[0]->deleteTransactions();
		}
		else
		{
			if ((double)cash <= phy[0]->currentState->MAX_CASH_OUT_PHY)
			{
				phy[0]->Commit();
				phy.erase(phy.begin() + 0);
			}
			else {
				system("cls");
				cout << "Сумма превышает допустимую!";
				phy[0]->deleteTransactions();
			}
		}
	}
}

void cash_out_leg()
{
	int cash;

	if (leg.size() == 0)
	{
		cout << "EMPTY" << endl;
	}
	else
	{
		leg[0]->BeginTransactions();
		cout << "Введите сумму: ";
		enterNum(&cash);
		leg[0]->currentState->SetCash(leg[0]->currentState->GetCash() - cash);

		if (leg[0]->currentState->GetCash() - cash < 0)
		{
			system("cls");
			cout << "На карте недостаточно средств!";
			leg[0]->deleteTransactions();
		}
		else
		{
			if ((double)cash <= leg[0]->currentState->MAX_CASH_OUT_LEGAL)
			{
				leg[0]->Commit();
				leg.erase(leg.begin() + 0);
			}
			else {
				system("cls");
				cout << "Сумма превышает допустимую!";
				leg[0]->deleteTransactions();
			}
		}
	}
}

int main()
{
	Menu menu;

	menu.CreateMenu(3, "Получить талон", "Показать очередь", "Работа с клиентами");
	{
		menu.sub[0].CreateMenu(2, "Физ. лицо", "Юр. лицо");
		{
			menu.sub[0].function[0] = add_phy;

			menu.sub[0].function[1] = add_leg;

		}
		menu.sub[1].CreateMenu(2, "Физ. лицо", "Юр. лицо");
		{
			menu.sub[1].function[0] = show_phy;

			menu.sub[1].function[1] = show_leg;
		}
		menu.sub[2].CreateMenu(2, "Физ. лицо", "Юр. лицо");
		{
			menu.sub[2].sub[0].CreateMenu(2, "Снять", "Пополнить");
			{
				menu.sub[2].sub[0].function[1] = cash_in_phy;

				menu.sub[2].sub[0].function[0] = cash_out_phy;
			}

			menu.sub[2].sub[1].CreateMenu(2, "Снять", "Пополнить");
			{
				menu.sub[2].sub[1].function[1] = cash_in_leg;

				menu.sub[2].sub[1].function[0] = cash_out_leg;
			}
		}
	}

	menu.StartMenu();
}