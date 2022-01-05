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

using namespace std;

class Transport
{
protected:
	string model;
	int seatsNum;
	string driverFio;
public:
	Transport();
	Transport(string model, int seatsNum, string driverFio);
	Transport(const Transport& obj);

	void virtual PrintInfo() = 0;
	void PrintInFile();
};

void Transport::PrintInFile() {
	fstream fs;
	string path = "file.txt";
	fs.open(path, fstream::in | fstream::out | fstream::app);
	if (fs.is_open()) {
		fs << model << " " << seatsNum << " " << " " << driverFio << endl;
		fs.close();
		cout << "Информация успешно записана в файл" << endl;
	}
	else {
		cout << "Не удалось записать информацию в файл" << endl;
	}
}

Transport::Transport()
{
	model = "-";
	seatsNum = 0;
	driverFio = "-";
}

Transport::Transport(string model, int seatsNum, string driverFio) {
	this->model = model;
	this->seatsNum = seatsNum;
	this->driverFio = driverFio;
}

Transport::Transport(const Transport& obj) {
	cout << "Сработал конструктор копирования" << endl;
	model = obj.model;
	seatsNum = obj.seatsNum;
	driverFio = obj.driverFio;
}

class Bus : public Transport {
public:
	Bus() : Transport() {}
	Bus(string model, int seatsNum, string driverFio) : Transport(model, seatsNum, driverFio) {}
	Bus(const Bus& obj) : Transport(obj) {}

	void i_bus(string imodel, int iseatsNum, string idriverFio)
	{
		model = imodel;
		seatsNum = iseatsNum;
		driverFio = idriverFio;
	}

	void PrintInfo() override {
		cout << "Автобус" << endl;
		cout << model << " " << seatsNum << " " << driverFio << endl;
	}
};

class Microbus : public Transport {
public:
	Microbus() : Transport() {}
	Microbus(string model, int seatsNum, string driverFio) : Transport(model, seatsNum, driverFio) {}
	Microbus(const Bus& obj) : Transport(obj) {}

	void i_microbus(string imodel, int iseatsNum, string idriverFio)
	{
		model = imodel;
		seatsNum = iseatsNum;
		driverFio = idriverFio;
	}

	void PrintInfo() override {
		cout << "Микроавтобус" << endl;
		cout << model << " " << seatsNum << " " << driverFio << endl;
	}
};

class Auto : public Transport {
public:
	Auto() : Transport() {}
	Auto(string model, int seatsNum, string driverFio) : Transport(model, seatsNum, driverFio) {}
	Auto(const Bus& obj) : Transport(obj) {}

	void i_auto(string imodel, int iseatsNum, string idriverFio)
	{
		model = imodel;
		seatsNum = iseatsNum;
		driverFio = idriverFio;
	}

	void PrintInfo() override {
		cout << "Автомобиль" << endl;
		cout << model << " " << seatsNum << " " << driverFio << endl;
	}
};

void Print(Transport* transport) {
	transport->PrintInfo();
	cout << endl;
}

void main_menu(int num)
{
	Transport* ptr;
	Bus bus;
	Microbus microbus;
	Auto automo;

	string buf1;
	int buf2;
	string buf3;

	int key = 0;
	int buff = 0;
	const int SIZE = 6;
	do
	{
		system("cls");

		if (buff == 27)
		{
			switch (key)
			{
			case 0:
				cout << "Модель: ";
				cin >> buf1;
				cout << "Количество мест: ";
				cin >> buf2;
				cout << "ФИО водителя: ";
				cin >> buf3;

				bus.i_bus(buf1, buf2, buf3);
				break;
			case 1:
				cout << "Модель: ";
				cin >> buf1;
				cout << "Количество мест: ";
				cin >> buf2;
				cout << "ФИО водителя: ";
				cin >> buf3;

				microbus.i_microbus(buf1, buf2, buf3);
				break;
			case 2:
				cout << "Модель: ";
				cin >> buf1;
				cout << "Количество мест: ";
				cin >> buf2;
				cout << "ФИО водителя: ";
				cin >> buf3;

				automo.i_auto(buf1, buf2, buf3);
				break;
			case 3:
				ptr = &bus;
				Print(ptr);
				system("pause");
				break;
			case 4:
				ptr = &microbus;
				Print(ptr);
				system("pause");
				break;
			case 5:
				ptr = &automo;
				Print(ptr);
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
		title = new char* [SIZE] {(char*)"Автобус", (char*)"Микроавтобус", (char*)"Автомобиль", (char*)"Вывод автобус", (char*)"Вывод микроавтобус", (char*)"Вывод автомобиль"};
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