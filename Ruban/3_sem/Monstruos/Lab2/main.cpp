#include <iostream>
#include <cstdlib>
#include "frac.h"

using namespace std;


Frac **arr;
int sizex, sizey;

void print_arr();
void rebaseGauss(int *basis);


//matrix[sizex][sizey]
int main()
{
    int i, j;
    int *basis;

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
    basis = new int[sizex];
    for(i = 0; i < sizex; ++i) {
        cout << "basis[" << i << "] = ";
        cin >> basis[i];
    }
    rebaseGauss(basis);
    cout << "Result:" << endl;
    print_arr();

    return 0;
}

void rebaseGauss(int *basis)
{
    int i, j, k;
    Frac q;
    for(i = 0; i < sizex; ++i)
    {
        Frac buf = arr[i][basis[i]];
        if(arr[i][basis[i]] == 0) {
            cout << "Cannot make basis(zero);" << endl;
            return;
        }
        for(j = 0; j < sizey; ++j)
            arr[i][j] /= buf;

        print_arr();
        for(j = 0; j < sizex; ++j)
        {
            if(j == i) continue;
            q = arr[j][basis[i]];

            for(k = 0; k < sizey; ++k)
                arr[j][k] -= arr[i][k] * q;
        }
        print_arr();
    }
    return;
}

void print_arr() {
    for(int k = 0; k < sizex; ++k)
    {
        for(int l = 0; l < sizey; ++l) {
            arr[k][l].print();
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}
