#include "Menu.h"

bool isNumber(const string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

class ProjectManagement {
public:

	string name;
	int priority;

	ProjectManagement(string _name, double _priority) : name(_name), priority(_priority) {};

	friend bool operator<(ProjectManagement obj1, ProjectManagement obj2) {
		return obj1.priority < obj2.priority;
	}
	friend bool operator>(ProjectManagement obj1, ProjectManagement obj2) {
		return obj1.priority > obj2.priority;
	}
	friend ostream& operator<<(ostream& str, ProjectManagement obj) {
		return str << "Название: " << obj.name << "\n   Приоритет: " << obj.priority << endl;
	}
};

priority_queue < ProjectManagement, vector<ProjectManagement>, less<vector<ProjectManagement>::value_type>> que;
queue<ProjectManagement> stk;

void Add() {
	string name;
	string priority;
	bool prov = false;
	cout << "Введите название задачи: ";
	getline(cin, name);
	cout << "Введите приоритет задачи от 1 до 10: ";
	getline(cin, priority);
	if (isNumber(priority) == true)
	{
		if (1>= atoi(priority.c_str()) || atoi(priority.c_str()) <= 10)
		{
			que.push(ProjectManagement(name, atoi(priority.c_str())));
			system("cls");
			cout << "Добавлено!";
		}
		else
		{
			system("cls");
			cout << "Значение за пределами допустимых!";
		}
	}
	else
	{
		system("cls");
		cout << "Значение не является числом!";
	}

}

void Show() {
	int i = 1;
	if (que.empty()) {
		cout << "Очередь пуста!";
	}
	else {
		while (!que.empty()) {
			cout << i << ". " << que.top();
			stk.push(que.top());
			que.pop();
			i++;
		}
		while (!stk.empty()) {
			que.push(stk.front());
			stk.pop();
		}
	}
}

void EndPrior() {
	cout << "Завершена задача " << "\"" + que.top().name + "\"";
	que.pop();
}

void Redact() {
	Show();

	cout << "\n\nВыберите задачу: ";
	int choise;
	cin >> choise;
	if (choise < 0 || choise > que.size()) {
		cout << "Такой позиции нет!";
	}
	else {
		string _name;
		double _priority;
		system("cls");
		cout << "Введите название задачи: ";
		cin >> _name;
		cout << "Введите приоритет задачи: ";
		cin >> _priority;
		int i = 1;
		while (!que.empty()) {
			if (choise == i) {
				que.pop();
				que.push(ProjectManagement(_name, _priority));
			}
			stk.push(que.top());
			que.pop();
			i++;
		}
		while (!stk.empty()) {
			que.push(stk.front());
			stk.pop();
		}
		system("cls");
		cout << "Изменено!";
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu;

	menu.CreateMenu(4, "Добавить", "Просмотреть", "Редактировать", "Завершить приор.");
	{
		menu.function[0] = Add;
		menu.function[1] = Show;
		menu.function[2] = Redact;
		menu.function[3] = EndPrior;
	}

	menu.Start();
}