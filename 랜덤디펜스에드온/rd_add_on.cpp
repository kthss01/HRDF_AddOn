// 히어로즈 랜덤 디펜스 조합 도우미 
// 국민대학교 컴퓨터공학과 20113273 김태훈

// 개발 이유 
// 조합 도감은 게임 내에 표현 되어는 있지만 바로 하위 케릭터의 조합으로만 표현되어있음
// #1 상위 케릭터를 조합하기 기본 케릭터가 몇개가 필요한지 빠르게 알기 위해서
// #2 기본 케릭터 구성에 따라 어떤 케릭터를 조합해야 할 지 판단 하기 위해서
// * 매 웨이브가 시작될 때마다 랜덤한 기본 케릭터를 주므로 상황에 맞는 조합방향을 정해야함

// 설계방안은 설계서에 정리

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define BASE_NUM 12
#define RANK 5 // 최대 등급
string base_names[] = 
	{ "전사", "도적","격투가","법사","사제","궁수","정령","메카닉",
		"베이비드래곤","다크소울1","다크소울3","다크소울5" };
vector< vector<struct hero> > heroes(RANK);
int sum_hero;
int cur_basehero_num[BASE_NUM];

// 영웅 struct
typedef struct hero {
	string name;
	int rank;
	string job;
	int base_num;
	string base[6];
	int basehero_num[BASE_NUM];
	hero** node;
}Hero;

void makeNode(Hero& hero) {
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
				for (int k = 0; k < heroes[hero.rank-1].size(); k++) {
					if (heroes[hero.rank-1][k].name == hero.base[i]) {
						hero.node[i] = &heroes[hero.rank-1][k];
						isfind = true;
						break;
					}
				}
			}
		}
	}
}

void deleteNode() {
	for (int i = 0; i < heroes.size(); i++) {
		for (int j = 0; j < heroes[i].size(); j++) {
			Hero hero = heroes[i][j];
			if (hero.node != NULL) {
				delete hero.node;
			}
		}
	}
}

void makeGraph() {
	for (int i = 0; i < heroes.size(); i++) {
		for (int j = 0; j < heroes[i].size(); j++) {
			makeNode(heroes[i][j]);
		}
	}
}

void print(Hero hero) {
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

void print() {
	cout << "******************************************" << endl;
	for (int i = heroes.size()-1; i >= 0; i--)
	{
		
		for (int j = 0; j < heroes[i].size(); j++) {
			Hero hero = heroes[i][j];
			if(j==0)
				cout << hero.rank << "성 " << endl;
			print(hero);
		}
		cout << endl;
	}
}

void print_base_hero() {
	cout << "*******************************현재 베이스 영웅 일람******" << endl;
	cout << "\t";
	for (int i = 0; i < BASE_NUM; i++)
	{
		if (cur_basehero_num[i] != 0)
			cout << base_names[i] << "(" << cur_basehero_num[i] << ") ";
	}
	cout << "\n**********************************************************" << endl;
}

void input_base_hero() {
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

	int rank_n = RANK;
	for (int i = 0; i < rank_n; i++){
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
			heroes[hero.rank-1].push_back(hero);
		}
	}
	// 모든 영웅 수
	in >> sum_hero;
	//print();
}

void write() {
	ofstream out;
	out.open("db.txt");
	for (int i = 0; i < heroes.size(); i++) {
		out << heroes[i].size() << endl;
		for (int j = 0; j < heroes[i].size(); j++) {
			Hero hero = heroes[i][j];
			out << hero.rank << " " << hero.job << " ";
			out << hero.name << " " << hero.base_num << " ";
			for (int j = 0; j < hero.base_num; j++)
				out << hero.base[j] << " ";
			out << endl;
		}
	}
	out << sum_hero << endl;
	out.close();
	cout << "db에 출력 되었습니다." << endl;
}

void search(string name) {
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

void search() {
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

void searchRank() {
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

void editUI() {
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

void searchOfBase() {
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

void add() {
	Hero hero;
	cout << "영웅 등급을 입력하세요 : ";
	cin >> hero.rank;
	cout << "영웅 직업을 입력하세요 : ";
	cin >> hero.job;
	string name;
	cout << "영웅 이름을 입력하세요 : ";
	cin >> hero.name;
	if (hero.rank != 1) {
		cout << "조합에 필요한 영웅 수를 입력하세요 : ";
		cin >> hero.base_num;
		for (int i = 0; i < hero.base_num; i++)
		{
			cout << "조합에 필요한 영웅 이름을 입력하세요 : ";
			cin >> hero.base[i];
		}
	}
	else
		hero.base_num = 0;
	bool check = false;
	cout << "이대로 입력하겠습니까? (y/n) : ";
	char ans;
	cin >> ans;
	ans == 'y' ? check = true : check = false;
	if (check) {
		heroes[hero.rank-1].push_back(hero);
		sum_hero++;
	}
	else
		cout << "취소 되었습니다." << endl;
}

int UI() {
	int s;
	cout << "******************************************" << endl;
	cout << "히어로즈 랜덤 디펜스 에드온" << endl;
	print_base_hero();
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
	cin >> s;
	return s;
}

void erase() {
	int max_erase = 30;
	for (int i = 0; i < max_erase; i++)
		cout << endl;
}

int* base_heroes;
int name_index(string name) {
	for (int i = 0; i < BASE_NUM; i++)
		if (name == base_names[i])
			return i;
}

string sort_base_name;

int cmp(Hero h1, Hero h2) {
	return h1.basehero_num[name_index(sort_base_name)]
	> h2.basehero_num[name_index(sort_base_name)];
}

void sortBase() {
	cout << "원하는 베이스영웅 직업을 입력하세요 : ";
	cin >> sort_base_name;
	for (int i = 0; i<heroes.size(); i++) {
		sort(heroes[i].begin(), heroes[i].end(), cmp);
	}
}

void recursive_base(Hero* hero) {
	if (hero->rank == 1)
	{
		base_heroes[name_index(hero->name)]++;
	}
	else {
		for (int i = 0; i < hero->base_num; i++)
			recursive_base(hero->node[i]);
	}
}

void count_base() {
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

void init() {
	bool done = false;
	read(); // 시작할때 먼저 읽어옴
	makeGraph();
	count_base();
	//print(); // 테스트용
	do {
		
		int select;
		select = UI();

		switch(select) {
		case 0:
			input_base_hero();
			break;
		case 1:
			search();
			break;
		case 2:
			searchRank();
			break;
		case 3:
			searchOfBase();
			break;
		case 4:
			sortBase();
			break;
		case 5:
			done = true;
			cout << "******************************************" << endl;
			break;
		case 6:
			print();
			break;
		case 7:
			write();
			break;
		case 8:
			add();
			break;
		default:
			cout << "잘못 입력 하셨습니다. 다시 입력해주세요" << endl;
			break;
		}
		//erase();
		
	} while (!done);

}

/*
int main() {

	init();
	deleteNode();
	return 0;
}*/