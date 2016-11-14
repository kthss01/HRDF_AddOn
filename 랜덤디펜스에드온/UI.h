#pragma once

#include "DB.h"
#include <iostream>
using namespace std;

class UI {
private:
	bool done = false;
	int select;
	DB db;
public:
	UI();
	void init();
};

UI::UI() {
	db.read();
	db.makeGraph();
	db.count_base();
	do {
		cout << "******************************************" << endl;
		cout << "������� ���� ���潺 �����" << endl;
		db.print_base_hero();
		cout << "0. ���̽� ���� �Է�" << endl;
		cout << "1. �̸� �˻�" << endl;
		cout << "2. ��޺� �˻�" << endl;
		cout << "3. ���̽������� ���� �˻�" << endl;
		cout << "4. ���̽������� ����" << endl;
		cout << "5. ����" << endl;
		cout << "6. Print" << endl;
		cout << "7. Write" << endl;
		cout << "8. Add" << endl;
		cout << "���Ͻô� ��ȣ�� �Է��ϼ��� : ";
		cin >> select;
		init();
	} while (!done);
}

void UI::init() {
	switch (select) {
	case 0:
		db.input_base_hero();
		break;
	case 1:
		db.search();
		break;
	case 2:
		db.searchRank();
		break;
	case 3:
		db.searchOfBase();
		break;
	case 4:
		//db.sortBase();
		break;
	case 5:
		done = true;
		cout << "******************************************" << endl;
		break;
	case 6:
		db.print();
		break;
// db write, add �� ���� ���� �˻����α׷��� ���̹Ƿ� ���� write add �� �ʿ� x
	case 7:
		//db.write();
		break;
	case 8:
		//db.add();
		break;
	default:
		cout << "�߸� �Է� �ϼ̽��ϴ�. �ٽ� �Է����ּ���" << endl;
		break;
	}
}