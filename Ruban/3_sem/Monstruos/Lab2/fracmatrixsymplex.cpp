#include "fracmatrixsymplex.h"

using namespace std;

FracMatrixSymplex::FracMatrixSymplex(Frac **matrix, int x, int y) : m(matrix), xsize(x), ysize(y)
{
    for(int i = 0; i < xsize; ++i) {
        setBasisInColumn(i, i);
    }
    m[xsize][ysize - 1] = 0.0;
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
    int *baseSnap = new int[xsize];
    for(int i = 0; i < ysize; ++i) {
        for(int j = 0; j < xsize; ++j) {
            if(columnIsBasis(i, j))
                baseSnap[j] = i;
        }
    }
    baseSnapshot.push_back(make_pair(snapshot, baseSnap));
    return true;
}

bool FracMatrixSymplex::columnIsBasis(int col, int row)
{
    for(int i = 0; i < xsize; ++i) {
        if(i == row) { // should be (a == 1)
            if(m[i][col] != 1)
                return false;
        } else {
            if(m[i][col] != 0)
                return false;
        }
    }
    return true;
}

void FracMatrixSymplex::symplexMethod()
{

}

bool FracMatrixSymplex::rebase(int inputColumn, int outputColumn)
{
    int basisRow = -1;
    for(int i = 0; i < xsize; ++i) { // check that output column is basis and that input column wasn't basis before
        if(columnIsBasis(outputColumn, i))
            basisRow = i;
        if(columnIsBasis(inputColumn, i))
            return false;
    }
    if(basisRow == -1) // basisRow is the num of row that is not null in output basis
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

void FracMatrixSymplex::findOptimal(int &row, int &column)
{

}
