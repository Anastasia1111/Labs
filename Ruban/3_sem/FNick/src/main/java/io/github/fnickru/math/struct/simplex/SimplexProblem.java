package io.github.fnickru.math.struct.simplex;

import io.github.fnickru.math.exeptions.NoSolutionException;
import io.github.fnickru.math.struct.Fraction;
import io.github.fnickru.math.struct.LinearProgrammingProblem;
import io.github.fnickru.math.struct.Solution;

public class SimplexProblem implements LinearProgrammingProblem {
    private CostFunction costFunction;
    private Limitation[] limitations;
    private SimplexTable table;
    private Solution<SimplexTable> solution;

    public SimplexProblem(CostFunction function, Limitation... limitations) {
        this.costFunction = function;
        this.limitations = limitations;
        setup();
    }

    private void setup() {
        int varnum = costFunction.getLength();
        for (Limitation limitation : limitations)
            varnum = Math.max(limitation.getLength(), varnum);
        int rows = limitations.length + 2; // F & M
        int cols = varnum + 1; // B
        Fraction[][] table = new Fraction[rows][cols];

        table[rows - 1][0] = Fraction.ZERO;
        table[rows - 2][0] = Fraction.ZERO;

        for (int v = 0; v < varnum; ++v) {
            if (costFunction.shouldBeMinimized())
                table[rows - 2][v + 1] = costFunction.getCoef(v);
            else
                table[rows - 2][v + 1] = costFunction.getCoef(v).negate();
            table[rows - 1][v + 1] = Fraction.ZERO;
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

        String[] rowId = new String[limitations.length];
        String[] colId = new String[varnum];
        for (int i = 0; i < colId.length; ++i) {
            colId[i] = "x" + i;
        }

        index = 0;
        for (Limitation l : limitations) {
            switch (l.getSign()) {
                case GE:
                    table[index][0] = l.getFreeTerm().negate();
                    rowId[index] = "x" + (index + table[0].length - 1);
                    break;
                case EQ:
                    table[index][0] = l.getFreeTerm();
                    rowId[index] = "r" + (index + table[0].length - 1);
                    break;
                case LE:
                    table[index][0] = l.getFreeTerm();
                    rowId[index] = "x" + (index + table[0].length - 1);
                    break;
            }
            ++index;
        }
        for (int i = 0; i < rowId.length; ++i)
            if (rowId[i].startsWith("r"))
                for (int j = 0; j <= varnum; ++j)
                    table[limitations.length + 1][j] = table[limitations.length + 1][j].subtract(table[i][j]);

        this.table = new SimplexTable(table, rowId, colId);
    }

    private void createSolution() throws NoSolutionException {
        solution = new Solution<>(table);
        String[] rowId = table.getRowId();

        for (int v = 0; v < costFunction.getLength(); ++v) {
            int j = 0;
            while(j < rowId.length && !rowId[j].equals("x" + v)) {
                if (rowId[j].startsWith("r"))
                    throw new NoSolutionException("No solution");
                ++j;
            }
            if (j == rowId.length)
                solution.addItem("x" + v, Fraction.ZERO);
            else
                solution.addItem("x" + v, table.getElement(j, 0));
        }

        String optimizationDirection = costFunction.shouldBeMinimized() ? "min" : "max";
        Fraction costFunctionValue = costFunction.shouldBeMinimized() ? table.getElement(rowId.length, 0).negate() : table.getElement(rowId.length, 0);
        solution.addItem(optimizationDirection + " F", costFunctionValue);
    }

    public String getSolution() {
        return solution.toString();
    }

    public void solve() throws NoSolutionException {
        boolean solved = false;

        System.out.println(table);

        while (!solved) {
            int row = table.getResRow();
            if (row != -1) {
                int col = table.getResCol(row);
                if (col != -1)
                    table.step(row, col);
                else
                    throw new NoSolutionException("No solution");
            } else {
                int col = table.getResCol(table.rows() - 1);
                col = col == -1 ? table.getResCol(table.rows() - 2) : col;
                if (col != -1) {
                    row = table.getResRow(col);
                    if (row != -1)
                        table.step(row, col);
                    else
                        throw new NoSolutionException("No solution");
                } else {
                    solved = true;
                }
            }
        }

        createSolution();
    }

    @Override
    public String toString() {
        String str = "Function:\n" + costFunction + "\nLimitations:\n";
        for (Limitation limitation : limitations) {
            str = str.concat(limitation + "\n");
        }
        return str;
    }
}
