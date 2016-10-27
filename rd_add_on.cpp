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
#define RANK 4 // 최대 등급
string base_names[] = 
	{ "전사", "도적","격투가","법사","사제","궁수","정령","메카닉",
		"베이비드래곤","다크소울1","다크소울3","다크소울5" };
vector< vector<struct hero> > heroes(RANK);
int sum_hero;

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
	cout << "}\n";;
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

	int rank_n = 4;
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

void search() {
	if (heroes.size() == 0)
		read();
	string name;
	cout << "케릭터 이름을 입력하세요 : ";
	cin >> name;
	bool is_find = false;
	for (int i = 0; i < heroes.size(); i++)
	{
		for (int j = 0; j < heroes[i].size(); j++) {
			if (heroes[i][j].name == name) {
				print(heroes[i][j]);
				is_find = true;
			}
		}
	}
	if (!is_find)
		cout << "케릭터를 찾을 수 없습니다." << endl;
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
			cout << "조합에 필요한 케릭터 이름을 입력하세요 : ";
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
	cout << "1. 이름 검색" << endl;
	cout << "2. 등급별 검색" << endl;
	cout << "3. 베이스영웅별 정렬" << endl;
	cout << "4. 종료" << endl;
	cout << "5. Print" << endl;
	cout << "6. Write" << endl;
	cout << "7. Add" << endl;
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
		case 1:
			search();
			break;
		case 2:
			searchRank();
			break;
		case 3:
			sortBase();
			break;
		case 4:
			done = true;
			cout << "******************************************" << endl;
			break;
		case 5:
			print();
			break;
		case 6:
			write();
			break;
		case 7:
			add();
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
	deleteNode();
	return 0;
}