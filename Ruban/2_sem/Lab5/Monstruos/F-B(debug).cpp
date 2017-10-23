#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>

#define INF 0xFFFFFF
#define LIMIT 0xFFFF

using namespace std;

int* Ford_Bellman_for_all(int **C, int n, int start);
bool isStable(int **A, int n);
// int L = 0;
// int Tpr = 0;

int* Ford_Bellman_for_all(int **C, int n, int start) {
	int i, j, k;
	char x;
	static int **D = new int *[2];
	for(i = 0; i < 2; ++i) {
		D[i] = new int [n];
		for(j = 0; j < n; ++j)
			D[i][j] = INF;
	}
	// cout << "Created D" << endl;
	D[0][start] = 0;
	k = 1;
	int k1;
	while( !isStable(D, n) ) {
		// L++;
		k = (++k) % 2;
		k1 = (k + 1) % 2;
		// cout << "|	isStabled -> k = " << k << " k1 = " << k1 << endl;
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				// Tpr++;
				if( D[k1][i] > D[k][j] + C[j][i] ) 
					D[k1][i] = D[k][j] + C[j][i];
			}
			if(D[k1][i] > LIMIT)
				D[k1][i] = INF;
		}
		/*for(j = 0; j < n; ++j) {
			D[0][j] == INF ? cout << "INF" : cout << D[0][j];
			cout << " ";
			D[1][j] == INF ? cout << "INF" : cout << D[1][j];
			cout << endl;
		}*/
		// cin >> x;
		// cout << "Stable?" << endl;
	}
	return D[k1];
}

bool isStable(int **A, int n) {
	for(int i = 0; i < n; ++i) {
		// cout << "|	isStabled -> checked " << i << " vertex" << endl;
		if(!(A[0][i] == A[1][i] && A[0][i] <= LIMIT && A[1][i] <= LIMIT))
			return false;
	}
	// cout << "|	isStabled -> true returned" << endl;
	return true;
}

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

	cout << "Print start vertex (from 0 to " << n-1 << ")" << endl;
	cin >> start;

	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j)
			A[i][j] == INF ? cout << "INF " : cout << A[i][j] << " ";
		cout << endl;
	}
	
	res = Ford_Bellman_for_all(A, n, start);
	cout << endl << endl;
	for(i = 0; i < n; ++i) {
		cout << "mass of way from " << start << " to " << i << " is eq to " << res[i] << endl;
	}
	// int T = L * n * n;
	// cout << "T(n) = " << T << endl;
	// cout << "Tpr(n) = " << Tpr << endl;
	system("pause");
	return 0;
}
