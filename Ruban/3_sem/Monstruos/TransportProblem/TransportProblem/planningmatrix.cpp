#include "planningmatrix.h"

PlanningMatrix::PlanningMatrix(vector<vector<VolumeAndCost> > m, vector<Container> store, vector<Container> cons) :
    matrix(m), storage(store), consumption(cons)
{

    //resizing vectores
    if(matrix.size() < storage.size())
        matrix.resize(storage.size());
    else
        storage.resize(matrix.size());

    for(unsigned int i = 0; i < matrix.size(); ++i) {
        if(matrix[i].size() < consumption.size())
            for(unsigned int i = 0; i < matrix.size(); ++i)
                matrix[i].resize(consumption.size());
        else
            consumption.resize(matrix[i].size());
    }

    xsize = matrix.size();
    ysize = matrix[0].size();

    potU.resize(xsize);
    potV.resize(ysize);
}

int PlanningMatrix::planCost()
{
    int z = 0;
    for(int i = 0; i < xsize; ++i) {
        for(unsigned int j = 0; j < matrix[i].size(); ++j) {
            z += matrix[i][j].fullCost();
        }
    }
    return z;
}

bool PlanningMatrix::checkLimit()
{
    int buffer;
    for(int i = 0; i < xsize; ++i) {
        buffer = 0;
        for(int j = 0; j < ysize; ++j) {
            buffer += matrix[i][j].getV();
        }
        if(buffer != storage[i].getSize()) {
            //cout << "Storage[" << i << "]: " << buffer << " != " << storage[i].getSize() << endl;
            return false;
        }
    }

    for(int j = 0; j < ysize; ++j) {
        buffer = 0;
        for(int i = 0; i < xsize; ++i) {
            buffer += matrix[i][j].getV();
        }
        if(buffer != consumption[j].getSize()) {
            //cout << "Consumption[" << j << "]: " << buffer << " != " << consumption[j].getSize() << endl;
            return false;
        }
    }

    //cout << "Limit is \'true\'" << endl;
    return true;
}

bool PlanningMatrix::isCloseSystem()
{
    int c = 0, s = 0;
    for(unsigned int i = 0; i < storage.size(); ++i)
        s += storage[i];

    for(unsigned int i = 0; i < consumption.size(); ++i)
        s += consumption[i];
    if(c == s) {
        return true;
    } else {
        printError("system is not close");
        return false;
    }
}

ostream &operator<<(ostream &str, const PlanningMatrix &outM)
{
    str << "[   u\\v   ] ";
    for(int i = 0; i < outM.ysize; ++i)
        str << "[" << outM.potV[i] << "] ";
    str << endl;
    for(int i = 0; i < outM.xsize + 1; ++i) {
        if(i != outM.xsize) {
            str << "[" << outM.potU[i] << "] ";
            for(unsigned int j = 0; j < outM.matrix[i].size(); ++j) {
                str << outM.matrix[i][j] << " ";
            }
            str << outM.storage[i] << endl;
        } else {
            str << "            ";
            for(unsigned int j = 0; j < outM.consumption.size(); ++j) {
                str << outM.consumption[j] << " ";
            }
        }
    }
    return str;
}

void PlanningMatrix::printError(string error)
{
    cout << "Error: " << error << "." << endl;
}

void PlanningMatrix::setConsEmpty()
{
    for(unsigned int iterc = 0; iterc < consumption.size(); ++iterc)
        consumption[iterc].take(consumption[iterc].getStore());
}

void PlanningMatrix::setStorFull()
{
    for(unsigned int iters = 0; iters < storage.size(); ++iters)
        storage[iters].put(storage[iters].getSize());
}

void PlanningMatrix::clearMatrix()
{
    for(int i = 0; i < xsize; ++i) {
        for(unsigned int j = 0; j < matrix[i].size(); ++j) {
            matrix[i][j].setV(0);
        }
    }
}

void PlanningMatrix::transfering(int from, int to)
{
    int buff, buff2;
    buff = storage[from].take(storage[from].getSize());
    cout << "take " << buff << " from A[" << from << "]..." << endl;

    if(buff > 0) { // some from storage put into consumption
        buff2 = consumption[to].put(buff);
        cout << "put into B[" << to <<  "],remained " << buff2 << "..." << endl;
        matrix[from][to].setV(buff - buff2);
        if(buff2 > 0) // we have remainder -> return into storage
            storage[from].put(buff2);
    }
}

void PlanningMatrix::findMinCost(vector<int> delRows, vector<int> delCols, int &x, int &y)
{
    int min = 100000000;
    for(int i = 0; i < xsize; ++i) {
        if(haveElem(delRows, i))
            continue;
        for(unsigned int j = 0; j < matrix[i].size(); ++j) {
            if(haveElem(delCols, j))
                continue;
            if(matrix[i][j].getC() < min) {
                min = matrix[i][j].getC();
                x = i;
                y = j;
            }
        }
    }
}

bool PlanningMatrix::haveElem(vector<int> vec, int a)
{
    bool ret = false;
    for(unsigned int i = 0; i < vec.size(); ++i)
        if(vec[i] == a) {
            ret = true;
            break;
        }
    return ret;
}

void PlanningMatrix::checkMinsInRow(int row, vector<int> &checkRow)
{

    int min = matrix[row][0].getC();
    for(unsigned int j = 1; j < matrix[row].size(); ++j) {
        if(min > matrix[row][j].getC()) {
            checkRow.clear();
            checkRow.push_back(j);
        }
        if(min == matrix[row][j].getC())
            checkRow.push_back(j);
    }
}

void PlanningMatrix::checkMinsInCol(int col, vector<int> &checkCol)
{
    int min = matrix[0][col].getC();
    for(int i = 1; i < xsize; ++i) {
        if(min > matrix[i][col].getC()) {
            checkCol.clear();
            checkCol.push_back(i);
        }
        if(min == matrix[i][col].getC())
            checkCol.push_back(i);
    }
}

bool PlanningMatrix::potIsDefined()
{
    for(int i = 0; i < xsize; ++i) {
        if(!potU[i].defined())
            return false;
    }
    for(int i = 0; i < ysize; ++i) {
        if(!potV[i].defined())
            return false;
    }
    return true;
}

void PlanningMatrix::DFSCircle(int xstart, int ystart)
{
    DFSInit();
    DFS();
    DFSFree();
}

void PlanningMatrix::DFSInit()
{
    mark.resize(xsize);
    for(int i = 0; i < xsize; ++i) {
        mark[i].resize(ysize, false);
    }
    from.resize(xsize);
    for(int i = 0; i < xsize; ++i) {
        from[i].resize(ysize, make_pair(-1, -1));
    }
}

void PlanningMatrix::DFS(int x, int y, int xfr, int yfr, int xfin, int yfin)
{
    if(mark[x][y])
        return;

    mark[x][y] = true;
    from[x][y] = make_pair(xfr, yfr);
    if(x == xfin && y == yfin)

}

void PlanningMatrix::DFSFree()
{
    mark.clear();
    from.clear();
}

void PlanningMatrix::northWestAngle()
{
    // make consumption empty
    // cout << endl << "NWAngle(), emptying consumption:" << endl;
    setConsEmpty();
    setStorFull();
    clearMatrix();
    //cout << endl << *this << endl;

    int iters = 0;
    for(unsigned int iterc = 0; iterc < consumption.size(); ++iterc) { // filling consumption

        cout << "Filling B[" << iterc<< "] consumption" << endl;

        while(!consumption[iterc].isFull()) {
            transfering(iters, iterc);
            if(storage[iters].isEmpty())
                iters++;

            cout << *this << endl << endl;
        }
    }

    cout << endl << "Z = " << planCost() << endl;
}

void PlanningMatrix::minCostMethod()
{
    vector<int> deletedRow;
    vector<int> deletedCol;

    setConsEmpty();
    setStorFull();
    clearMatrix();

    int x, y;

    while(!checkLimit()) {
        findMinCost(deletedRow, deletedCol, x, y);
        transfering(x, y);
        if(storage[x].isEmpty())
            deletedRow.push_back(x);
        if(consumption[y].isFull())
            deletedCol.push_back(y);
        cout << *this << endl << endl;
    }

    cout << endl << "Z = " << planCost() << endl;
}

void PlanningMatrix::doublePrefMethod()
{
//    setConsEmpty();
//    setStorFull();
//    clearMatrix();

//    vector<vector<int>> checkCol;
//    vector<vector<int>> checkRow;

//    checkCol.resize(xsize);
//    checkRow.resize(ysize);

//    for(int i = 0; i < xsize; ++i)
//        checkMinsInRow(i, checkRow[i]);
//    for(int j = 0; j < ysize; ++j)
//        checkMinsInCol(j, checkCol[j]);

//    while(!checkLimit()) {

    //    }
}

void PlanningMatrix::potentialMethod()
{
    potU[0].setValue(0);

    while(!potIsDefined()) {
        for(int i = 0; i < xsize; ++i) { // find C[i]
            if(potU[i].defined()) {
                cout << "Found u[" << i << "]" << endl;
                for(int j = 0; j < ysize; ++j) { // calc all what we can
                    if(matrix[i][j].isWorking() && !potV[j].defined())
                        potV[j].setValue(matrix[i][j].getC() - potU[i].getValue()); // C[i][j] - U[i] = V[j]
                }
            }
        }

        for(int j = 0; j < ysize; ++j) {
            if(potV[j].defined()) { // find V[j]
                cout << "Found v[" << j << "]" << endl;
                for(int i = 0; i < xsize; ++i) { // calc all what we can
                    if(matrix[i][j].isWorking() && !potU[i].defined())
                        potU[i].setValue(matrix[i][j].getC() - potV[j].getValue()); // C[i][j] - V[j] = U[i]
                }
            }
        }
    }

    cout << "Defined potential" << endl;
    cout << *this;
}
