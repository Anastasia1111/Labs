#ifndef PLANNINGMATRIX_H
#define PLANNINGMATRIX_H

#include "volumeandcost.h"
#include "container.h"
#include <vector>
#include <utility>
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

    void setPotential();
    bool findMinNegRating(int &x, int &y);
    bool potIsDefined();

    void DFSCircle(int x, int y);
    void DFSInit(int x, int y);
    void DFSEnd();
    bool DFSSearch(int v);

    bool findRight(int origx, int origy, int &resx, int &resy);
    bool findUp(int origx, int origy, int &resx, int &resy);
    bool findLeft(int origx, int origy, int &resx, int &resy);
    bool findDown(int origx, int origy, int &resx, int &resy);

    vector<vector<bool>> mark;
    vector<vector<pair<int, int>>> from;
    vector<vector<VolumeAndCost>> matrix;
    vector<Container> storage;
    vector<Container> consumption;
    vector <Potential> potU;
    vector <Potential> potV;

    vector <int> vertex;
//    0 is white
//    1 is grey
//    2 is black
    vector< vector <int>> refer;
    vector<int> path;

    int xsize, ysize;
    int stx, sty, endx, endy;
};

#endif // PLANNINGMATRIX_H
