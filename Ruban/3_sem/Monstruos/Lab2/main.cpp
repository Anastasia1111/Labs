#include <iostream>
#include <cstdlib>
#include "fracmatrixsymplex.h"


using namespace std;


Frac **arr;
int sizex, sizey;

//matrix[sizex][sizey] and target_function[sizey]
int main()
{
    int i, j;

    FILE *f = fopen("matrix.txt", "r+");
    fscanf(f, "%i %i", &sizex, &sizey);
    cout << "sizex = " << sizex << endl
         << "sizey = " << sizey << endl
         << endl;
    int bufNumer, bufDenom;
    arr = new Frac *[sizex + 1];
    for(i = 0; i < sizex + 1; ++i) {
        arr[i] = new Frac [sizey];
        for(j = 0; j < sizey; ++j) {
            fscanf(f, "%i/%i", &bufNumer, &bufDenom);
            arr[i][j].setNewNum(bufNumer, bufDenom);
        }
    }
    FracMatrixSymplex a(arr, sizex, sizey);
    a.symplexMethod();

    return 0;
}

