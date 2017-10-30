#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <utility>
#include <list>
#include <algorithm>

#define INF 0xFFFFFF
#define LIMIT 0xFFFF
using namespace std;

void print_way(int *W, int n, int start, int end);
int *Dijkstra(int **C, int n, int start, int *W);

int main(int argc, char const *argv[])
{
	
	int i, j;
	int n = 6;
	int *res;
	int start = 0;

	int statA[6][6] = {
		{0, 7, INF, INF, INF, 14},
		{INF, 0, 10, 15, INF, INF},
		{9, INF, 0, 11, INF, INF},
		{INF, INF, INF, 0, 6, INF},
		{INF, INF, INF, INF, 0, 9},
		{INF, INF, 2, INF, INF, 0}
	};

	int **A = new int *[n];
	for(i = 0; i < n; ++i) {
		A[i] = new int [n];
		for(j = 0; j < n; ++j) {
			A[i][j] = statA[i][j];
		}
	}

	int *W = new int [n];
	cout << "Print start vertex (from 0 to " << n-1 << ")" << endl;
	cin >> start;
	for(i = 0; i < n; ++i)
		W[i] = start;
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j)
			A[i][j] == INF ? cout << "INF " : cout << A[i][j] << " ";
		cout << endl;
	}

	res = Dijkstra(A, n, start, W);
	for(i = 0; i < n; ++i) {
		cout << "mass of way from " << start << " to " << i << " is eq to " << res[i] << ":";
		print_way(W, n, start, i);
		cout << endl;
	}
	system("pause");
	return 0;
}

void print_way(int *W, int n, int start, int end){
	int a;
	int i = end;
	while((i != start)) {
		cout << i << " <- ";
		i = W[i];
	}
	cout << i;
	return;
}

int *Dijkstra(int **C, int n, int start, int *W) {
	int *d = new int [n];
	bool *v = new bool [n];
	int temp, min, minindex;

	for (int i = 0; i < n; i++) {
		d[i] = INF;
		v[i] = false;
		W[i] = start;
	}
	d[start] = 0;

	do {
		minindex = INF;
		min = INF;
		for (int i = 0; i < n; i++) {
			if (!(v[i]) && (d[i] < min)) {
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != INF) {
			for (int i = 0; i < n; i++) {
				if (C[minindex][i] > 0 && C[minindex][i] < LIMIT) {
					temp = min + C[minindex][i];
					if(temp > LIMIT)
						temp = INF;
					if (temp < d[i]) {
						d[i] = temp;
						W[i] = minindex;
					}
				}
			}
			v[minindex] = true;
		}
	} while (minindex < INF);

	return d;
}
