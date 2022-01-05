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
	if (button == 72)  num--; // ��� 72 ������������ ������� �����
	if (button == 80)  num++; // ��� 80 ������������ ������� ����
	return num;
}

class Data {
protected:
	string surname;
	int* salaries;
public:
	Data(string surname, const int* salaries) {
		cout << "����������� Data" << endl;
		this->salaries = new int[3];
		this->surname = surname;
		for (int i = 0; i < 3; i++)
		{
			this->salaries[i] = salaries[i];
		}
	}
	~Data() {
		cout << "���������� Data" << endl;
		delete[] salaries;
	}
};

class Tax {
protected:
	int incomeTax;
public:
	Tax(int incomeTax) {
		cout << "����������� Tax" << endl;
		this->incomeTax = incomeTax;
	}
};

class PaymentForm : public Data, public Tax {
public:
	PaymentForm(string surname, int* salaries, int incomeTax) : Data(surname, salaries), Tax(incomeTax) {
		cout << "����������� PaymentForm" << endl;
	};

	void Print() {
		cout << "������� ����������: " << this->surname << endl << endl;
		for (int i = 0; i < 3; i++)
		{
			cout << "��������� ������ ��� " << i + 1 << "-� ��������: " << this->incomeTax * this->salaries[i] / 100 << endl;
		}
	}
};

void main_menu(int num)
{
	int salaries[3] = { 1000, 1200, 800 };
	PaymentForm form1("������", salaries, 20);
	int n = 0;

	int key = 0;
	int buff = 0;
	const int SIZE = 1;
	do
	{
		system("cls");

		if (buff == 27)
		{
			switch (key)
			{
				/*case 0:
					for (int i = 0; i < 255; ++i)
					{
						if (salaries[i] % 2 != 0 || salaries[i] == 0)
						{
							break;
						}
						else
						{
							n++;
						}
					}

					cout << "������� ��������: ";
					cin >> salaries[n];
					break;*/
			case 0:
				form1.Print();
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
		title = new char* [SIZE] {/*(char*)"������ ��������", */(char*)"�������"};
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