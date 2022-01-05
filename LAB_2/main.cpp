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

class Array
{
public:

	char* c_array_A = new char[length];
	float* f_array_A = new float[length];
	int* i_array_A = new int[length];
	char* c_array_B = new char[length];
	float* f_array_B = new float[length];
	int* i_array_B = new int[length];

	Array()
	{
		length = 1; format = 0;
		char* c_array_A = 0;
		float* f_array_A = 0;
		int* i_array_A = 0;
		char* c_array_B = 0;
		float* f_array_B = 0;
		int* i_array_B = 0;
	}

	void i_array(unsigned int FORMAT, unsigned int LENGTH, int* ARRAY_A, int* ARRAY_B)
	{
		format = FORMAT;
		length = LENGTH;
		for (unsigned int i = 0; i < length; i++)
		{
			i_array_A[i] = ARRAY_A[i];
			i_array_B[i] = ARRAY_B[i];
		}
	}

	void f_array(unsigned int FORMAT, unsigned int LENGTH, float ARRAY_A[], float ARRAY_B[])
	{
		format = FORMAT;
		length = LENGTH;
		for (unsigned int i = 0; i < length; i++)
		{
			f_array_A[i] = ARRAY_A[i];
			f_array_B[i] = ARRAY_B[i];
		}
	}

	void c_array(unsigned int FORMAT, unsigned int LENGTH, char ARRAY_A[], char ARRAY_B[])
	{
		format = FORMAT;
		length = LENGTH;
		for (unsigned int i = 0; i < length; i++)
		{
			c_array_A[i] = ARRAY_A[i];
			c_array_B[i] = ARRAY_B[i];
		}
	}

	void sw_format(unsigned int FORMAT) { format = FORMAT; }

	void PRINT_IN_LINE()
	{
		if (format == 1)
		{
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "A[" << i << "]= " << i_array_A[i] << " ";
			}
			cout << endl;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "B[" << i << "]= " << i_array_B[i] << " ";
			}
		}
		if (format == 2)
		{
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "A[" << i << "]= " << f_array_A[i] << " ";
			}
			cout << endl;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "B[" << i << "]= " << f_array_B[i] << " ";
			}
		}
		if (format == 3)
		{
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "A[" << i << "]= " << c_array_A[i] << " ";
			}
			cout << endl;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "B[" << i << "]= " << c_array_B[i] << " ";
			}
		}
	}
	void PRINT_IN_COLUMN()
	{
		if (format == 1)
		{
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "A[" << i << "]= " << i_array_A[i] << " ";
				cout << "B[" << i << "]= " << i_array_B[i] << "\n";
			}
		}
		if (format == 2)
		{
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "A[" << i << "]= " << f_array_A[i] << " ";
				cout << "B[" << i << "]= " << f_array_B[i] << "\n";
			}
		}
		if (format == 3)
		{
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "A[" << i << "]= " << c_array_A[i] << " ";
				cout << "B[" << i << "]= " << c_array_B[i] << "\n";
			}
		}
	}
	void ARRAY_CROSSING()
	{
		if (format == 1)
		{
			for (unsigned int j = 0; j < length; j++)
			{
				for (unsigned int i = 0; i < length; i++)
				{
					if (i_array_A[j] == i_array_B[i])
					{
						cout << "A[" << j << "]= " << i_array_A[j] << " ";
						cout << "B[" << i << "]= " << i_array_B[i] << "\n";
						break;
					}
				}
			}
		}
		if (format == 2)
		{
			for (unsigned int j = 0; j < length; j++)
			{
				for (unsigned int i = 0; i < length; i++)
				{
					if (f_array_A[j] == f_array_B[i])
					{
						cout << "A[" << j << "]= " << f_array_A[j] << " ";
						cout << "B[" << i << "]= " << f_array_B[i] << "\n";
						break;
					}
				}
			}
		}
		if (format == 3)
		{
			for (unsigned int j = 0; j < length; j++)
			{
				for (unsigned int i = 0; i < length; i++)
				{
					if (c_array_A[j] == c_array_B[i])
					{
						cout << "A[" << j << "]= " << c_array_A[j] << " ";
						cout << "B[" << i << "]= " << c_array_B[i] << "\n";
						break;
					}
				}
			}
		}
	}
	void ARRAY_CONECT()
	{
		if (format == 1)
		{
			int j = 0;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "C[" << i << "]= " << i_array_A[i] << "\n";
				j = i;
			}
			j = j + 1;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "C[" << i + j << "]= " << i_array_B[i] << "\n";
			}
		}
		if (format == 2)
		{
			int j = 0;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "C[" << i << "]= " << f_array_A[i] << "\n";
				j = i;
			}
			j = j + 1;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "C[" << i + j << "]= " << f_array_B[i] << "\n";
			}
		}
		if (format == 3)
		{
			int j = 0;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "C[" << i << "]= " << c_array_A[i] << "\n";
				j = i;
			}
			j = j + 1;
			for (unsigned int i = 0; i < length; i++)
			{
				cout << "C[" << i + j << "]= " << c_array_B[i] << "\n";
			}
		}
	}
private:
	unsigned int length, format;
};

void SET_ARRAY(int num, Array* p)
{
	int length;
	bool prov;
	unsigned int format;

	cout << "Enter a length: ";
	cin >> length;

	do
	{
		cout << "Chose format 1)int 2)float 3)char: ";
		cin >> format;

		if (format == 1 && format == 2 && format == 3)
		{
			prov = true;
		}
		else
		{
			prov = false;
		}
	} while (prov == true);

	char* c_array_A = new char[length];
	float* f_array_A = new float[length];
	int* i_array_A = new int[length];
	char* c_array_B = new char[length];
	float* f_array_B = new float[length];
	int* i_array_B = new int[length];

	switch (format)
	{
	case 1:

		for (int i = 0; i < length; i++) {
			cout << "A " << i << ": ";
			cin >> i_array_A[i];
		}
		for (int i = 0; i < length; i++) {
			cout << "B " << i << ": ";
			cin >> i_array_B[i];
		}
		p->i_array(format, length, i_array_A, i_array_B);
		break;
	case 2:

		for (int i = 0; i < length; i++) {
			cout << "A " << i << ": ";
			cin >> f_array_A[i];
		}
		for (int i = 0; i < length; i++) {
			cout << "B " << i << ": ";
			cin >> f_array_B[i];
		}
		p->f_array(format, length, f_array_A, f_array_B);
		break;
	case 3:

		for (int i = 0; i < length; i++) {
			cout << "A " << i << ": ";
			cin >> c_array_A[i];
		}
		for (int i = 0; i < length; i++) {
			cout << "B " << i << ": ";
			cin >> c_array_B[i];
		}
		p->c_array(format, length, c_array_A, c_array_B);
		break;
	}
}



void main_menu(int num)
{
	Array array;

	int key = 0;
	int buff = 0;
	const int SIZE = 5;
	do
	{
		system("cls");

		if (buff == 27)
		{
			switch (key)
			{
			case 0:
				SET_ARRAY(0, &array);
				break;
			case 1:
				array.PRINT_IN_LINE();
				_getch();
				break;
			case 2:
				array.PRINT_IN_COLUMN();
				_getch();
				break;
			case 3:
				array.ARRAY_CROSSING();
				_getch();
				break;
			case 4:
				array.ARRAY_CONECT();
				_getch();
				break;
			}
			system("cls");
		}
		if (buff < 0)
			key = SIZE - 1;
		else
			key = buff % SIZE;
		char** title;
		title = new char* [SIZE] {(char*)"Set array A and B", (char*)"Print in line", (char*)"Print in column", (char*)"Array crossing", (char*)"Array conect"};
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
	main_menu(0);
}