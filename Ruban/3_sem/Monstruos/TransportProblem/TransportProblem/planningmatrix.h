#ifndef PLANNINGMATRIX_H
#define PLANNINGMATRIX_H

#include "volumeandcost.h"
#include "container.h"
#include <vector>
#include <string>
#include <iostream>
#include "potential.h"

using namespace std;


class PlanningMatrix
{
public:
    PlanningMatrix(vector<vector<VolumeAndCost>> m, vector<Container> store, vector<Container> cons);
    int planCost();
    bool checkLimit();
    bool isCloseSystem();
    void northWestAngle();
    void minCostMethod();
    void doublePrefMethod();
    void potentialMethod();

    friend std::ostream &operator<<(std::ostream &str, const PlanningMatrix& outM);

private:

    void printError(string error); // deprecated?

    void setConsEmpty();
    void setStorFull();
    void clearMatrix();

    void transfering(int from, int to);

    void findMinCost(vector<int> delRows, vector<int> delCols, int &x, int &y);
    bool haveElem(vector<int> vec, int a);

    void checkMinsInRow(int row, vector<int> &checkRow);
    void checkMinsInCol(int col, vector<int> &checkCol);

    bool potIsDefined();

    vector<vector<VolumeAndCost>> matrix;
    vector<Container> storage;
    vector<Container> consumption;
    vector <Potential> potU;
    vector <Potential> potV;
    int xsize, ysize;
};

#endif // PLANNINGMATRIX_H
