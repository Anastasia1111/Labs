package io.github.fnickru.math.struct.simplex;

import io.github.fnickru.math.exeptions.NoSolutionException;
import io.github.fnickru.math.struct.Fraction;

public class Problem {
    private CostFunction costFunction;
    private Limitation[] limitations;
    private SimplexTable simplexTable;
    private SimplexAnswer answer;

    public Problem(CostFunction function, Limitation... limitations) {
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
        Fraction[][] table = new Fraction[rows][cols];

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
    }

    private void createAnswer() {
        answer = new SimplexAnswer(simplexTable);
        int[] rowId = simplexTable.getRowId();

        for (int v = 0; v < costFunction.getLength(); ++v) {
            int j = 0;
            while(j < simplexTable.rows() - 1 && rowId[j] != v)
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

        System.out.println(simplexTable);

        while (!solved) {
            int row = simplexTable.getResRow();
            if (row != -1) {
                int col = simplexTable.getResCol(row);
                if (col != -1)
                    simplexTable.step(row, col);
                else
                    throw new NoSolutionException("No solution");
            } else {
                int col = simplexTable.getResCol(simplexTable.rows() - 1);
                if (col != -1) {
                    row = simplexTable.getResRow(col);
                    if (row != -1)
                        simplexTable.step(row, col);
                    else
                        throw new NoSolutionException("No solution");
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
}
