#include <iostream>
#include <fstream>
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

    ifstream inp_file("matrix.txt");
    inp_file >> sizex >> sizey;

    //FILE *f = fopen("matrix.txt", "r+");
    //fscanf(f, "%i %i", &sizex, &sizey);

    cout << "sizex = " << sizex << endl
         << "sizey = " << sizey << endl
         << endl;

    cout << "input:";

    //int bufNumer, bufDenom;

    //arr = new Frac *[sizex];
    for(i = 0; i < sizex; ++i) {
        //arr[i] = new Frac [sizey];
        cout << endl;
        for(j = 0; j < sizey; ++j) {
            inp_file >> buff;
            cout << buff << " ";
            task.push_back(buff);

            //arr[i][j].setNewNum(bufNumer, bufDenom);
        }

        //set limitation
        pointFunc.setLine(task);
        task.clear();
        if(i != sizex - 1)
            m.push_back(pointFunc);
    }

    FracMatrixSymplex a(m, pointFunc);
    cout << "through cout: " << endl;
    cout << a;
//    a.symplexMethod();

    return 0;
}

