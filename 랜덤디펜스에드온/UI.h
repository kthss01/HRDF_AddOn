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
		cout << "히어로즈 랜덤 디펜스 에드온" << endl;
		db.print_base_hero();
		cout << "0. 베이스 영웅 입력" << endl;
		cout << "1. 이름 검색" << endl;
		cout << "2. 등급별 검색" << endl;
		cout << "3. 베이스영웅에 따른 검색" << endl;
		cout << "4. 베이스영웅별 정렬" << endl;
		cout << "5. 종료" << endl;
		cout << "6. Print" << endl;
		cout << "7. Write" << endl;
		cout << "8. Add" << endl;
		cout << "원하시는 번호를 입력하세요 : ";
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
		db.sortBase();
		break;
	case 5:
		done = true;
		cout << "******************************************" << endl;
		break;
	case 6:
		db.print();
		break;
// db write, add 는 삭제 예정 검색프로그램이 주이므로 굳이 write add 할 필요 x
	case 7:
		//db.write();
		break;
	case 8:
		//db.add();
		break;
	default:
		cout << "잘못 입력 하셨습니다. 다시 입력해주세요" << endl;
		break;
	}
}