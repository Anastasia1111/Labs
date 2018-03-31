#include <iostream>
#include <cstdlib>
#include "fracmatrixsymplex.h"
#include "matrixlimitation.h"

using namespace std;


Frac **arr;
int sizex, sizey;

//matrix[sizex][sizey] and target_function[sizey]
int main()
{
    int i, j;

    vector<MatrixLimitation> m;
    vector<Frac> task;
    MatrixLimitation pointFunc;
    Frac buff;

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
            buff.setNewNum(bufNumer, bufDenom);
            task.push_back(buff);
        }
        pointFunc.setLine(task);
        task.clear();
        if(i != sizex - 1)
            m.push_back(pointFunc);
    }


    FracMatrixSymplex a(m, pointFunc);
//    a.symplexMethod();

    return 0;
}

