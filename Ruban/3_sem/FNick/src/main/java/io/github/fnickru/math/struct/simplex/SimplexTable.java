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
    private int[] rowId;
    private int[] colId;

    SimplexTable(Fraction[][] table) {
        this(table, -1, -1);
    }

    private SimplexTable(Fraction[][] table, int resRow, int resCol) {
        this.table = table.clone();
        for(int i = 0; i < this.table.length; ++i)
            this.table[i] = table[i].clone();
        stateList = new ArrayList<>();

        this.resRow = resRow;
        this.resCol = resCol;

        rowId = new int[table.length - 1];
        colId = new int[table[0].length - 1];
        for (int i = 0; i < colId.length; ++i) {
            colId[i] = i;
        }
        for (int i = 0; i < rowId.length; ++i) {
            rowId[i] = i + table[0].length -1;
        }
    }

    private SimplexTable(Fraction[][] table, int resRow, int resCol, int[] rowId, int[] colId) {
        this.table = table.clone();
        for(int i = 0; i < this.table.length; ++i)
            this.table[i] = table[i].clone();
        stateList = new ArrayList<>();

        this.resRow = resRow;
        this.resCol = resCol;

        this.rowId = Arrays.copyOf(rowId, rowId.length);
        this.colId = Arrays.copyOf(colId, colId.length);
    }

    int rows() {
        return table.length;
    }

    int cols() {
        return table[0].length;
    }

    Fraction getElement(int row, int column) {
        return table[row][column];
    }

    private void switchBasis(int row, int col) {
        rowId[row] += colId[col - 1];
        colId[col - 1] = rowId[row] - colId[col - 1];
        rowId[row] -= colId[col - 1];
    }

    int getResRow() {
        int index = 0;
        for (int i = 1; i < rows() - 1; ++i) {
            if (table[i][0].isNegative() && table[index][0].compareTo(table[i][0]) > 0)
                index = i;
        }
        return table[index][0].isNegative() ? index : -1;
    }

    int getResRow(int resCol) {
        int index = -1;
        Fraction ratio = Fraction.INFINITY;
        for (int i = 0; i < rows() - 1; ++i) {
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
        this.resCol = resCol;
        this.resRow = resRow;

        stateList.add(new SimplexTable(table, resRow, resCol, rowId, colId));

        for (int i = 0; i < rows(); ++i)
            if (i != resRow)
                for (int j = 0; j < cols(); ++j)
                    if (j != resCol)
                        table[i][j] = table[i][j].subtract(
                                table[resRow][j]
                                        .multiply(table[i][resCol])
                                        .divide(table[resRow][resCol])
                        );

        for (int j = 0; j < cols(); ++j)
            if (j != resCol)
                table[resRow][j] = table[resRow][j].divide(table[resRow][resCol]);

        for (int i = 0; i < rows(); ++i)
            if (i != resRow)
                table[i][resCol] = table[i][resCol].divide(table[resRow][resCol].negate());

        table[resRow][resCol] = table[resRow][resCol].invert();
        switchBasis(resRow, resCol);
    }

    List<SimplexTable> getStateList() {
        return stateList;
    }

    int[] getRowId() {
        return rowId;
    }

    public String toString() {
        String string = String.format("%14s ", "B");
        for (int i : colId) {
            string = string.concat(String.format("%10s ", "x" + i));
        }
        string += '\n';
        for (int i = 0; i < rows(); i++) {
            string = string.concat(String.format("%3s ", i < rowId.length ? "x" + rowId[i] : "F"));
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
