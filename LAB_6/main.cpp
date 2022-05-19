#include "Menu.h"

void Replace(char* buf, char replace, char to) {
	for (int i = 0; i < 60; i++) {
		if (buf[i] == replace) buf[i] = to;
	}
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
	string buf;
	int priority;
	cout << "Введите название задачи: ";
	getline(cin, name);
	cout << "Введите приоритет задачи: ";
	getline(cin, buf);
	priority = atoi(buf.c_str());
	que.push(ProjectManagement(name, priority));
	system("cls");
	cout << "Добавлено!";
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