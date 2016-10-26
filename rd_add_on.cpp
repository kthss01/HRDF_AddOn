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

#define BASE_NUM 8
#define RANK 6 // �ִ� ���
vector< vector<struct hero> > heroes(RANK);
int sum_hero;

// ���� struct
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
		for (int j = 0; j < heroes[i].size(); j++) {
			Hero hero = heroes[i][j];
			cout << hero.rank << "�� " << hero.name << " ";
			for (int j = 0; j < hero.base_num; j++)
				cout << hero.base[j].first <<
				"(" << hero.base[j].second << ") ";
			cout << endl;
		}
		cout << endl;
	}
}
void print(Hero hero) {
	cout << "******************************************" << endl;
	cout << hero.rank << "�� " << hero.name << " ";
	for (int j = 0; j < hero.base_num; j++)
		cout << hero.base[j].first <<
		"(" << hero.base[j].second << ") ";
	cout << endl;
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
			for (int k = 0; k < hero.base_num; k++) {
				in >> hero.base[k].first;
				in >> hero.base[k].second;
			}
			heroes[hero.rank-1].push_back(hero);
		}
	}
	// ��� ���� ��
	in >> sum_hero;
	//print();
}

bool cmp(Hero h1, Hero h2) {
	return h1.rank > h2.rank;
}

void write() {
	//sort(heroes.begin(), heroes.end(), cmp);
	ofstream out;
	out.open("db.txt");
	for (int i = 0; i < heroes.size(); i++) {
		out << heroes[i].size() << endl;
		for (int j = 0; j < heroes[i].size(); j++) {
			Hero hero = heroes[i][j];
			out << hero.rank << " " << hero.job << " ";
			out << hero.name << " " << hero.base_num << " ";
			for (int j = 0; j < hero.base_num; j++)
				out << hero.base[j].first << " " << hero.base[j].second << " ";
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
			cout << "���տ� �ʿ��� �ɸ��� �̸�[" << i + 1 << "]�� �Է��ϼ��� : ";
			cin >> hero.base[i].first;
			hero.base[i].second = 1; // �켱�� �׳� �Է��ص���
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
	cout << "1. �˻�" << endl;
	cout << "2. �ɸ� �Է�" << endl;
	cout << "3. ����" << endl;
	cout << "4. Print" << endl;
	cout << "5. Write" << endl;
	cout << "���Ͻô� ��ȣ�� �Է��ϼ��� : ";
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
	read(); // �����Ҷ� ���� �о��
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
			cout << "�߸� �Է� �ϼ̽��ϴ�. �ٽ� �Է����ּ���" << endl;
			break;
		}
		//erase();
		
	} while (!done);

}

int main() {

	init();
	
	return 0;
}