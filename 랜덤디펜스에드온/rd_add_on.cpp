// ������� ���� ���潺 ���� ����� 
// ���δ��б� ��ǻ�Ͱ��а� 20113273 ������

// ���� ���� 
// ���� ������ ���� ���� ǥ�� �Ǿ�� ������ �ٷ� ���� �ɸ����� �������θ� ǥ���Ǿ�����
// #1 ���� �ɸ��͸� �����ϱ� �⺻ �ɸ��Ͱ� ��� �ʿ����� ������ �˱� ���ؼ�
// #2 �⺻ �ɸ��� ������ ���� � �ɸ��͸� �����ؾ� �� �� �Ǵ� �ϱ� ���ؼ�
// * �� ���̺갡 ���۵� ������ ������ �⺻ �ɸ��͸� �ֹǷ� ��Ȳ�� �´� ���չ����� ���ؾ���

// �������� ���輭�� ����

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define BASE_NUM 12
#define RANK 5 // �ִ� ���
string base_names[] = 
	{ "����", "����","������","����","����","�ü�","����","��ī��",
		"���̺�巡��","��ũ�ҿ�1","��ũ�ҿ�3","��ũ�ҿ�5" };
vector< vector<struct hero> > heroes(RANK);
int sum_hero;
int cur_basehero_num[BASE_NUM];

// ���� struct
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
				cout << hero.rank << "�� " << endl;
			print(hero);
		}
		cout << endl;
	}
}

void print_base_hero() {
	cout << "*******************************���� ���̽� ���� �϶�******" << endl;
	cout << "\t";
	for (int i = 0; i < BASE_NUM; i++)
	{
		if (cur_basehero_num[i] != 0)
			cout << base_names[i] << "(" << cur_basehero_num[i] << ") ";
	}
	cout << "\n**********************************************************" << endl;
}

void input_base_hero() {
	cout << "���� �����ϰ� �ִ� ���̽� ������ �Է����ּ���" << endl;
	for (int i = 0; i < BASE_NUM; i++) {
		cout << base_names[i] << " : ";
		cin >> cur_basehero_num[i];
		if (i == BASE_NUM - 4) {
			int darksoul; // ��ũ�ҿ� ������ �޾Ƽ� �迭�� ����� ����
			cout << "��ũ�ҿ� : ";
			cin >> darksoul;
			cur_basehero_num[i + 1] = darksoul / 1;
			cur_basehero_num[i + 2] = darksoul / 3;
			cur_basehero_num[i + 3] = darksoul / 5;
			break;
		}
	}
}

void read() {
	// �о�;��� ����
	// ��ϵ� ��ü ���� ��, �� ���� ���տ� �ʿ��� ������ ��, �ش翵�� ����, ��� 
	// ���� Ư¡�� �־��ָ� ������

	ifstream in;
	// �ϴ��� ������ġ�� db.txt �о����
	in.open("db.txt"); 
	if (!in.is_open()) {
		cout << "db�� �о� �� �� �� �����ϴ�." << endl;
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
	// ��� ���� ��
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
	cout << "db�� ��� �Ǿ����ϴ�." << endl;
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
		cout << "������ ã�� �� �����ϴ�." << endl;
	char ans;
	if (hero.rank > 2) {
		cout << hero.name << "�� ������ Ȯ�� �Ͻðڽ��ϱ�? (y/n) ";
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
	cout << "���� �̸��� �Է��ϼ��� : ";
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
		cout << "������ ã�� �� �����ϴ�." << endl;
	char ans;
	cout << "���� ������ ������ Ȯ�� �Ͻðڽ��ϱ�? (y/n) ";
	cin >> ans;
	if (ans == 'y') {
		for (int i = 0; i < hero.base_num; i++) {
			search(hero.base[i]);
		}
	}
}

void searchRank() {
	int rank;
	cout << "����� �Է��ϼ��� : ";
	cin >> rank;
	cout << "******************************************" << endl;
	cout << rank << "��\n";
	for (int i = 0; i < heroes[rank - 1].size(); i++) {
		Hero hero = heroes[rank - 1][i];
		print(hero);
	}
}

void editUI() {
	bool done = false;
	char ans;
	do {
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "��ȣ�� �������ּ��� : ";
		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "�����Ͻ� ������ �Է��ϼ��� : ";
			string name;
			cin >> name;
			int index;
			for (int i = 0; i < BASE_NUM; i++) {
				if (base_names[i] == name)
					index = i;
			}
			cout << "�Է��Ͻ� ������ ���� " << cur_basehero_num[index] << " �Դϴ�." << endl;
			cout << "�����Ͻ� ���ڸ� �Է��ϼ��� : ";
			int num;
			cin >> num;
			cout << "\t" << base_names[index] << "(" << num << ")" << endl;
			cout << "�����Ͻðڽ��ϱ�? (y/n) : ";
			cin >> ans;
			if (ans == 'y')
				cur_basehero_num[index] = num;
			else {
				cout << "������ ��ҵǾ����ϴ�." << endl;
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
	cout << "�ԷµǾ��� ������ ����Ͻðڽ��ϱ�? (y/n) : ";
	cin >> ans;
	
	if (ans == 'n') {
		input_base_hero();
	}

	print_base_hero();
	
	cout << "�Է��� ������ �½��ϱ�? (������ ���Ͻø� n) (y/n) : ";
	cin >> ans;
	if (ans == 'y') {
		cout << "******************************************" << endl;
		int rank;
		cout << "����� ���ϴ� ����� �Է����ּ��� : ";
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
		cout << "�����Ͻðڽ��ϱ�? (y/n) : ";
		cin >> ans;
		if (ans == 'y') {
			editUI();
		}
		else {
			cout << "�Է��� ��ҵǾ����ϴ�" << endl;
		}
	}

}

void add() {
	Hero hero;
	cout << "���� ����� �Է��ϼ��� : ";
	cin >> hero.rank;
	cout << "���� ������ �Է��ϼ��� : ";
	cin >> hero.job;
	string name;
	cout << "���� �̸��� �Է��ϼ��� : ";
	cin >> hero.name;
	if (hero.rank != 1) {
		cout << "���տ� �ʿ��� ���� ���� �Է��ϼ��� : ";
		cin >> hero.base_num;
		for (int i = 0; i < hero.base_num; i++)
		{
			cout << "���տ� �ʿ��� ���� �̸��� �Է��ϼ��� : ";
			cin >> hero.base[i];
		}
	}
	else
		hero.base_num = 0;
	bool check = false;
	cout << "�̴�� �Է��ϰڽ��ϱ�? (y/n) : ";
	char ans;
	cin >> ans;
	ans == 'y' ? check = true : check = false;
	if (check) {
		heroes[hero.rank-1].push_back(hero);
		sum_hero++;
	}
	else
		cout << "��� �Ǿ����ϴ�." << endl;
}

int UI() {
	int s;
	cout << "******************************************" << endl;
	cout << "������� ���� ���潺 �����" << endl;
	print_base_hero();
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
	cout << "���ϴ� ���̽����� ������ �Է��ϼ��� : ";
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
	read(); // �����Ҷ� ���� �о��
	makeGraph();
	count_base();
	//print(); // �׽�Ʈ��
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
			cout << "�߸� �Է� �ϼ̽��ϴ�. �ٽ� �Է����ּ���" << endl;
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