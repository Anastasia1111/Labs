package io.github.fnickru.math.struct.transportation;

import io.github.fnickru.math.struct.Fraction;
import io.github.fnickru.math.struct.Matrix;
import io.github.fnickru.math.struct.LinearProgrammingProblem;
import io.github.fnickru.math.struct.Solution;

import java.util.List;

public class TransportationProblem implements LinearProgrammingProblem {
    private List<Fraction> stock;
    private List<Fraction> required;
    private Matrix cost;
    private TransportationTable table;
    private Solution<TransportationTable> solution;

    public TransportationProblem(List<Fraction> stock, List<Fraction> required, Matrix cost) {
        this.stock = stock;
        this.cost = cost;
        this.required = required;
        setup();
    }

    private void setup() {
        Fraction suma = Fraction.ZERO;
        Fraction sumb = Fraction.ZERO;

        for (Fraction fraction : stock) {
            suma = suma.add(fraction);
        }
        for (Fraction fraction : required) {
            sumb = sumb.add(fraction);
        }
        Fraction[] vector;
        switch (suma.compareTo(sumb)) {
            case -1: // suma < sumb
                stock.add(sumb.subtract(suma));
                vector = new Fraction[required.size()];
                for (int j = 0; j < required.size(); ++j)
                    vector[j] = Fraction.ZERO;
                cost.addRow(vector);
                break;
            case 1: // suma > sumb
                required.add(suma.subtract(sumb));
                vector = new Fraction[stock.size()];
                for (int j = 0; j < stock.size(); ++j)
                    vector[j] = Fraction.ZERO;
                cost.addColumn(vector);
                break;
        }

        int stockSize = stock.size(), requiredSize = required.size();
        boolean[][] filled = new boolean[stockSize][requiredSize];
        Fraction minCost, x;
        int minStock = -1, minReq = -1;
        Fraction[] a = stock.toArray(new Fraction[0]);
        Fraction[] b = required.toArray(new Fraction[0]);

        table = new TransportationTable(cost.getMatrix(), a, b);

        for (int k = 0; k < (stockSize + requiredSize - 1); ++k) {
            minCost = Fraction.INFINITY;
            for (int i = 0; i < stockSize; ++i) {
                for (int j = 0; j < requiredSize; ++j) {
                    if (!filled[i][j]) {
                        Fraction c = cost.get(i, j);
                        if (c.compareTo(minCost) < 0) {
                            minCost = c;
                            minStock = i;
                            minReq = j;
                        }
                    }
                }
            }
            x = Fraction.min(a[minStock], b[minReq]);
            table.setQuantity(x, minStock, minReq);

            a[minStock] = a[minStock].subtract(x);
            b[minReq] = b[minReq].subtract(x);

            if (a[minStock].equals(Fraction.ZERO))
                for (int j = 0; j < requiredSize; ++j)
                    filled[minStock][j] = true;
            else
                for(int i = 0; i < stockSize; ++i)
                    filled[i][minReq] = true;
        }
    }

    @Override
    public void solve() {

    }

    @Override
    public String getSolution() {
        return solution.toString();
    }

    @Override
    public String toString() {
        return table.toString();
    }
}
