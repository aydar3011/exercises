#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct horse {
	int x, y;
    horse() {}
    horse(int x, int y) {
		this->x = x;
		this->y = y;
	} 
	horse operator +(int s)
	{
        horse tmp;
		tmp.x = this->x + s;
        tmp.y = this->y + s;
		return tmp;
	}
};

int main()
{
	int n, x, y;
	cin >> n >> x >> y;
	horse start(--x, --y);
	cin >> x >> y;
	horse end(--x, --y);
	vector < vector < int > > distance(n, vector < int >(n, 0));
	vector < vector < bool > > used(n, vector < bool >(n,false));
	vector < vector < horse > > parrents(n, vector < horse >(n));
	queue < horse > q;
	q.push(start);
	parrents[start.x][start.y].x = -1;
	parrents[start.x][start.y].y = -1;
	used[start.x][start.y] = true;
	while (!q.empty()) {
		horse v = q.front();
        q.pop();
        if (v.x + 2 < n)
        {
            int x = v.x + 2;
            if (v.y + 1 < n && (!used[x][v.y + 1]))
            {
                int y = v.y + 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
            if (v.y - 1 >= 0 && (!used[x][v.y - 1]))
            {
                int y = v.y - 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
        }
        if (v.x - 2 >= 0)
        {
            int x = v.x - 2;
            if (v.y + 1 < n && (!used[x][v.y + 1]))
            {
                int y = v.y + 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
            if (v.y - 1 >= 0 && (!used[x][v.y - 1]))
            {
                int y = v.y - 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
        }
        if (v.y + 2 < n)
        {
            int y = v.y + 2;
            if (v.x + 1 < n && (!used[v.x + 1][y]))
            {
                int x = v.x + 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
            if (v.x - 1 >= 0 && (!used[v.x - 1][y]))
            {
                int x = v.x - 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
        }
        if (v.y - 2 >= 0)
        {
            int y = v.y - 2;
            if (v.x + 1 < n && (!used[v.x + 1][y]))
            {
                int x = v.x + 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
            if (v.x - 1 >= 0 && (!used[v.x - 1][y]))
            {
                int x = v.x - 1;
                q.push(horse(x, y));
                distance[x][y] = distance[v.x][v.y] + 1;
                parrents[x][y] = v;
                used[x][y] = true;
            }
        }
	}
    vector < horse > path;
    cout << distance[end.x][end.y] << endl;
    for (horse i = end; i.x != -1, i.y != -1; i = parrents[i.x][i.y])
        path.push_back(i+1);
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
        cout << path[i].x << " " << path[i].y << endl;
}
