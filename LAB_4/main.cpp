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

class Circle;
class Square;
class Triangle;

class Shape
{
public:
	Shape(const std::string& type) : _type(type) {}

	friend void  intersectC_S_or_S_C(Circle& circle, Square& square);
	friend void  intersectC_T_or_T_C(Circle& circle, Triangle& triangle);
	friend void  intersectS_T_or_T_S(Square& square, Triangle& triangle);

protected:
	std::string _type;

private:

};

class Circle :public Shape
{
public:
	int R;

	Circle() : Shape("circle")
	{
		R = 0;
	}

	void i_circle(int r)
	{
		R = r;
	}

	friend class Shape;
};

class Square :public Shape
{
public:
	int A;

	Square() : Shape("square")
	{
		A = 0;
	}

	void i_square(int a)
	{
		A = a;
	}

	friend class Shape;
};

class Triangle :public Shape
{
public:
	int A;

	Triangle() : Shape("triangle")
	{
		A = 0;
	}

	void i_triangle(int a)
	{
		A = a;
	}

	friend class Shape;
};

void  intersectC_S_or_S_C(Circle& circle, Square& square)
{
	int R = circle.R;
	int A = square.A;
	double pi = 3.14159;

	double MAX_R = A * 2 * sqrt(2);
	double MIN_R = A / 2;

	double REAL_SQUARE = pi * R * R;

	double MAX_SQUARE = pi * MAX_R * MAX_R;
	double MIN_SQUARE = pi * MIN_R * MIN_R;

	if (REAL_SQUARE <= MAX_SQUARE && REAL_SQUARE >= MIN_SQUARE)
	{
		cout << "Square intersect Circle" << endl;
	}
	else
	{
		cout << "Square not intersect Circle" << endl;
	}
}

void  intersectC_T_or_T_C(Circle& circle, Triangle& triangle)
{
	int R = circle.R;
	int A = triangle.A;
	double pi = 3.14159;

	double MAX_R = (A * sqrt(3)) / 2;
	double MIN_R = (A * sqrt(3)) / 6;

	double REAL_SQUARE = pi * R * R;

	double MAX_SQUARE = pi * MAX_R * MAX_R;
	double MIN_SQUARE = pi * MIN_R * MIN_R;

	if (REAL_SQUARE <= MAX_SQUARE && REAL_SQUARE >= MIN_SQUARE)
	{
		cout << "Square intersect Triangle" << endl;
	}
	else
	{
		cout << "Square not intersect Triangle" << endl;
	}
}

void  intersectS_T_or_T_S(Square& square, Triangle& triangle)  //хз
{

}

void SET(int num, Circle* c, Triangle* t, Square* s)
{
	int circle_R, triangle_A, square_A;

	cout << "Enter R of circle: ";
	cin >> circle_R;
	cout << "Enter A of triangle: ";
	cin >> triangle_A;
	cout << "Enter A of square: ";
	cin >> square_A;

	c->i_circle(circle_R);
	t->i_triangle(triangle_A);
	s->i_square(square_A);
}

void main_menu(int num)
{
	Circle circle;
	Triangle triangle;
	Square square;

	int key = 0;
	int buff = 0;
	const int SIZE = 4;
	do
	{
		system("cls");

		if (buff == 27)
		{
			switch (key)
			{
			case 0:
				SET(0, &circle, &triangle, &square);
				break;
			case 1:
				intersectC_S_or_S_C(circle, square);
				_getch();
				break;
			case 2:
				intersectC_T_or_T_C(circle, triangle);
				_getch();
				break;
			case 3:
				intersectS_T_or_T_S(square, triangle);
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
		title = new char* [SIZE] {(char*)"Set shape's settings", (char*)"Circle intersect Square?", (char*)"Circle intersect Triangle?", (char*)"Square intersect Triangle?"};
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