// 히어로즈 랜덤 디펜스 조합 도우미 
// 국민대학교 컴퓨터공학과 20113273 김태훈

// 개발 이유 
// 조합 도감은 게임 내에 표현 되어는 있지만 바로 하위 케릭터의 조합으로만 표현되어있음
// #1 상위 케릭터를 조합하기 기본 케릭터가 몇개가 필요한지 빠르게 알기 위해서
// #2 기본 케릭터 구성에 따라 어떤 케릭터를 조합해야 할 지 판단 하기 위해서
// * 매 웨이브가 시작될 때마다 랜덤한 기본 케릭터를 주므로 상황에 맞는 조합방향을 정해야함

// 설계 방안 
// write : 먼저 db에 히어로즈 랜덤 디펜스에 케릭터에 따른 조합 목록을 쓴다.
// read : 쓰여진 db에서 조합 목록을 읽어온다.
// *search : 케릭터 이름에 따른 조합 목록을 기본케릭터 수에 따라 보여준다.

// 추후 설계 방안 : 
// search2 : 기본 케릭터 수가 어떤게 많은 지에 따라 어떤 케릭터를 조합해야할지 방향을 알려줌

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define BASE_NUM 8
vector<struct hero> heroes;

// 영웅 struct
typedef struct hero{
	string name;
	int rank;
	string job;
	int base_num;
	pair<string, int> base[BASE_NUM];
}Hero;

void print() {
	cout << "******************************************" << endl;
	for (int i = 0; i < heroes.size(); i++)
	{
		Hero hero = heroes[i];
		cout << hero.rank << "성 " << hero.name << " ";
		for (int j = 0; j < hero.base_num; j++)
			cout << hero.base[j].first << 
				"(" << hero.base[j].second << ") ";
		cout << endl;
	}
}
void print(Hero hero) {
	cout << "******************************************" << endl;
	cout << hero.rank << "성 " << hero.name << " ";
	for (int j = 0; j < hero.base_num; j++)
		cout << hero.base[j].first <<
		"(" << hero.base[j].second << ") ";
	cout << endl;
}

bool cmp(Hero h1, Hero h2) {
	return h1.rank > h2.rank;
}

void read() {
	// 읽어와야할 사항
	// 등록된 전체 영웅 수, 각 영웅 조합에 필요한 영웅들 수, 해당영웅 직업, 등급 
	// 추후 특징도 넣어주면 좋을듯

	ifstream in;
	// 일단은 현재위치에 db.txt 읽어오기
	in.open("db.txt"); 
	if (!in.is_open()) {
		cout << "db를 읽어 올 수 가 없습니다." << endl;
		exit(1);
	}

	int num;
	in >> num;
	while (num--) {
		Hero hero;
		in >> hero.rank;
		in >> hero.job;
		in >> hero.name;
		in >> hero.base_num;
		for (int i = 0; i < hero.base_num; i++) {
			in >> hero.base[i].first;
			in >> hero.base[i].second;
		}
		heroes.push_back(hero);
	}
	sort(heroes.begin(), heroes.end(), cmp);
	print();
}

void write() {
	ofstream out;
	out.open("db.txt");
	out << heroes.size() << endl;
	for (int i = 0; i < heroes.size(); i++) {
		Hero hero = heroes[i];
		out << hero.rank << " " << hero.job << " ";
		out << hero.name << " " << hero.base_num << " ";
		for (int j = 0; j < hero.base_num; j++)
			out << hero.base[j].first << " " << hero.base[j].second << " ";
		out << endl;
	}
	out.close();
	cout << "db에 출력 되었습니다." << endl;
}

void search() {
	if (heroes.size() == 0)
		read();
	string name;
	cout << "케릭터 이름을 입력하세요 : ";
	cin >> name;
	bool is_find = false;
	for (int i = 0; i < heroes.size(); i++)
	{
		if (heroes[i].name == name) {
			print(heroes[i]);
			is_find = true;
		}
	}
	if (!is_find)
		cout << "케릭터를 찾을 수 없습니다." << endl;
}

void add() {
	Hero hero;
	cout << "케릭터 등급을 입력하세요 : ";
	cin >> hero.rank;
	cout << "케릭터 직업을 입력하세요 : ";
	cin >> hero.job;
	string name;
	cout << "케릭터 이름을 입력하세요 : ";
	cin >> hero.name;
	if (hero.rank != 1) {
		cout << "조합에 필요한 케릭터 수를 입력하세요 : ";
		cin >> hero.base_num;
		for (int i = 0; i < hero.base_num; i++)
		{
			cout << "조합에 필요한 케릭터 이름[" << i + 1 << "]을 입력하세요 : ";
			cin >> hero.base[i].first;
			hero.base[i].second = 1; // 우선은 그냥 입력해두자
		}
	}
	else
		hero.base_num = 0;
	bool check = false;
	cout << "이대로 입력하겠습니까? (y/n) : ";
	char ans;
	cin >> ans;
	ans == 'y' ? check = true : check = false;
	if (check)
		heroes.push_back(hero);
	else
		cout << "취소 되었습니다." << endl;
}

int UI() {
	int s;
	cout << "******************************************" << endl;
	cout << "히어로즈 랜덤 디펜스 에드온" << endl;
	cout << "1. 검색" << endl;
	cout << "2. 케릭 입력" << endl;
	cout << "3. 종료" << endl;
	cout << "4. Print" << endl;
	cout << "5. Write" << endl;
	cout << "원하시는 번호를 입력하세요 : ";
	cin >> s;
	return s;
}

void erase() {
	int max_erase = 30;
	for (int i = 0; i < max_erase; i++)
		cout << endl;
}

void init() {
	bool done = false;
	read(); // 시작할때 먼저 읽어옴
	do {
		
		int select;
		select = UI();

		switch(select) {
		case 1:
			search();
			break;
		case 2:
			add();
			break;
		case 3:
			done = true;
			cout << "******************************************" << endl;
			break;
		case 4:
			print();
			break;
		case 5:
			write();
			break;
		default:
			cout << "잘못 입력 하셨습니다. 다시 입력해주세요" << endl;
			break;
		}
		//erase();
		
	} while (!done);

}

int main() {

	init();
	
	return 0;
}