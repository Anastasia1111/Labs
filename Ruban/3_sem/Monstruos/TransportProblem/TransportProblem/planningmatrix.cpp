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
//            cout << "Storage[" << i << "]: " << buffer << " != " << storage[i].getSize() << endl;
            return false;
        }
    }

    for(int j = 0; j < ysize; ++j) {
        buffer = 0;
        for(int i = 0; i < xsize; ++i) {
            buffer += matrix[i][j].getV();
        }
        if(buffer != consumption[j].getSize()) {
//            cout << "Consumption[" << j << "]: " << buffer << " != " << consumption[j].getSize() << endl;
            return false;
        }
    }

//    cout << "Limit is \'true\'" << endl;
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
            matrix[i][j].setWork(false);
        }
    }
}

void PlanningMatrix::transfering(int from, int to)
{
    int buff, buff2;
    buff = storage[from].take(storage[from].getSize());
    cout << "take " << buff << " from A[" << from << "]..." << endl;

    // some from storage put into consumption
    buff2 = consumption[to].put(buff);
    cout << "put into B[" << to <<  "],remained " << buff2 << "..." << endl;
    matrix[from][to].setV(buff - buff2);
    if(buff2 > 0) // we have remainder -> return into storage
        storage[from].put(buff2);
}

void PlanningMatrix::findMinCost(vector<int> delRows, vector<int> delCols, int &x, int &y)
{
    int min = 100000000;
    for(int i = 0; i < xsize; ++i) {
        if(haveElem(delRows, i)) // filled before
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

void PlanningMatrix::setPotential()
{
    for(int i = 0; i < xsize; ++i)
        potU[i].setSet(false);
    for(int i = 0; i < ysize; ++i)
        potV[i].setSet(false);

    potU[0].setValue(0);

    while(!potIsDefined()) {
        for(int i = 0; i < xsize; ++i) { // find C[i]
            if(potU[i].defined()) {
//                cout << "Found u[" << i << "]" << endl;
                for(int j = 0; j < ysize; ++j) { // calc all what we can
                    if(matrix[i][j].isWorking() && !potV[j].defined())
                        potV[j].setValue(matrix[i][j].getC() - potU[i].getValue()); // C[i][j] - U[i] = V[j]
                }
            }
        }

        for(int j = 0; j < ysize; ++j) {
            if(potV[j].defined()) { // find V[j]
//                cout << "Found v[" << j << "]" << endl;
                for(int i = 0; i < xsize; ++i) { // calc all what we can
                    if(matrix[i][j].isWorking() && !potU[i].defined())
                        potU[i].setValue(matrix[i][j].getC() - potV[j].getValue()); // C[i][j] - V[j] = U[i]
                }
            }
        }
    }
}

bool PlanningMatrix::findMinNegRating(int &x, int &y)
{
    int min = 999999;
    int buf;
    for(int i = 0; i < xsize; ++i) {
        for(int j = 0; j < ysize; ++j) {
            if(!matrix[i][j].isWorking()) {
                buf = matrix[i][j].getC() - potU[i].getValue() - potV[j].getValue();
                if(buf < min) {
                    min = buf;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return min < 0 ? true : false;
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

list<pair<int, int> > PlanningMatrix::DFSH(pair<int, int> start, pair<int, int> finish,
                                            pair<int, int> previous, list<pair<int, int> > cycle)
{
    list <pair<int, int> > path = cycle;
//    cout << "start: (" << start.first<< "," << start.second << ") ";
//    cout << "finish: (" << finish.first << "," << finish.second << ") " << endl;
//    cout << "previous: (" << previous.first << "," << previous.second << ") ";
//    cout << endl;
    if(!(start.first == finish.first && start.second == finish.second) || previous.first < 0 || previous.second < 0) {
        list <pair<int, int> > neighbours;

        for (int j = 0; j < ysize; ++j) {

            bool inCycle = false;
            if (j != start.second && matrix[start.first][j].isWorking()) {
                for(list<pair<int, int>>::iterator it = cycle.begin(); it != cycle.end(); ++it) {
                    if(it->first == start.first && it->second == j) {
                        inCycle = true;
                        break;
                    }
                }
                if(!inCycle)
                    neighbours.push_back(make_pair(start.first, j));
            }
        }

        neighbours.remove(previous);

//        cout << "neighbours: ";
//        for(list<pair<int, int>>::iterator i = neighbours.begin(); i != neighbours.end(); ++i) {
//            cout << "(" << i->first << "," << i->second << ") ";
//        }
//        cout << endl;

        for(list<pair<int, int>>::iterator it = neighbours.begin(); it != neighbours.end(); ++it) {
            list<pair<int, int>> newPath = cycle;
            pair<int, int> neighbour = make_pair(it->first, it->second);
            newPath.push_back(neighbour);

//            cout << "DFSH:" << endl;
//            cout << "neighbour: (" << neighbour.first << "," << neighbour.second << ")" << endl;
//            cout << "finish: (" << finish.first << "," << finish.second << ")" << endl;
//            cout << "start: (" << start.first << "," << start.second << ")" << endl;
//            cout << "DFSH newPath (before):";
//            for(list<pair<int, int>>::iterator i = newPath.begin(); i != newPath.end(); ++i) {
//                cout << "(" << i->first << "," << i->second << ") ";
//            }
//            cout << endl;

            newPath = DFSV(neighbour, finish, start, newPath);

//            cout << "DFSH newPath (after):";
//            for(list<pair<int, int>>::iterator i = newPath.begin(); i != newPath.end(); ++i) {
//                cout << "(" << i->first << "," << i->second << ") ";
//            }
//            cout << endl;

            if(newPath.back().first == finish.first && newPath.back().second == finish.second) {
                path = newPath;
                break;
            }
        }
    }

    return path;
}

list<pair<int, int> > PlanningMatrix::DFSV(pair<int, int> start,
                                           pair<int, int> finish,
                                           pair<int, int> previous,
                                           list<pair<int, int> > cycle)
{
    list <pair<int, int> > path = cycle;
//    cout << "DFSV: ";
//    cout << "start: (" << start.first<< "," << start.second << ") ";
//    cout << "finish: (" << finish.first << "," << finish.second << ") " << endl;
//    cout << "previous: (" << previous.first << "," << previous.second << ") ";
//    cout << endl;
    if(!(start.first == finish.first && start.second == finish.second) || previous.first < 0 || previous.second < 0) {
        list <pair<int, int> > neighbours;

        for (int i = 0; i < xsize; ++i) {
            if (i != start.first && matrix[i][start.second].isWorking()) {
                bool inCycle = false;
                for(list<pair<int, int>>::iterator it = cycle.begin(); it != cycle.end(); ++it) {
                    if(it->second == start.second && it->first == i) {
                        inCycle = true;
                        break;
                    }
                }
                if(!inCycle)
                    neighbours.push_back(make_pair(i, start.second));
            }
        }

        neighbours.remove(previous);

//        cout << "neighbours: ";
//        for(list<pair<int, int>>::iterator i = neighbours.begin(); i != neighbours.end(); ++i) {
//            cout << "(" << i->first << "," << i->second << ") ";
//        }
//        cout << endl;

        for(list<pair<int, int>>::iterator it = neighbours.begin(); it != neighbours.end(); ++it) {
            list<pair<int, int>> newPath = cycle;
            pair<int, int> neighbour = make_pair(it->first, it->second);
            newPath.push_back(neighbour);

//            cout << "DFSV:" << endl;
//            cout << "neighbour: (" << neighbour.first << "," << neighbour.second << ")" << endl;
//            cout << "finish: (" << finish.first << "," << finish.second << ")" << endl;
//            cout << "start: (" << start.first << "," << start.second << ")" << endl;
//            cout << "DFSV newPath (before):";
//            for(list<pair<int, int>>::iterator i = newPath.begin(); i != newPath.end(); ++i) {
//                cout << "(" << i->first << "," << i->second << ") ";
//            }/*
//            cout << endl;*/

            newPath = DFSH(neighbour, finish, start, newPath);

//            cout << "DFSV newPath (after):";
//            for(list<pair<int, int>>::iterator i = newPath.begin(); i != newPath.end(); ++i) {
//                cout << "(" << i->first << "," << i->second << ") ";
//            }
//            cout << endl;

            if(newPath.back().first == finish.first && newPath.back().second == finish.second) {
                path = newPath;
                break;
            }
        }
    }

    return path;
}

list<pair<int, int> > PlanningMatrix::findCycle(int x, int y)
{
    matrix[x][y].setV(0);
    mainCycle.clear();
    pair<int, int> start = make_pair(x, y);
    cout << "Start/finish: (" << x << "," << y << ")" << endl;
    cout << "Finding..." << endl;
    mainCycle = DFSH(start, start, make_pair(-1, -1), mainCycle);
    mainCycle.pop_back();

    return mainCycle;
}

void PlanningMatrix::remakeCycle(int stx, int sty)
{
    pair<int, int> min = make_pair(-1, -1);
    int minV = 9999999;
    bool parity = false; // 0 is start element (enpty field), so substract from 1, 3, 5 & addition for 2, 4, 6...
    for(list<pair<int, int>>::iterator k = mainCycle.begin(); k != mainCycle.end(); k++) {
        if(!parity) {
            int x = k->first;
            int y = k->second;

            if(minV > matrix[x][y].getV()) {
                min = make_pair(x, y);
                minV = matrix[x][y].getV();
            }
        }
        parity = !parity;
    }

    parity = false;
    for(list<pair<int, int>>::iterator k = mainCycle.begin(); k != mainCycle.end(); k++) {
        if(!parity) {
            int x = k->first;
            int y = k->second;
            int sub = matrix[x][y].getV() - minV;

            (sub > 0) ? matrix[x][y].setV(sub) : matrix[x][y].setWork(false);
        }
        parity = !parity;
    }

    parity = false;
    for(list<pair<int, int>>::iterator k = mainCycle.begin(); k != mainCycle.end(); k++) {
        if(parity) {
            int x = k->first;
            int y = k->second;
            int add = matrix[x][y].getV() + minV;

            matrix[x][y].setV(add);
        }
        parity = !parity;
    }

    matrix[stx][sty].setV(minV);
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
            if(storage[iters].isEmpty()) {
                iters++;
            }

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
    cout << *this << endl;

    int x, y;

    while(!checkLimit()) {
        cout << "Limit checked..." << endl;
        findMinCost(deletedRow, deletedCol, x, y);
        cout << "Transfer from " << x
             << " to " << y << endl;
        transfering(x, y);
        if(storage[x].isEmpty())
            deletedRow.push_back(x);
        if(consumption[y].isFull() && !storage[x].isEmpty())
            deletedCol.push_back(y);
        cout << *this << endl << endl;
    }

    cout << endl << "Z = " << planCost() << endl;
}

void PlanningMatrix::potentialMethod()
{
    int x, y;
    setPotential();
    while(findMinNegRating(x, y)) {
        cout << *this << endl << endl;
        cout << "Setting potential..." << endl;
        setPotential();
        mainCycle = findCycle(x, y);
        cout << "Cycle:" << endl << "(" << x << "," << y << ")" << endl;
        for(list<pair<int, int>>::iterator k = mainCycle.begin(); k != mainCycle.end(); k++) {
            cout << "(" << k->first << "," << k->second << ")" << endl;
        }
        cout << "(" << x << "," << y << ")" << endl;
        remakeCycle(x, y);
    }
    cout << "RESULT:" << endl << *this << endl << endl;
}
