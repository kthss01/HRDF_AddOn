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
#define RANK 4 // �ִ� ���
string base_names[] = 
	{ "����", "����","������","����","����","�ü�","����","��ī��",
		"���̺�巡��","��ũ�ҿ�1","��ũ�ҿ�3","��ũ�ҿ�5" };
vector< vector<struct hero> > heroes(RANK);
int sum_hero;

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
	cout << "}\n";;
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

void search() {
	if (heroes.size() == 0)
		read();
	string name;
	cout << "�ɸ��� �̸��� �Է��ϼ��� : ";
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
		cout << "�ɸ��͸� ã�� �� �����ϴ�." << endl;
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

void add() {
	Hero hero;
	cout << "�ɸ��� ����� �Է��ϼ��� : ";
	cin >> hero.rank;
	cout << "�ɸ��� ������ �Է��ϼ��� : ";
	cin >> hero.job;
	string name;
	cout << "�ɸ��� �̸��� �Է��ϼ��� : ";
	cin >> hero.name;
	if (hero.rank != 1) {
		cout << "���տ� �ʿ��� �ɸ��� ���� �Է��ϼ��� : ";
		cin >> hero.base_num;
		for (int i = 0; i < hero.base_num; i++)
		{
			cout << "���տ� �ʿ��� �ɸ��� �̸��� �Է��ϼ��� : ";
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
	cout << "1. �̸� �˻�" << endl;
	cout << "2. ��޺� �˻�" << endl;
	cout << "3. ���̽������� ����" << endl;
	cout << "4. ����" << endl;
	cout << "5. Print" << endl;
	cout << "6. Write" << endl;
	cout << "7. Add" << endl;
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
			cout << "�߸� �Է� �ϼ̽��ϴ�. �ٽ� �Է����ּ���" << endl;
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