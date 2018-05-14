#ifndef PLANNINGMATRIX_H
#define PLANNINGMATRIX_H

#include "volumeandcost.h"
#include "container.h"
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <list>
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

    list <pair<int, int>> DFSH(pair<int, int> start,
                                pair<int, int> finish,
                                pair<int, int> previous,
                                list<pair<int, int> > cycle);
    list <pair<int, int>> DFSV(pair<int, int> start,
                                pair<int, int> finish,
                                pair<int, int> previous,
                                list<pair<int, int> > cycle);

    list <pair<int, int>> findCycle(int x, int y);
    void remakeCycle(int stx, int sty);

    list <pair<int, int>> mainCycle;

    vector<vector<VolumeAndCost>> matrix;
    vector<Container> storage;
    vector<Container> consumption;
    vector <Potential> potU;
    vector <Potential> potV;

    int xsize, ysize;
};

#endif // PLANNINGMATRIX_H
