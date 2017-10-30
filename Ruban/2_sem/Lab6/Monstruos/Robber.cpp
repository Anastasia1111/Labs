#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int i, j, M;
    int n = 3;
    int statM[] = {3, 5, 8};
    int statC[] = {8, 14, 23};
    cout << "M = ";
    cin >> M;
    int *m = new int [n];
    int *c = new int [n];
    double *f = new double [M + 1];
    for(i = 0; i < n; ++i) {
        m[i] = statM[i];
        c[i] = statC[i];
    }


    for(i = 0; i < n; ++i) {
        m[i] = statM[i];
        c[i] = statC[i];
        cout << "m[" << i << "] = " << m[i] << " ";
        cout << "c[" << i << "] = " << c[i] << " ";
        cout << endl;
    }
    int temp, max, ftemp;
    for(i = 0; i < M + 1; ++i) {
        max = 0;
        f[i] = 0.0;
        temp = i - m[0];
        temp >= 0 ? max = f[temp] + c[0] : max = 0;

        for(j = 1; j < n; ++j) {
            temp = i - m[j];
            if(temp >= 0) {
                ftemp = f[temp] + c[j];
                if(ftemp > max) {
                    max = ftemp;
                }
            }
        }
        f[i] = max;
        cout << "f[" << i << "] = " << f[i] << endl;
    }
    cout << "max cost is eq to " << f[M] << endl;
    system("pause");
    return 0;
}
