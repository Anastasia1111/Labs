#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>

#define INF 0xFFFFFF
#define LIMIT 0xFFFF

using namespace std;

int* Ford_Bellman_for_all(int **C, int n, int start, int *W);
void print_way(int *W, int n, int start, int end);

int main(int argc, char const *argv[])
{
	int i, j;
	int n = 4;
	int *res;
	int start = 0;

	int statA[4][4] = {
		{0, 2, INF, INF},
		{INF, 0, 6, INF},
		{3, INF, 0, 4},
		{INF, 6, INF, 0}
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
	
	res = Ford_Bellman_for_all(A, n, start, W);
	cout << endl << endl;

	for(i = 0; i < n; ++i) {
		cout << "mass of way from " << start << " to " << i << " is eq to " << res[i] << ":";
		print_way(W, n, start, i);
		cout << endl;
	}
	system("pause");
	return 0;
}


int* Ford_Bellman_for_all(int **C, int n, int start, int *W) {
	int z ,i, j, k;
	char x;
	int **D = new int *[2];
	for(i = 0; i < 2; ++i) {
		D[i] = new int [n];
		for(j = 0; j < n; ++j)
			D[i][j] = INF;
	}
	D[0][start] = 0;

	k = 1;
	int k1;
	bool changed = false;
	for(z = 0; z < n-1; z++) {
		k = (++k) % 2;
		k1 = (k + 1) % 2;
		for(i = 0; i < n; ++i) {
			D[k1][i] = D[k][i];
			for(j = 0; j < n; ++j) {
				if( D[k1][i] > D[k][j] + C[j][i] ) { 
					D[k1][i] = D[k][j] + C[j][i];
					W[i] = j;
					changed = true;
				}
			}
			if(D[k1][i] > LIMIT)
				D[k1][i] = INF;
		}
		if(!changed)
			break;
	}
	return D[k1];
}

void print_way(int *W, int n, int start, int end){
	int i = end;
	while((i != start)) {
		cout << i << " <- ";
		i = W[i];
	}
	cout << i;
	return;
}
