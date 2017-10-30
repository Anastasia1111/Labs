#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

void print(int **f, int **jm, int n, int up, int down);

int main() {
    int i, j, M;
    int n = 4;
    int statR[] = {10, 20, 50, 1, 100};
    int *r = new int [n + 1];
    for(i = 0; i < n+1; ++i)
        r[i] = statR[i];
    int **f = new int *[n];
    for(i = 0; i < n; ++i) {
        f[i] = new int [n];
        for(j = 0; j < n; ++j)
            f[i][j] = -1;
    }
    for(i = 0; i < n; ++i)
        f[i][i] = 0;

    int t, k, temp;
    int **jm = new int *[n];
    for(i = 0; i < n; ++i) {
        jm[i] = new int [n];
        for(j = 0; j < n; ++j)
            jm[i][j] = -1;
    }
    for(t = 1; t < n; ++t) {
        for(k = 0; k < n-t; ++k) { 
            jm[k][k+t] = k;
            f[k][k+t] = f[k][k] + f[k+1][k+t] + r[k]*r[k+1]*r[k+t+1];
            for(j = k + 1; j < k+t; ++j) {
                temp = f[k][j] + f[j+1][k+t] + r[k]*r[j+1]*r[k+t+1];
                if(temp < f[k][k+t]) {
                    jm[k][k+t] = j;
                    f[k][k+t] = temp;
                }
            }
            //cout << "f(" << k+1 << "," << k+t+1 << ") = min<f(" << k+1 << "," << jb+1 << ") + f(" << jb + 2 << "," << k+t+1 << ") + " << r[k] << "*" << r[jb+1] << "*" <<  r[k+t+1] << ">" << endl;
        }
    }

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j)
            cout << f[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j)
            cout << jm[i][j] << " ";
        cout << endl;
    } 

    cout << endl;
    print(f, jm, n, 0, n-1);
    cout << endl;
    system("pause");
    return 0;
}

void print(int **f, int **jm, int n, int up, int down) {
    switch(down - up) {
        case 0: {
            cout << " M[" << up+1 << "] ";
            return;
        }
        case 1: {
            cout << "( ";
            cout << "M[" << up+1 << "] * M[" << down+1 << "]";
            cout << " )";
            return;
        }
        default: {
            cout << "( ";
            print(f, jm, n, up, jm[up][down]);
            print(f, jm, n, jm[up][down] + 1, down);
            cout << " )";
            return;
        }
    }
}
