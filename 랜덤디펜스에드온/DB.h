#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define RANK 5
#define BASE_NUM 12

class Hero {
public:
	string name;
	int rank;
	string job;
	string base[6];
	int base_num;
	int basehero_num[BASE_NUM];
	Hero** node;
};

vector< vector<Hero> > heroes(RANK);

class DB {
private:
	string base_names[BASE_NUM] =
	{ "전사", "도적","격투가","법사","사제","궁수","정령","메카닉",
		"베이비드래곤","다크소울1","다크소울3","다크소울5" };
	int sum_hero; // 모든 영웅의 수
	int cur_basehero_num[BASE_NUM];
	int* base_heroes;
	string sort_base_name;
public:
	~DB() {
		deleteNode();
	}
	void read();
	void search();
	void search(string name);
	void searchRank();
	void searchOfBase();

	void makeNode(Hero& hero);
	void deleteNode();
	void makeGraph();

	void print();
	void print(Hero hero);
	void print_base_hero();

	void input_base_hero();

	void editUI();
	void sortBase();
	int cmp(Hero h1, Hero h2);

	int name_index(string name);
	void recursive_base(Hero* hero);
	void count_base();
};

void DB::read() {
	ifstream in;
	in.open("db.txt");
	if (!in.is_open()) {
		cout << "db를 읽어 올 수 가 없습니다." << endl;
		exit(1);
	}

	int rank_n = RANK;
	for (int i = 0; i < rank_n; i++) {
		int num_rank;
		in >> num_rank;
		for (int j = 0; j < num_rank; j++) {
			Hero hero;
			in >> hero.rank;
			in >> hero.job;
			in >> hero.name;
			in >> hero.base_num;
			for (int k = 0; k < hero.base_num; k++)
				in >> hero.base[k];
			heroes[hero.rank - 1].push_back(hero);
		}
	}
	// 모든 영웅 수
	in >> sum_hero;
	in.close();
}

void DB::search() {
	if (heroes.size() == 0)
		read();
	string name;
	cout << "영웅 이름을 입력하세요 : ";
	cin >> name;
	cout << "******************************************" << endl;
	Hero hero;
	bool is_find = false;
	for (int i = 0; i < heroes.size(); i++)
	{
		for (int j = 0; j < heroes[i].size(); j++) {
			if (heroes[i][j].name == name) {
				hero = heroes[i][j];
				print(hero);
				is_find = true;
			}
		}
	}
	if (!is_find)
		cout << "영웅을 찾을 수 없습니다." << endl;
	char ans;
	cout << "조합 영웅의 조합을 확인 하시겠습니까? (y/n) ";
	cin >> ans;
	if (ans == 'y') {
		for (int i = 0; i < hero.base_num; i++) {
			search(hero.base[i]);
		}
	}
}

void DB::search(string name) {
	Hero hero;
	bool is_find = false;
	for (int i = 0; i < heroes.size(); i++)
	{
		for (int j = 0; j < heroes[i].size(); j++) {
			if (heroes[i][j].name == name) {
				hero = heroes[i][j];
				print(hero);
				is_find = true;
			}
		}
	}
	if (!is_find)
		cout << "영웅을 찾을 수 없습니다." << endl;
	char ans;
	if (hero.rank > 2) {
		cout << hero.name << "의 조합을 확인 하시겠습니까? (y/n) ";
		cin >> ans;
		if (ans == 'y') {
			for (int i = 0; i < hero.base_num; i++) {
				search(hero.base[i]);
			}
		}
	}
}

void DB::searchRank() {
	int rank;
	cout << "등급을 입력하세요 : ";
	cin >> rank;
	cout << "******************************************" << endl;
	cout << rank << "성\n";
	for (int i = 0; i < heroes[rank - 1].size(); i++) {
		Hero hero = heroes[rank - 1][i];
		print(hero);
	}
}

void DB::searchOfBase() {
	char ans;
	cout << "입력되었던 정보를 사용하시겠습니까? (y/n) : ";
	cin >> ans;

	if (ans == 'n') {
		input_base_hero();
	}

	print_base_hero();

	cout << "입력한 정보가 맞습니까? (수정을 원하시면 n) (y/n) : ";
	cin >> ans;
	if (ans == 'y') {
		cout << "******************************************" << endl;
		int rank;
		cout << "출력을 원하는 등급을 입력해주세요 : ";
		cin >> rank;

		for (int i = 0; i < heroes[rank - 1].size(); i++) {
			Hero hero = heroes[rank - 1][i];
			bool check = true;
			for (int j = 0; j < BASE_NUM; j++) {
				if (hero.basehero_num[j] > cur_basehero_num[j]) {
					check = false;
					break;
				}
			}
			if (check)
				print(hero);
		}
	}
	else {
		cout << "수정하시겠습니까? (y/n) : ";
		cin >> ans;
		if (ans == 'y') {
			editUI();
		}
		else {
			cout << "입력이 취소되었습니다" << endl;
		}
	}
}

void DB::makeNode(Hero& hero) {
	if (hero.base_num == 0) {
		hero.node = NULL;
	}
	else {
		hero.node = new Hero*[hero.base_num];
		for (int i = 0; i < hero.base_num; i++) {
			bool isfind = false;
			for (int j = hero.rank - 2; j >= 0; j--) {
				for (int k = 0; k < heroes[j].size(); k++) {
					if (heroes[j][k].name == hero.base[i]) {
						hero.node[i] = &heroes[j][k];
						isfind = true;
						break;
					}
				}
				if (isfind)
					break;
			}
			if (!isfind)
			{
				for (int k = 0; k < heroes[hero.rank - 1].size(); k++) {
					if (heroes[hero.rank - 1][k].name == hero.base[i]) {
						hero.node[i] = &heroes[hero.rank - 1][k];
						isfind = true;
						break;
					}
				}
			}
		}
	}
}

void DB::deleteNode() {
	for (int i = 0; i < heroes.size(); i++) {
		for (int j = 0; j < heroes[i].size(); j++) {
			Hero hero = heroes[i][j];
			if (hero.node != NULL) {
				delete hero.node;
			}
		}
	}
}

void DB::makeGraph() {
	for (int i = 0; i < heroes.size(); i++) {
		for (int j = 0; j < heroes[i].size(); j++) {
			makeNode(heroes[i][j]);
		}
	}
}

void DB::print() {
	cout << "******************************************" << endl;
	for (int i = heroes.size() - 1; i >= 0; i--)
	{

		for (int j = 0; j < heroes[i].size(); j++) {
			Hero hero = heroes[i][j];
			if (j == 0)
				cout << hero.rank << "성 " << endl;
			print(hero);
		}
		cout << endl;
	}
}

void DB::print(Hero hero) {
	cout << hero.name;
	if (hero.base_num != 0)
		cout << " (";
	for (int k = 0; k < hero.base_num; k++) {
		cout << hero.base[k];
		if (k == hero.base_num - 1)
			cout << ")";
		else
			cout << " ";
	}
	cout << "\n\t{ ";
	for (int k = 0; k < BASE_NUM; k++) {
		if (hero.basehero_num[k] != 0)
			cout << base_names[k] << "(" << hero.basehero_num[k] << ") ";
	}
	cout << "}\n";
}

void DB::print_base_hero() {
	cout << "*******************************현재 베이스 영웅 일람******" << endl;
	cout << "\t";
	for (int i = 0; i < BASE_NUM; i++)
	{
		if (cur_basehero_num[i] != 0)
			cout << base_names[i] << "(" << cur_basehero_num[i] << ") ";
	}
	cout << "\n**********************************************************" << endl;
}

void DB::input_base_hero() {
	cout << "현재 소지하고 있는 베이스 영웅을 입력해주세요" << endl;
	for (int i = 0; i < BASE_NUM; i++) {
		cout << base_names[i] << " : ";
		cin >> cur_basehero_num[i];
		if (i == BASE_NUM - 4) {
			int darksoul; // 다크소울 총합을 받아서 배열에 계산해 저장
			cout << "다크소울 : ";
			cin >> darksoul;
			cur_basehero_num[i + 1] = darksoul / 1;
			cur_basehero_num[i + 2] = darksoul / 3;
			cur_basehero_num[i + 3] = darksoul / 5;
			break;
		}
	}
}

void DB::editUI() {
	bool done = false;
	char ans;
	do {
		cout << "1. 수정" << endl;
		cout << "2. 종료" << endl;
		cout << "번호를 선택해주세요 : ";
		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "수정하실 직업을 입력하세요 : ";
			string name;
			cin >> name;
			int index;
			for (int i = 0; i < BASE_NUM; i++) {
				if (base_names[i] == name)
					index = i;
			}
			cout << "입력하신 직업에 수는 " << cur_basehero_num[index] << " 입니다." << endl;
			cout << "수정하실 숫자를 입력하세요 : ";
			int num;
			cin >> num;
			cout << "\t" << base_names[index] << "(" << num << ")" << endl;
			cout << "수정하시겠습니까? (y/n) : ";
			cin >> ans;
			if (ans == 'y')
				cur_basehero_num[index] = num;
			else {
				cout << "수정이 취소되었습니다." << endl;
			}
		}
		else
		{
			done = true;
		}
	} while (!done);
}
/*
void DB::sortBase() {
	cout << "원하는 베이스영웅 직업을 입력하세요 : ";
	cin >> sort_base_name;
	for (int i = 0; i<heroes.size(); i++) {
		sort(heroes[i].begin(), heroes[i].end(), cmp);
	}
}

int DB::cmp(Hero h1, Hero h2) {
	return h1.basehero_num[name_index(sort_base_name)]
	> h2.basehero_num[name_index(sort_base_name)];
}*/

int DB::name_index(string name) {
	for (int i = 0; i < BASE_NUM; i++)
		if (name == base_names[i])
			return i;
}

void DB::recursive_base(Hero* hero) {
	if (hero->rank == 1)
	{
		base_heroes[name_index(hero->name)]++;
	}
	else {
		for (int i = 0; i < hero->base_num; i++)
			recursive_base(hero->node[i]);
	}
}

void DB::count_base() {
	for (int i = 0; i < heroes.size(); i++)
	{
		for (int j = 0; j < heroes[i].size(); j++) {
			for (int k = 0; k < BASE_NUM; k++)
				heroes[i][j].basehero_num[k] = 0;
			base_heroes = heroes[i][j].basehero_num;
			recursive_base(&heroes[i][j]);
		}
	}
}