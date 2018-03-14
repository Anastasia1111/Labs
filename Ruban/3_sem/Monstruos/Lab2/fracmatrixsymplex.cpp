#include "fracmatrixsymplex.h"

using namespace std;

FracMatrixSymplex::FracMatrixSymplex(Frac **matrix, int x, int y, bool isMin) : m(matrix), xsize(x), ysize(y)
{
    setNewSnapshot();
}

void FracMatrixSymplex::rowAdd(int row, Frac *add)
{
    for(int i = 0; i < ysize; ++i) {
        m[row][i] += add[i];
    }
}

void FracMatrixSymplex::rowMulti(int row, Frac mult)
{
    for(int i = 0; i < ysize; ++i)
        m[row][i] *= mult;
}

void FracMatrixSymplex::colMulti(int col, Frac mult)
{
    for(int i = 0; i < xsize; ++i)
        m[i][col] *= mult;
}

bool FracMatrixSymplex::setNewSnapshot()
{
    Frac **snapshot;
    snapshot = new Frac *[xsize + 1];
    for(int i = 0; i < xsize + 1; ++i) {
        snapshot[i] = new Frac[ysize];
        for(int j = 0; j < ysize; ++j) {
            snapshot[i][j] = m[i][j];
        }
    }
    bool res;
    for(int i = 0; i < baseSnapshot.size(); ++i) {
        res = true;
        for(int j = 0; j < xsize + 1; ++j) {
            for(int k = 0; k < ysize; ++k) {
                if(!(snapshot[j][k] == (baseSnapshot[i].first)[j][k])) {
                    res = false; // vector[i] is diff
                    break; // its useless for us now
                }
            }
        }
        if(res == true) // if snapshot is equal vector[i]
            return false;
    }
    //snapshot is original
    int *baseSnap = new int[ysize];
    for(int i = 0; i < ysize; ++i) {
        int b = columnIsBasis(i);
        if(b != -1) {
            baseSnap[i] = b + 1;
        } else {
            baseSnap[i] = 0;
        }
    }
    baseSnapshot.push_back(make_pair(snapshot, baseSnap));
//    cout << "SNAPSHOT: <";
//    for(int i = 0; i < ysize; ++i) {
//        cout << baseSnapshot[baseSnapshot.size() - 1].second[i] << " ";
//    }
//    cout << "\b>" << endl;

//    for(int i = 0; i <= xsize; ++i) {
//        for(int j = 0; j < ysize; ++j) {
//            baseSnapshot[baseSnapshot.size() - 1].first[i][j].print();
//            cout << " ";
//        }
//        cout << endl;
//    }
    return true;
}

int FracMatrixSymplex::columnIsBasis(int col)
{
    int basisRow = -1;
    for(int i = 0; i < xsize; ++i) {
        if(m[i][col] == 1) {
            if(basisRow == -1) {
                basisRow = i;
            } else {
                return -1;
            }
        } else {
            if(m[i][col] != 0)
                return -1;
        }
    }
    return basisRow;
}

void FracMatrixSymplex::symplexMethod()
{
    int lRow, lCol;
    printMatrix();
    cout << endl << endl;
    while(!isOptimal()) {
        findLeadForBasisPlan(lRow, lCol);
        rectangleMethod(lRow, lCol);
        setNewSnapshot();
        printMatrix();
        cout << endl << "THAT'S ALL, FOLKS!!!" << endl;
    }
}

bool FracMatrixSymplex::rebase(int inputColumn, int outputColumn)
{
    int basisRow = -1;
    // check that output column is basis and that input column wasn't basis before
    basisRow = columnIsBasis(outputColumn);
    if(basisRow == -1 || columnIsBasis(inputColumn) != -1) // basisRow is the num of row that is not null in output basis
        return false;

    setBasisInColumn(inputColumn, basisRow);
    setNewSnapshot();
    return true;
}

void FracMatrixSymplex::printMatrix()
{
    cout << "Matrix:" << endl;
    for(int i = 0; i < xsize; ++i) {
        for(int j = 0; j < ysize; ++j) {
            m[i][j].print();
            cout << " ";
        }
        cout << endl;
    }

    cout << "Target function:" << endl;
    for(int j = 0; j < ysize - 1; ++j) {
        (m[xsize][j] * -1).print();
        cout << "*x[" << j + 1 << "] + ";
    }
    cout << "\b\b";
    cout << "= ";
    m[xsize][ysize - 1].print();
    cout << endl;
}

void FracMatrixSymplex::setBasis(int *columns)
{
    for(int i = 0; i < xsize; ++i) {
        setBasisInColumn(columns[i], i);
    }
}

bool FracMatrixSymplex::basisWasBefore(int *columns)
{
    bool res;
    for(int i = 0; i < baseSnapshot.size(); ++i) { // for every snapshot...
        res = true;
        for(int j = 0; j < xsize; ++j) { // if input basis was exist, res will be true
            if(columns[j] != (baseSnapshot[i].second)[j]) {
                res = false;
                break;
            }
        }
        if(res)
            return res;
    }
    return false;
}

void FracMatrixSymplex::setBasisInColumn(int column, int row)
{
    Frac *bufRow = new Frac[ysize]; // buffer for making '0'
    rowMulti(row, m[row][column].invert()); // making '1' in m[row][column]
    for(int i = 0; i < xsize + 1; ++i) { // for every row

        if(i != row) {
            for(int j = 0; j < ysize; ++j) { // "(i) - (row) * m[i][column]"
                bufRow[j] = m[row][j] * m[i][column] * -1.0;
            }
            rowAdd(i, bufRow);
        }
    }
    delete bufRow;
}

void FracMatrixSymplex::findOptForBasisPlan(int &optimalRow, int &optimalCol)
{
    Frac min = m[0][ysize - 1];
    for(int i = 1; i <= xsize; ++i) {
        if(m[i][ysize - 1] < 0.0)
            if(m[i][ysize - 1] < min) {
                min = m[i][ysize - 1];
                optimalRow = i;
            }
    }

    optimalCol = 0;
    min = m[optimalRow][0];
    for(int j = 1; j < ysize; ++j) {
        if(m[optimalRow][j] < min) {
            min = m[optimalRow][j];
            optimalCol = j;
        }
    }
    if(min > 0.0 && min == 0.0) {
        cout << "CRITICAL ERROR! WTF IS GOING ON!" << endl;
    }


}

void FracMatrixSymplex::findLeadForBasisPlan(int &leadRow, int &leadCol)
{
    Frac min = m[xsize][0];
    for(int i = 1; i < ysize - 1; ++i) {
        if(m[xsize][i] < min) {
            min = m[xsize][i];
            leadCol = i;
        }
    }

    leadRow = 0;
    Frac k = m[0][ysize - 1] / m[0][leadCol];
    for(int i = 0; i < xsize; ++i) {
        Frac kbuf = m[i][ysize - 1] / m[i][leadCol];
        if(kbuf < k && m[i][leadCol] > 0) {
            leadRow = i;
            k = kbuf;
        }
    }
//    cout << "Lead for basis plan:" << leadRow << " " << leadCol << endl;
}

void FracMatrixSymplex::rectangleMethod(int optRow, int optColumn)
{
//    cout << "Multiplcation: (" << optRow << ") * ";
//    m[optRow][optColumn].invert().print();
//    cout << endl;
    rowMulti(optRow, m[optRow][optColumn].invert());
    for(int i = 0; i < xsize + 1; ++i) {
        if(i != optRow)
            for(int j = 0; j < ysize; ++j) {
                if(j != optColumn) {
                    m[i][j] = m[i][j] - (m[i][optColumn] * m[optRow][j] / m[optRow][optColumn]);
                }
            }
    }
    for(int i = 0; i < xsize + 1; ++i)
        if(i != optRow)
            m[i][optColumn] = 0;
}

bool FracMatrixSymplex::isOptimal()
{
//    cout << "isOptimal:" << endl;
    for(int i = 0; i < ysize; ++i) {
//        m[xsize][i].print();
//        cout << " ";
        if(m[xsize][i] < 0.0) {
//            cout << endl;
            return false;
        }
    }
//    cout << endl;
    return true;
}
