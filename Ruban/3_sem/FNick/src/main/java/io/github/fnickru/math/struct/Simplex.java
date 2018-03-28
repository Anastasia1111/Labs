package io.github.fnickru.math.struct;

import io.github.fnickru.math.exeptions.NoSolutionException;
import io.github.fnickru.math.util.FileWorker;

import java.util.*;

public class Simplex {
    private CostFunction costFunction;
    private Limitation[] limitations;
    private SimplexTable simplexTable;
    private Answer answer;
    private int[] rowId;
    private int[] colId;

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
    }

    private void createAnswer() {
        answer = new Answer(simplexTable);

        for (int v = 0; v < costFunction.getLength(); ++v) {
            int j = 0;
            while(j < simplexTable.rows() - 1 && rowId[j] != (v + 1))
                ++j;
            if (j == simplexTable.rows() - 1)
                answer.addItem("x" + v, Fraction.ZERO);
            else
                answer.addItem("x" + v, simplexTable.getElement(j, 0));
        }

        String optimizationDirection = costFunction.shouldBeMinimized() ? "min" : "max";
        Fraction costFunctionValue = costFunction.shouldBeMinimized() ? simplexTable.getElement(simplexTable.rows() - 1, 0).negate() : simplexTable.getElement(simplexTable.rows() - 1, 0);
        answer.addItem(optimizationDirection + " F", costFunctionValue);
    }

    public String getAnswer() {
        return answer.toString();
    }

    public void solve() throws NoSolutionException {
        boolean solved = false;

        for (int i = 0; i < simplexTable.cols() - 1; ++i) {
            colId[i] = i + 1;
        }
        for (int i = 0; i < simplexTable.rows() - 1; ++i) {
            rowId[i] = i + simplexTable.cols();
        }

        while (!solved) {
            int row = simplexTable.getResRow();
            if (row != -1) {
                int col = simplexTable.getResCol(row);
                if (col != -1) {
                    rowId[row] += colId[col - 1];
                    colId[col - 1] = rowId[row] - colId[col - 1];
                    rowId[row] -= colId[col - 1];
                    simplexTable.setResElement(row, col);
                    simplexTable.step(row, col);
                } else
                    throw new NoSolutionException("No solution");
            } else {
                int col = simplexTable.getResCol(simplexTable.rows() - 1);
                if (col != -1) {
                    row = simplexTable.getResRow(col);
                    if (row != -1) {
                        rowId[row] += colId[col - 1];
                        colId[col - 1] = rowId[row] - colId[col - 1];
                        rowId[row] -= colId[col - 1];
                        simplexTable.setResElement(row, col);
                        simplexTable.step(row, col);
                    } else
                        throw new NoSolutionException("No solution\n" + simplexTable);
                } else {
                    solved = true;
                }
            }
        }

        createAnswer();
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
        try {
            simplex.solve();
            System.out.println(simplex.getAnswer());
        } catch (NoSolutionException e) {
            e.printStackTrace();
        }
    }

    private class SimplexTable {

        private Fraction[][] table;
        private int resRow = -1;
        private int resCol = -1;
        private List<SimplexTable> stateList;

        private SimplexTable(Fraction[][] table) {
            this.table = table.clone();
            for(int i = 0; i < this.table.length; i++)
                this.table[i] = table[i].clone();
            stateList = new ArrayList<>();
        }

        private SimplexTable(Fraction[][] table, int resRow, int resCol) {
            this.table = table.clone();
            for(int i = 0; i < this.table.length; i++)
                this.table[i] = table[i].clone();
            stateList = new ArrayList<>();
            this.resRow = resRow;
            this.resCol = resCol;
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

        public void setResElement(int row, int column) {
            resCol = column;
            resRow = row;
        }

        private int getResRow() {
            int index = 0;
            for (int i = 1; i < rows() - 1; ++i) {
                if (table[i][0].isNegative() && table[index][0].compareTo(table[i][0]) > 0)
                    index = i;
            }
            return table[index][0].isNegative() ? index : -1;
        }

        private int getResRow(int resCol) {
            int index = -1;
            Fraction ratio = Fraction.INFINITY;
            for (int i = 0; i < rows() - 1; ++i) {
                if (table[i][0].compareTo(Fraction.ZERO) > 0
                    && table[i][resCol].compareTo(Fraction.ZERO) > 0
                    && table[i][0].divide(table[i][resCol]).compareTo(ratio) < 0) {
                    index = i;
                    ratio = table[i][0].divide(table[i][resCol]);
                }
            }
            return index;
        }

        private int getResCol(int resRow) {
            int index = 1;
            for (int i = 2; i < cols(); ++i) {
                if (table[resRow][i].isNegative() && table[resRow][index].compareTo(table[resRow][i]) > 0)
                    index = i;
            }
            return table[resRow][index].isNegative() ? index : -1;
        }

        private void step(int resRow, int resCol) {
            stateList.add(new SimplexTable(table, resRow, resCol));

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
            String string = resRow + " " + resCol + "\n";

            for (int i = 0; i < rows(); i++) {
                for (int j = 0; j < cols(); j++) {
                    if (i == resRow && j == resCol)
                        string = string.concat("*" + getElement(i, j) + "*");
                    else
                        string = string.concat(getElement(i, j).toString());
                    string = string.concat("\t");
                }
                string = string.concat("\n");
            }

            return string;
        }
    }

    private class Answer {

        private Map<String, Fraction> items;
        private SimplexTable simplexTable;

        Answer(SimplexTable simplexTable) {
            this.simplexTable = simplexTable;
            items = new LinkedHashMap<>();
        }

        private void addItem(String key, Fraction value) {
            items.put(key, value);
        }

        public String toString() {
            String string = "";

            List<SimplexTable> stateList = simplexTable.getStateList();
            for (SimplexTable table : stateList) {
                string = string.concat(table + "\n");
            }
            string += simplexTable;

            for (Map.Entry<String, Fraction> item : items.entrySet())
                string = string.concat("\n" + item.getKey() + " = " + item.getValue());

            return string;
        }
    }
}
