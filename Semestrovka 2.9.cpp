#include <iostream>
#include <cmath>
using namespace std;
double** create(int n, int m, char c) {
	double** z = new double* [n];
	for (int i = 0; i < n; i++) {
		z[i] = new double[m];
		for (int j = 0; j < m; j++) {
			cout << c << "[" << i << "][" << j << "] = ";
			cin >> z[i][j];
		}
	}
	return z;
}
void show(double** x, int n, int m) {
	cout << "Matrix X5:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << x[i][j] << " ";
		}
		cout << endl;
	}
}
double** E1(double** a, double** b, int n, int m) {
	double** c = new double* [n];
	for (int i = 0; i < n; i++) {
		c[i] = new double[m];
		for (int j = 0; j < m; j++) {
			if (i <= j)
				c[i][j] = a[i][j] + b[i][j];
			else
				c[i][j] = a[i][j] - b[i][j];
		}
	}
	return c;
}
double** E2(double** a, double** b, int n, int m) {
	double** c = new double* [n];
	for (int i = 0; i < n; i++) {
		c[i] = new double[m];
		for (int j = 0; j < m; j++) {
			if (i == j)
				c[i][j] = exp(-(a[i][j] + b[i][j]));
			else
				c[i][j] = sqrt(fabs(a[i][j] + b[i][j]));
		}
	}
	return c;
}
double F(double** a, int n, int m) {
	double max, s = 0;
	for (int k = 0; k < n; k++)
		s += a[0][k];
	max = fabs(s);
	for (int i = 1; i < n; i++) {
		s = 0;
		for (int k = 0; k < n; k++)
			s += a[i][k];
		if (fabs(s) > max)
			max = fabs(s);
	}
	return max;
}
double** create_x5(double** x, double** y, int n, int m) {
	for (int i = 0; i < 5; i++) {
		if (F(x, n, m) < F(y, n, m))
			x = E1(x, y, n, m);
		else x = E2(y, x, n, m);
	}
	return x;
}
int main() {
	int n, m;
	cout << "Enter count of rows: n = ";
	cin >> n;
	cout << "Enter count of columns: m = ";
	cin >> m;
	double** x = create(n, m, 'x'), ** y = create(n, m, 'y');
	x = create_x5(x, y, n, m);
	show(x, n, m);
}