#include <iostream>
#include <fstream>

#include "planningmatrix.h"
using namespace std;

int main()
{
    ifstream inp("matrix.txt");
    int xsize, ysize;
    inp >> xsize >> ysize;
    vector<vector<VolumeAndCost>> inpM;
    inpM.resize(xsize - 1);
    for(unsigned int i = 0; i < inpM.size(); ++i) {
        inpM[i].resize(ysize - 1);
    }
    vector<Container> inpStore;
    vector<Container> inpCons;

    inpStore.resize(xsize - 1);
    inpCons.resize(ysize - 1);

    for(int i = 0; i < xsize; ++i) {
        if(i != xsize - 1) {
            for(int j = 0; j < ysize; ++j) {
                if(j != ysize - 1) {
                    inp >> inpM[i][j];
                } else {
                    inp >> inpStore[i];
                }
            }
        } else {
            for(int j = 0; j < ysize - 1; ++j) {
                inp >> inpCons[j];
            }
        }
    }

    PlanningMatrix plan(inpM, inpStore, inpCons);
    cout << "NWAngle method:" << endl;
    plan.northWestAngle();
    cout << endl << endl
         << "MinCost method:" << endl;
    plan.minCostMethod();

//    plan.potentialMethod();
//    cout << endl;
    return 0;
}
