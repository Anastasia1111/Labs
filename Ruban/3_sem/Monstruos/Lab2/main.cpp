#include <iostream>
#include <cstdlib>
#include "fracmatrixsymplex.h"


using namespace std;


Frac **arr;
int sizex, sizey;

//matrix[sizex][sizey]
int main()
{
    int i, j;

    FILE *f = fopen("matrix.txt", "r+");
    fscanf(f, "%i %i", &sizex, &sizey);
    cout << "sizex = " << sizex << endl
         << "sizey = " << sizey << endl
         << endl;
    int bufNumer, bufDenom;
    arr = new Frac *[sizex];
    for(i = 0; i < sizex; ++i) {
        arr[i] = new Frac [sizey];
        for(j = 0; j < sizey; ++j) {
            fscanf(f, "%i/%i", &bufNumer, &bufDenom);
            arr[i][j].setNewNum(bufNumer, bufDenom);
            arr[i][j].print();
            cout << " ";
        }
        cout << endl;
    }
    vector<int> basis;
    int buf;
    for(i = 0; i < sizex; ++i) {
        cout << "basis[" << i << "] = ";
        cin >> buf;
        basis.push_back(buf);
    }
    FracMatrixSymplex matrix(arr, sizex, sizey, basis);
    matrix.printInfo();

    return 0;
}

