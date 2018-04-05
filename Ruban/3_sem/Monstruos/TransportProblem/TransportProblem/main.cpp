#include <iostream>
#include <fstream>

#include "planningmatrix.h"
using namespace std;

int main()
{
    ifstream inp("matrix.txt");
    int xsize, ysize;
    inp >> xsize >> ysize;
    //cout << xsize << " " << ysize << endl;
    vector<vector<VolumeAndCost>> inpM;
    inpM.resize(xsize - 1);
    for(unsigned int i = 0; i < inpM.size(); ++i) {
        inpM[i].resize(ysize - 1);
    }
    vector<Container> inpStore;
    vector<Container> inpCons;

    inpStore.resize(xsize - 1);
    inpCons.resize(ysize - 1);

    //cout << "reading values..." << endl;

    for(int i = 0; i < xsize; ++i) {
        if(i != xsize - 1) {
            //cout << "read " << i << " string..." << endl;
            for(int j = 0; j < ysize; ++j) {
                //cout << "[" << j << "] ";
                if(j != ysize - 1) {
                    inp >> inpM[i][j];
                    //cout << inpM[i][j] << " ";
                } else {
                    inp >> inpStore[i];
                    //cout << inpStore[i] << " ";
                }
            }
            //cout << endl;
        } else {
            //cout << "read " << i << " string (else)..." << endl;
            for(int j = 0; j < ysize - 1; ++j) {
                inp >> inpCons[j];
                //cout << inpCons[j] << " ";
            }
        }
        //cout << endl;
    }

    PlanningMatrix plan(inpM, inpStore, inpCons);
    cout << "NWAngle method:" << endl;
    plan.northWestAngle();
    cout << endl << endl
         << "MinCost method:" << endl;
    plan.minCostMethod();
    return 0;
}
