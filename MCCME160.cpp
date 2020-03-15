#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
	int n, start, end;
	cin >> n;
	vector <int > d(n, 0), p(n);
	vector <bool> used(n);
	vector < vector < int > > graph(n, d);
	queue <int > q;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> graph[i][j];
	cin >> start >> end;
	--start;
	--end;
	q.push(start);
	p[start] = -1;
	used[start] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < n; i++) {
			int t;
			if (graph[v][i]) {
				t = i;
				if (!used[t]) {
					used[t] = 1;
					q.push(t);
					p[t] = v;
					d[t] = d[v] + 1;
				}
			}
		}
	}
	if (!used[end]) {
		cout << -1;
	}
	else {
		vector < int > path;
		cout << d[end] << endl;
		if (d[end]) {
			for (int i = end; i != -1; i = p[i])
				path.push_back(i + 1);
			reverse(path.begin(), path.end());
			for (int i = 0; i < path.size(); i++)
				cout << path[i] << " ";
		}
	}
	return 0;
}
