package io.github.fnickru.math.struct;

import io.github.fnickru.math.exeptions.NoSolutionException;
import io.github.fnickru.math.util.FileWorker;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

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

        System.out.println(costFunction.getLength());
        for (int v = 0; v < costFunction.getLength(); ++v) {
            int j = 0;
            while(j < simplexTable.rows() - 1 && rowId[j] != (v + 1))
                ++j;
            if (j == simplexTable.rows() - 1)
                answer.addItem("x" + j, Fraction.ZERO);
            else
                answer.addItem("x" + j, simplexTable.getElement(j, 0));
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
            int col = simplexTable.getNegativeCol();
            if(simplexTable.getNegativeCol() != 0) {
                int resRow = simplexTable.getResRow(col);
                if (resRow == -1) {
                    throw new NoSolutionException("No solution");
                } else {
                    int resCol = simplexTable.getResCol(resRow, true);
                    rowId[resRow] += colId[resCol - 1];
                    colId[resCol - 1] = rowId[resRow] - colId[resCol - 1];
                    rowId[resRow] -= colId[resCol - 1];
                    simplexTable.step(resRow, resCol);
                }
            } else {
                int resRow = simplexTable.getResRow();
                if (resRow == -1) {
                    solved = true;
                } else {
                    int resCol = simplexTable.getResCol(resRow, false);
                    if (resCol == -1) {
                        throw new NoSolutionException("No solution");
                    } else {
                        rowId[resRow] += colId[resCol - 1];
                        colId[resCol - 1] = rowId[resRow] - colId[resCol - 1];
                        rowId[resRow] -= colId[resCol - 1];
                        simplexTable.step(resRow, resCol);
                    }
                }
            }
        }

        createAnswer();
    }

    public String getHistory() {
        List<SimplexTable> stateList = simplexTable.getStateList();
        String string = "";
        for (SimplexTable table : stateList) {
            string = string.concat(table + "\n");
        }
        string += simplexTable;
        return string;
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
            System.out.println(simplex.getHistory());
            System.out.println(simplex.getAnswer());
        } catch (NoSolutionException e) {
            e.printStackTrace();
        }
    }

    private class SimplexTable {

        private Fraction[][] table;
        private List<SimplexTable> stateList;

        private SimplexTable(Fraction[][] table) {
            this.table = table.clone();
            for(int i = 0; i < this.table.length; i++)
                this.table[i] = table[i].clone();
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

        private int getNegativeCol() {
            for (int i = 1; i < cols(); i++)
                if (table[rows() - 1][i].isNegative())
                    return i;
            return 0;
        }

        private int getResCol(int resRow, boolean firstHalf) {
            Fraction r, maxR = Fraction.ZERO;
            boolean firstRatio = true;
            int resCol = 0;

            for (int i = 1; i < cols(); ++i) {
                if (firstHalf) {
                    if (!table[resRow][i].equals(Fraction.ZERO)) {
                        r = table[rows() - 1][i].divide(table[resRow][i]);
                        if (r.isNegative() || (r.equals(Fraction.ZERO) && table[resRow][i].isNegative())) {
                            maxR = r;
                            resCol = i;
                        }
                    }
                } else {
                    if (table[resRow][i].isNegative()) {
                        r = table[rows() - 1][i].divide(table[resRow][i]);
                        if ((r.compareTo(Fraction.ZERO) <= 0) && (firstRatio || r.compareTo(maxR) > 0)) {
                            firstRatio = false;
                            maxR = r;
                            resCol = i;
                        }
                    }
                }
            }

            return resCol;
        }

        private int getResRow(int col) {
            for (int i = 0; i < rows() - 1; ++i) {
                if (table[i][col].compareTo(Fraction.ZERO) > 0)
                    return i;
            }
            return -1;
        }

        private int getResRow() {
            for (int i = 0; i < rows() - 1; ++i) {
                if (table[i][0].isNegative())
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
                    int resCol = getNegativeCol();
                    int resRow = getResRow(resCol);

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

            for (Map.Entry<String, Fraction> item : items.entrySet())
                string = string.concat("\n" + item.getKey() + " = " + item.getValue());

            return string.substring(1);
        }
    }
}
