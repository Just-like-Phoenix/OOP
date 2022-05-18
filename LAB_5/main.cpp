#include "menu.h"

using namespace std;

class Services {
	string group;
	string name;
	int cost;

public:
	Services() {};
	Services(string _group) : group(_group) {};

	string GetName() { return name; }
	int GetCost() { return cost; }

	friend ostream& operator<<(ostream& stream, Services& obj) {
		cout << obj.name << " " << obj.cost << "\n";
		return stream;
	}
	friend istream& operator>>(istream& stream, Services& obj) {
		cout << "Введите название услуги: ";
		cin >> obj.name;
		cout << "Введите стоимость услуги: ";
		cin >> obj.cost;
		return stream;
	}
	friend ofstream& operator<<(ofstream& stream, Services& obj) {
		stream << obj.name << " " << obj.cost << "\n";
		return stream;
	}
	friend ifstream& operator>>(ifstream& stream, Services& obj) {
		stream >> obj.name >> obj.cost;
		return stream;
	}
};

map<string, vector<Services>> _Map;
vector<Services> med, kosm;

void ShowMed() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	if (Mptr->second.empty()) {
		cout << "Нет услуг!";
	}
	else {
		for (int i = 1; Vptr != Mptr->second.end(); Vptr++, i++) {
			cout << i << ") " << *Vptr << "\n\n";
		}
	}
}
void ShowKosm() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	if (Mptr->second.empty()) {
		cout << "Нет услуг!";
	}
	else {
		for (int i = 1; Vptr != Mptr->second.end(); Vptr++, i++) {
			cout << i << ") " << *Vptr << "\n\n";
		}
	}
}

void AddMed() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");
	Services tmp("Мед. услуги");
	cin >> tmp;

	Mptr->second.push_back(tmp);
}
void AddKosm() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");
	Services tmp("Косметические");
	cin >> tmp;

	Mptr->second.push_back(tmp);
}

void RedMed() {
	ShowMed();

	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");

	if (Mptr->second.size() != 0) {
		cout << "Введите номер: ";

		int choise;
		cin >> choise;
		if (choise < 0 || choise > Mptr->second.size() && Mptr->second.size() != 0) {
			cout << "Такого номера нет!";
		}
		else {
			system("cls");
			cin >> Mptr->second[choise - 1];
		}
	}
}
void RedKosm() {
	ShowKosm();

	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");

	if (Mptr->second.size() != 0) {
		cout << "Введите номер: ";

		int choise;
		cin >> choise;
		if (choise < 0 || choise > Mptr->second.size() && Mptr->second.size() != 0) {
			cout << "Такого номера нет!";
		}
		else {
			system("cls");
			cin >> Mptr->second[choise - 1];
		}
	}
}

void DelMed() {
	ShowMed();

	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	if (Mptr->second.size() != 0) {
		cout << "Введите номер: ";

		int choise;
		cin >> choise;
		if (choise < 0 || choise > Mptr->second.size() && Mptr->second.size() != 0) {
			cout << "Такого номера нет!";
		}
		else {
			system("cls");
			Mptr->second.erase(Vptr + choise - 1);
			cout << "Удалено!";
		}
	}
}
void DelKosm() {
	ShowKosm();

	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	if (Mptr->second.size() != 0) {
		cout << "Введите номер: ";

		int choise;
		cin >> choise;
		if (choise < 0 || choise > Mptr->second.size() && Mptr->second.size() != 0) {
			cout << "Такого номера нет!";
		}
		else {
			system("cls");
			Mptr->second.erase(Vptr + choise - 1);
			cout << "Удалено!";
		}
	}
}

void SortByNameUPMed() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetName() > Mptr->second[i + k].GetName()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowMed();
	}
}
void SortbyNameDownMed() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetName() < Mptr->second[i + k].GetName()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowMed();
	}
}

void SortByNameUPKosm() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetName() > Mptr->second[i + k].GetName()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowKosm();
	}
}
void SortByNameDownKosm() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetName() < Mptr->second[i + k].GetName()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowKosm();
	}
}

void SortByCostUPMed() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetCost() > Mptr->second[i + k].GetCost()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowMed();
	}
}
void SortbyCostDownMed() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetCost() < Mptr->second[i + k].GetCost()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowMed();
	}
}

void SortByCostUPKosm() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetCost() > Mptr->second[i + k].GetCost()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowKosm();
	}
}
void SortByCostDownKosm() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		for (int k = Mptr->second.size() / 2; k > 0; k--) {
			for (int i = 0; i < Mptr->second.size() - k; i++) {
				if (Mptr->second[i].GetCost() < Mptr->second[i + k].GetCost()) swap(Mptr->second[i], Mptr->second[i + k]);
			}
		}
		ShowKosm();
	}
}

void SearchMed() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		bool exist = false;
		cout << "Введите строку для поиска: ";
		string str;
		cin >> str;
		system("cls");
		for (int i = 0; Vptr != Mptr->second.end(); Vptr++, i++) {
			if (strstr(Mptr->second[i].GetName().c_str(), str.c_str())) {
				exist = true;
				cout << Mptr->second[i] << "\n\n";
			}
		}
		if (!exist) cout << "Не найдено записей";
	}
}
void SearchKosm() {
	map<string, vector<Services>>::iterator Mptr = _Map.find("Косметические");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	if (Mptr->second.size() == 0) {
		cout << "Услуг нет!";
	}
	else {
		bool exist = false;
		cout << "Введите строку для поиска: ";
		string str;
		cin >> str;
		system("cls");
		for (int i = 0; Vptr != Mptr->second.end(); Vptr++, i++) {
			if (strstr(Mptr->second[i].GetName().c_str(), str.c_str())) {
				exist = true;
				cout << Mptr->second[i] << "\n\n";
			}
		}
		if (!exist) cout << "Не найдено записей";
	}
}

void Save() {
	ofstream med, kosm;

	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	med.open("med.txt", ios::out);
	for (; Vptr != Mptr->second.end(); Vptr++) {
		med << *Vptr;
	}
	med.close();

	Mptr = _Map.find("Косметические");
	Vptr = Mptr->second.begin();

	kosm.open("kosm.txt", ios::out);
	for (; Vptr != Mptr->second.end(); Vptr++) {
		kosm << *Vptr;
	}
	kosm.close();
}
void Init() {
	ifstream med, kosm;

	map<string, vector<Services>>::iterator Mptr = _Map.find("Мед. услуги");
	vector<Services>::iterator Vptr = Mptr->second.begin();

	med.open("med.txt", ios::out);
	while (med) {
		if (!med.eof()) {
			Services tmp("Мед. услуги");
			med >> tmp;
			Mptr->second.push_back(tmp);
		}
	}
	Vptr = Mptr->second.end();
	Mptr->second.erase(Vptr - 1);
	med.close();

	Mptr = _Map.find("Косметические");
	Vptr = Mptr->second.begin();

	kosm.open("kosm.txt", ios::out);
	while (kosm) {
		if (!kosm.eof()) {
			Services tmp("Косметические");
			kosm >> tmp;
			Mptr->second.push_back(tmp);
		}
	}
	Vptr = Mptr->second.end();
	Mptr->second.erase(Vptr - 1);
	kosm.close();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu;

	_Map.insert(pair<string, vector<Services>>("Мед. услуги", med));
	_Map.insert(pair<string, vector<Services>>("Косметические", kosm));

	Init();

	menu.CreateMenu(7, "Просмотреть", "Добавить", "Редактировать", "Удалить", "Поиск", "Сортировать", "Сохранить");
	{
		menu.sub[0].CreateMenu(2, "Мед. услуги", "Косметические");
		{
			menu.sub[0].function[0] = ShowMed;
			menu.sub[0].function[1] = ShowKosm;
		}
		menu.sub[1].CreateMenu(2, "Мед. услуги", "Косметические");
		{
			menu.sub[1].function[0] = AddMed;
			menu.sub[1].function[1] = AddKosm;
		}
		menu.sub[2].CreateMenu(2, "Мед. услуги", "Косметические");
		{
			menu.sub[2].function[0] = RedMed;
			menu.sub[2].function[1] = RedKosm;
		}
		menu.sub[3].CreateMenu(2, "Мед. услуги", "Косметические");
		{
			menu.sub[3].function[0] = DelMed;
			menu.sub[3].function[1] = DelKosm;
		}
		menu.sub[4].CreateMenu(2, "Мед. услуги", "Косметические");
		{
			menu.sub[4].function[0] = SearchMed;
			menu.sub[4].function[1] = SearchKosm;
		}
		menu.sub[5].CreateMenu(2, "Мед. услуги", "Косметические");
		{
			menu.sub[5].sub[0].CreateMenu(2, "По названию", "По стоимости");
			{
				menu.sub[5].sub[0].sub[0].CreateMenu(2, "По возрастанию", "По убыванию");
				{
					menu.sub[5].sub[0].sub[0].function[0] = SortByNameUPMed;
					menu.sub[5].sub[0].sub[0].function[1] = SortbyNameDownMed;
				}
				menu.sub[5].sub[0].sub[1].CreateMenu(2, "По возрастанию", "По убыванию");
				{
					menu.sub[5].sub[0].sub[1].function[0] = SortByCostUPMed;
					menu.sub[5].sub[0].sub[1].function[1] = SortbyCostDownMed;
				}
			}
			menu.sub[5].sub[1].CreateMenu(2, "По названию", "По стоимости");
			{
				menu.sub[5].sub[1].sub[0].CreateMenu(2, "По возрастанию", "По убыванию");
				{
					menu.sub[5].sub[1].sub[0].function[0] = SortByNameUPKosm;
					menu.sub[5].sub[1].sub[0].function[1] = SortByNameDownKosm;
				}
				menu.sub[5].sub[1].sub[1].CreateMenu(2, "По возрастанию", "По убыванию");
				{
					menu.sub[5].sub[1].sub[1].function[0] = SortByCostUPKosm;
					menu.sub[5].sub[1].sub[1].function[1] = SortByCostDownKosm;
				}
			}
		}
		menu.function[6] = Save;
	}

	menu.Start();
}