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
int main()
{
	ifstream in("arb.txt");
	ofstream mout("outman.bin", ios::binary);
	ofstream fout("outfemale.bin", ios::binary);
	person x;
	int k1 = 0;
	int k2 = 0;
	if (!in)
	{
		cout << "File not found!" << endl;
		system("pause");
		exit(-1);
	}
	while (in >> x.fio >> x.year >> x.sex >> x.ms >> x.child >> x.edu >> x.salary)
	{
		if ((x.sex == 'm') && ((2020 - x.year) <= 40) && ((2020 - x.year) >= 18)
			&& (x.edu == 'v') && (x.salary >= 75000))
		{
			mout.write((char*)&x, sizeof(struct person));

			k1++;
		}
		if ((x.sex == 'f') && ((2020 - x.year) <= 40) && ((2020 - x.year) >= 20) && (x.edu == 'v'))
		{
			fout.write((char*)&x, sizeof(struct person));
			k2++;
		};
	}
	in.close();
	fout.close();
	mout.close();
	
	return 0;
}