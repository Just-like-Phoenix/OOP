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

class Vector;

class Matrix
{
public:



	Matrix()
	{
		length_i = 1;
		length_j = 1;
		int** matrix = 0;
	}

	int GetI() { return length_i; }
	int GetJ() { return length_j; }

	void i_matrix(unsigned int LENGTH_I, unsigned int LENGTH_J, int** MATRIX)
	{
		length_i = LENGTH_I;
		length_j = LENGTH_J;

		matrix = new int* [length_i];
		for (unsigned int i = 0; i < length_j; i++)
			matrix[i] = new int[length_j];

		for (unsigned int i = 0; i < length_j; i++)
		{
			for (unsigned int j = 0; j < length_i; j++)
			{
				matrix[i][j] = MATRIX[i][j];
			}
		}
	}

	friend void MATRIX_INC_VECTOR(Matrix& matrix, Vector& vector);

private:
	int** matrix;
	unsigned int length_i;
	unsigned int length_j;
};

class Vector
{
public:

	int* vector = new int[length];

	Vector()
	{
		length = 1;
		int* Vector = 0;

	}

	void i_vector(unsigned int LENGTH, int* VECTOR)
	{
		length = LENGTH;
		for (unsigned int i = 0; i < length; i++)
		{
			vector[i] = VECTOR[i];
		}
	}

	friend class Matrix;
	friend void MATRIX_INC_VECTOR(Matrix& matrix, Vector& vector);

private:
	unsigned int length;
};

void MATRIX_INC_VECTOR(Matrix& matrix, Vector& vector)
{
	int i_for_inc = matrix.length_i;
	int j_for_inc = matrix.length_j;
	for (int i = 0; i < j_for_inc; i++)
	{
		int temp = 0;
		for (int j = 0; j < i_for_inc; j++)
		{
			temp += matrix.matrix[i][j] * vector.vector[i];
		}
		cout << "C[" << i << "] = " << temp << endl;
	}
}

void SET_MATRIX_AND_VECTOR(int num, Matrix* m, Vector* v)
{
	int length_i, length_j;

	int** matrix;

	cout << "Enter a length i: "; // строки
	cin >> length_i;
	cout << "Enter a length j: "; //столбцы
	cin >> length_j;

	matrix = new int* [length_i];         // строки
	for (int i = 0; i < length_j; i++)
		matrix[i] = new int[length_j];   //столбцы

	cout << "Enter Matrix: ";

	for (int i = 0; i < length_j; i++)   // строки
	{
		for (int j = 0; j < length_i; j++)   //столбцы
		{
			cout << "A[" << i << "][" << j << "] = ";
			cin >> matrix[i][j];
		}
	}
	m->i_matrix(length_i, length_j, matrix);

	cout << "Enter Vector: ";

	int* vector = new int[length_j];

	for (int i = 0; i < length_j; i++) {
		cout << "B[" << i << "] = ";
		cin >> vector[i];
	}
	v->i_vector(length_j, vector);
}

void main_menu(int num)
{
	Matrix matrix;
	Vector vector;

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
				SET_MATRIX_AND_VECTOR(0, &matrix, &vector);
				break;
			case 1:
				MATRIX_INC_VECTOR(matrix, vector);
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
		title = new char* [SIZE] {(char*)"Set array A and B", (char*)"A inc B"};
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