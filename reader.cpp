#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct person
{
	char fio[40];
	int year;
	char sex;
	int ms;
	int child;
	char edu;
	int salary;
};
int main() {
	ifstream manbin("outman.bin", ios::binary);
	ifstream fembin("outfemale.bin", ios::binary);
	person x;
	if (!manbin)
	{
		cout << "File (man) not found" << endl;
		system("pause");
		exit(-1);
	}
	if (!fembin)
	{
		cout << "File (fem) not found" << endl;
		system("pause");
		exit(-1);
	}
	cout << "Men list" << endl;
	while (manbin.read((char*)&x, sizeof(struct person)))
	{
		cout << x.fio << ' ' << x.year << ' ' << x.child << endl;
	}
	cout << "Women list" << endl;
	while (fembin.read((char*)&x, sizeof(struct person)))
	{
		cout << x.fio << ' ' << x.year << ' ' << x.child << endl;
	}
	manbin.close();
	fembin.close();
	system("pause");
}
