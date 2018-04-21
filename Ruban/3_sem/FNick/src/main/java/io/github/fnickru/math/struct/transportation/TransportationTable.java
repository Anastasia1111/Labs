package io.github.fnickru.math.struct.transportation;

import io.github.fnickru.math.struct.Fraction;
import io.github.fnickru.math.struct.Memento;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

class TransportationTable implements Memento<TransportationTable> {

    private class Variable {
        Fraction quantity;
        Fraction cost;

        Variable() {
            quantity = null;
            cost = Fraction.ZERO;
        }

        @Override
        public String toString() {
            String var = quantity != null ? quantity.toString() : "-";
            return String.format("(%s|%s)", var, cost);
        }
    }

    private Variable[][] table;
    private List<TransportationTable> stateList;
    private Fraction[] stock;
    private Fraction[] required;

    TransportationTable(Fraction[][] cost, Fraction[] stock, Fraction[] required) {
        table = new Variable[stock.length][required.length];
        for (int i = 0; i < table.length; ++i)
            for (int j = 0; j < table[0].length; ++j) {
                table[i][j] = new Variable();
                table[i][j].cost = cost[i][j];
            }
        this.stock = stock.clone();
        this.required = required.clone();
        stateList = new ArrayList<>();
    }

    private TransportationTable(TransportationTable transportationTable) {
        this.table = transportationTable.table.clone();
        for(int i = 0; i < this.table.length; ++i)
            this.table[i] = transportationTable.table[i].clone();
        this.stock = transportationTable.stock;
        this.required = transportationTable.required;
        stateList = new ArrayList<>();
    }

    int rows() {
        return table.length;
    }

    int cols() {
        return table[0].length;
    }

    void setQuantity(Fraction value, int i, int j) {
        try {
            table[i][j].quantity = value;
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    Fraction getQuantity(int i, int j) {
        return table[i][j].quantity;
    }

    Fraction getCost(int i, int j) {
        return table[i][j].cost;
    }

    private List<Variable> pathFinder(int i, int j) {
        List<Variable> path = new LinkedList<>();
        List<Variable> vertical = new LinkedList<>();
        List<Variable> horizontal = new LinkedList<>();
        boolean isVertical = false;

        horizontal.add(table[i][j]);


        return path;
    }

    void step(int maxi, int maxj) {
        stateList.add(new TransportationTable(this));

        Integer plusi = -1, plusj = -1;
        if (!leftBottom(plusi, plusj, maxi, maxj))
            rightTop(maxi, maxj, plusi, plusj);
        Fraction min = Fraction.min(table[maxi][plusj].quantity, table[plusi][maxj].quantity);

        table[maxi][maxj].quantity = min;
        table[plusi][maxj].quantity = table[plusi][maxj].quantity.subtract(min);
        table[maxi][plusj].quantity = table[maxi][plusj].quantity.subtract(min);
        table[plusi][plusj].quantity = table[plusi][plusj].quantity.add(min);
    }

    public List<TransportationTable> getStateList() {
        return stateList;
    }

    public String toString() {
        String string = String.format("%14s ", "stock\\required");
        for (Fraction i : required) {
            string = string.concat(String.format("%10s ", i));
        }
        string += '\n';
        for (int i = 0; i < rows(); i++) {
            string = string.concat(String.format("%14s ", stock[i]));
            for (int j = 0; j < cols(); j++) {
                string = string.concat(String.format("%10s ", table[i][j]));
            }
            string = string.concat("\n");
        }

        return string;
    }


}
