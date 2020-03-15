#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");
const int maxT = 100, wid = 3, indent = 2;
int count_of_q;
/* Moves = {L = -1, R = 1; H = 0}
Q = {!,1, 2, 3...} 
count_of_q count of different conditions except stop condition(!).
input:
{Alphabet},
count_of_q,
array x,
work table.
*/
struct tur {
	char a;
	int q, M;
};
struct graph {
	vector < int > Q;
	vector < bool > use;
	vector < char > x0;
	int numOfUse_a1_q2, cout_of_turns;
	string stop;
};
void row(int size, int wid) {
	out << setw(indent);
	for (int i = 0; i < size * (wid+1); i++) {
		out << '_';
	}
	out << endl;
}
void upRow(int size, int wid) {
	out << setw(indent);
	for (int i = 0; i < size * (wid + 1); i++) {
		out << '~';
	}
	out << endl;
}
void Table(string x, int wid) {
	//row(x.size(), wid);
	out << setw(indent-1) << '|';
	for (int i = 0; i < x.size(); i++) {
		out << setw(wid-1) << x[i] <<" |";
	}
	out << endl;
	//upRow(x.size(), wid);
	out << setw(indent - 1) << '|';
	for (int i = 0; i < x.size(); i++) {
		out << setw(wid) << i-maxT << '|';
	}
	out << endl << endl;
	//upRow(x.size(), wid);
}
int count_of_true(vector <bool> used) {
	int k = 0;
	for (int i = 0; i < used.size(); i++)
		if (used[i])
			k++;
	return k;
}
void show(string x, graph& f, vector < char > &Alphabet) {
	bool t = true;
	//out << x << endl;
	Table(x, wid);
	out << "Count of condition q1 = " << f.Q[0] << ". " + f.stop <<  endl;
	for (int i = 0; i < f.Q.size(); i++) {
		out << "Count of condition q"<<i+1<<" = "<< f.Q[i] <<". " + f.stop << endl;
		if (f.Q[i] == 0) t = false;
	}
	out << "Count of changed elements: " << count_of_true(f.use) << ". " + f.stop << endl;
	int k = 0;
	for (int i = 0; i < x.size(); i++)
		if (x[i] != Alphabet[0]) k++;
	out << "Count of non empty elemets: " << k << ". " + f.stop << endl;
	t ? out << "Program was in each conditions" << ". " + f.stop << endl : out << "Program wasn't in each conditions" << ". " + f.stop << endl;
	if (!f.x0.empty())
		for (int i = 0; i < f.x0.size(); i++)
			out << "On t = " << (i + 1) * 10 << " x0 = " << f.x0[i] << ". " + f.stop << endl;
	else out << "Program has played less than 10 times" << ". " + f.stop << endl;
	out << "Count of use a1 and q2: " << f.numOfUse_a1_q2 << ". " + f.stop << endl;
	out << "Count of changing rotation: " << f.cout_of_turns << ". " + f.stop << endl;
}
void create_workProgram(vector <vector < tur > >& program, int n, int m) {
	for (int i = 0; i < n; i++) {
		char c;
		in >> c;
		for (int j = 0; j < m; j++) {
			char tempM, tempQ;
			in >> program[(int)c][j].a >> tempQ >> tempM;
			if (tempQ == '!') program[(int)c][j].q = -1;
			else program[(int)c][j].q = tempQ - '0';
			switch (tempM){
				case 'R':
				{
					program[(int)c][j].M = 1;
					break;
				}
				case 'L':
				{
					program[(int)c][j].M = -1;
					break;
				}
				case 'H':
				{
					program[(int)c][j].M = 0;
					break;
				}
			}
		}
	}
}
void create_Alphabet(vector < char >& Alphabet) {
	string s;
	getline(in, s);
	for (int i = 0; i < s.size(); i++)
	{
		if(s[i] != ' ')
			Alphabet.push_back(s[i]);
	}
}
void create_graph(graph& forX, int size) {
	forX.Q.resize(count_of_q, 0);
	forX.use.resize(size, false);
	forX.numOfUse_a1_q2 = 0;
	forX.cout_of_turns = 0;
}
string work(string x, int k, int workQ, vector <vector < tur > >& program, graph& forX, char a2) {
	int t = 0, previousM = 0;
	while (t < maxT && workQ != -1) {
		t++;
		forX.Q[workQ - 1]++;
		forX.use[k] = 1;
		if (workQ == 2 && x[k] == a2) forX.numOfUse_a1_q2++;
		tur current = program[(int)x[k]][workQ-1];
		if ((previousM == 1 && current.M == -1) || (previousM == -1 && current.M == 1)) forX.cout_of_turns++;
		x[k] = current.a;
		workQ = current.q;
		k += current.M;
		if(current.M != 0)
			previousM = current.M;
		if (t % 10 == 0) forX.x0.push_back(x[maxT]);
	}
	if (t >= maxT) forX.stop = "The programm has stoped by count of T";
	else if (workQ == -1) forX.stop = "The program has stopped by q0(!)";
	return x;
}
int main() {
	vector <char> Alphabet;
	create_Alphabet(Alphabet);
	in >> count_of_q;
	vector < tur > row(count_of_q);
	vector <vector < tur > > program(256, row);
	string x, s;
	graph forX;
	x.resize(maxT, Alphabet[0]);
	if (!in) cout << -1;
	in >> s;
	x += s;
	x.resize(2 * maxT, Alphabet[0]);
//	out << s.size()<<endl;
	Table(x, wid);
	//out << x << endl;
	create_workProgram(program, Alphabet.size(), count_of_q);
	create_graph(forX, x.size());
	x = work(x, maxT, 1, program, forX, Alphabet[1]);
	//out << x << endl;
	show(x, forX, Alphabet);
	out << "The program was played for alphabet:" << endl;
	for (int i = 0; i < Alphabet.size(); i++)
	{
		out << Alphabet[i]<< " ";
	}
}