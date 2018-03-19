package io.github.fnickru.math.struct;

import io.github.fnickru.math.util.FileWorker;

import java.util.ArrayList;
import java.util.List;

public class Simplex {
    private CostFunction costFunction;
    private Limitation[] limitations;
    private SimplexTable simplexTable;
    private int[] rowId;
    private int[] colId;
    private boolean isFirstStepDone;

    public Simplex(CostFunction function, Limitation... limitations) {
        this.costFunction = function;
        this.limitations = limitations;
        setup();
    }

    private void setup() {
        int varnum = costFunction.getLength();
        for (Limitation limitation : limitations)
            varnum = Math.max(limitation.getLength(), varnum);
        int rows = limitations.length + 1;
        int cols = varnum + 1;
        Fraction [][] table = new Fraction[rows][cols];

        table[rows - 1][0] = Fraction.ZERO;

        for (int v = 0; v < varnum; ++v) {
            if (costFunction.shouldBeMinimized())
                table[rows - 1][v + 1] = costFunction.getCoef(v);
            else
                table[rows - 1][v + 1] = costFunction.getCoef(v).negate();
        }

        int index = 0;
        for (Limitation l : limitations) {
            for (int v = 0; v < varnum; ++v) {
                if (l.getSign() == Limitation.LimitationSign.GE)
                    table[index][v + 1] = l.getCoef(v).negate();
                else
                    table[index][v + 1] = l.getCoef(v);
            }
            ++index;
        }

        index = 0;
        for (Limitation l : limitations) {
            if (l.getSign() == Limitation.LimitationSign.GE)
                table[index][0] = l.getFreeTerm().negate();
            else
                table[index][0] = l.getFreeTerm();
            ++index;
        }

        simplexTable = new SimplexTable(table);

        rowId = new int[simplexTable.rows() - 1];
        colId = new int[simplexTable.cols() - 1];
        isFirstStepDone = false;
    }

    public void solve() {

    }

    @Override
    public String toString() {
        String str = "Function:\n" + costFunction + "\nLimitations:\n";
        for (Limitation limitation : limitations) {
            str = str.concat(limitation + "\n");
        }
        return str;
    }

    public static void main(String[] args) {
        Simplex simplex = FileWorker.readSimplex("./src/main/resources/simplex.txt");
        System.out.println(simplex);
    }

    private class SimplexTable {

        private Fraction[][] table;
        private List<SimplexTable> stateList;

        private SimplexTable(Fraction[][] table) {
            this.table = table;
            stateList = new ArrayList<>();
        }

        private int rows() {
            return table.length;
        }

        private int cols() {
            return table[0].length;
        }

        private Fraction getElement(int row, int column) {
            return table[row][column];
        }

        private int findResCol() {
            for (int i = 1; i < cols(); ++i)
                if (table[rows() - 1][i].isNegative())
                    return i;
            return 0;
        }

        private int findResRow(int col) {
            for (int i = 0; i < rows() - 1; ++i) {
                if (!table[i][col].isNegative())
                    return i;
            }
            return -1;
        }

        private void step(int resRow, int resCol) {
            stateList.add(new SimplexTable(table));

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
        }

        private List<SimplexTable> getStateList() {
            return stateList;
        }

        public String toString() {
            String string = "";

            for (int i = 0; i < rows(); i++) {
                for (int j = 0; j < cols(); j++) {
                    int resCol = findResCol();
                    int resRow = findResRow(resCol);

                    if (i == resRow && j == resCol)
                        string = string.concat("*" + getElement(i, j) + "*");
                    else
                        string = string.concat(getElement(i, j).toString());

                    string = string.concat(" ");
                }

                string = string.concat("\n");
            }

            return string;
        }
    }
}
