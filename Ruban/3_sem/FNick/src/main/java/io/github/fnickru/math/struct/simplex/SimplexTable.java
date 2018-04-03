package io.github.fnickru.math.struct.simplex;

import io.github.fnickru.math.struct.Fraction;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class SimplexTable {

    private Fraction[][] table;
    private int resRow;
    private int resCol;
    private List<SimplexTable> stateList;
    private String[] rowId;
    private String[] colId;

    SimplexTable(Fraction[][] table, String[] rowId, String[] colId) {
        this.table = table.clone();
        for(int i = 0; i < this.table.length; ++i)
            this.table[i] = table[i].clone();
        stateList = new ArrayList<>();

        setResElement(-1, -1);
        setId(rowId, colId);
    }

    private SimplexTable(SimplexTable simplexTable) {
        this.table = simplexTable.table.clone();
        for(int i = 0; i < this.table.length; ++i)
            this.table[i] = simplexTable.table[i].clone();
        stateList = new ArrayList<>();

        setResElement(simplexTable.resRow, simplexTable.resCol);
        setId(simplexTable.rowId, simplexTable.colId);
    }

    int rows() {
        return table.length;
    }

    int cols() {
        return table[0].length;
    }

    private void setResElement(int row, int column) {
        resRow = row;
        resCol = column;
    }

    private void setId(String[] rowId, String[] colId) {
        this.rowId = Arrays.copyOf(rowId, rowId.length);
        this.colId = Arrays.copyOf(colId, colId.length);
    }

    Fraction getElement(int row, int column) {
        return table[row][column];
    }

    private void switchBasis(int row, int col) {
        rowId[row] = rowId[row] + colId[col - 1];
        colId[col - 1] = rowId[row].substring(0, (rowId[row].length() - colId[col - 1].length()));
        rowId[row] = rowId[row].substring(colId[col - 1].length());
    }

    int getResRow() {
        int index = 0;
        for (int i = 1; i < rowId.length; ++i) {
            if (table[i][0].isNegative() && table[index][0].compareTo(table[i][0]) > 0)
                index = i;
        }
        return table[index][0].isNegative() ? index : -1;
    }

    int getResRow(int resCol) {
        int index = -1;
        Fraction ratio = Fraction.INFINITY;
        for (int i = 0; i < rowId.length; ++i) {
            if (table[i][0].compareTo(Fraction.ZERO) >= 0
                    && table[i][resCol].compareTo(Fraction.ZERO) > 0
                    && table[i][0].divide(table[i][resCol]).compareTo(ratio) < 0) {
                index = i;
                ratio = table[i][0].divide(table[i][resCol]);
            }
        }
        return index;
    }

    int getResCol(int resRow) {
        int index = 1;
        for (int i = 2; i < cols(); ++i) {
            if (table[resRow][i].isNegative() && table[resRow][index].compareTo(table[resRow][i]) > 0)
                index = i;
        }
        return table[resRow][index].isNegative() ? index : -1;
    }

    void step(int resRow, int resCol) {
        setResElement(resRow, resCol);
        stateList.add(new SimplexTable(this));

        switchBasis(resRow, resCol);

        for (int i = 0; i <= rowId.length; ++i)
            if (i != resRow)
                for (int j = 0; j < cols(); ++j)
                    if (j != resCol)
                        table[i][j] = table[i][j].subtract(
                                table[resRow][j]
                                        .multiply(table[i][resCol])
                                        .divide(table[resRow][resCol])
                        );

        for (int j = 0; j < cols(); ++j) {
            if (j != resCol)
                table[resRow][j] = table[resRow][j].divide(table[resRow][resCol]);
            table[rows() - 1][j] = Fraction.ZERO;
        }

        for (int i = 0; i <= rowId.length; ++i)
            if (i != resRow)
                table[i][resCol] = table[i][resCol].divide(table[resRow][resCol].negate());

        table[resRow][resCol] = table[resRow][resCol].invert();

        for (int i = 0; i < rowId.length; ++i)
            if (rowId[i].startsWith("r"))
                for (int j = 0; j < cols(); ++j)
                    table[rows() - 1][j] = table[rows() - 1][j].subtract(table[i][j]);
    }

    List<SimplexTable> getStateList() {
        return stateList;
    }

    String[] getRowId() {
        return rowId;
    }

    public String toString() {
        String string = String.format("%14s ", "B");
        for (String i : colId) {
            string = string.concat(String.format("%10s ", i));
        }
        string += '\n';
        for (int i = 0; i < rows(); i++) {
            String index = i < rowId.length ? rowId[i] : (i == rowId.length ? "F" : "M");
            string = string.concat(String.format("%3s ", index));
            for (int j = 0; j < cols(); j++) {
                if (i == resRow && j == resCol)
                    string = string.concat(String.format("%10s ","*" + getElement(i, j) + "*"));
                else
                    string = string.concat(String.format("%10s ",getElement(i, j)));
            }
            string = string.concat("\n");
        }

        return string;
    }
}
