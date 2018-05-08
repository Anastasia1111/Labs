package io.github.fnickru.math.struct.transportation;

import io.github.fnickru.math.struct.Fraction;
import io.github.fnickru.math.struct.Memento;

import java.util.*;

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
    private int resRow = -1;
    private int resCol = -1;

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
        for (int i = 0; i < this.table.length; ++i)
            this.table[i] = transportationTable.table[i].clone();
        this.stock = transportationTable.stock.clone();
        this.required = transportationTable.required.clone();

        this.resRow = transportationTable.resRow;
        this.resCol = transportationTable.resCol;

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

    private LinkedList<Integer> dfsHorizontal(int start, int finish, Integer previous, List<Integer> cycle) {
        LinkedList<Integer> path = new LinkedList<>(cycle);
        if (start != finish || previous < 0) {
            int n = table[0].length;

            int st_i = start / n;
            int st_j = start % n;

            List<Integer> neighbours = new LinkedList<>();

            for (int j = 0; j < n; ++j) {
                if (j != st_j && table[st_i][j].quantity != null) {
                    neighbours.add(st_i * n + j);
                }
            }

            neighbours.removeAll(cycle);
            neighbours.remove(previous);

            for (Integer neighbour : neighbours) {
                LinkedList<Integer> newPath = new LinkedList<>(cycle);
                newPath.add(neighbour);
                newPath = dfsVertical(neighbour, finish, start, newPath);
                if (newPath.getLast() == finish) {
                    path = newPath;
                    break;
                }
            }
        }

        return path;
    }

    private LinkedList<Integer> dfsVertical(int start, int finish, Integer previous, List<Integer> cycle) {
        LinkedList<Integer> path = new LinkedList<>(cycle);
        if (start != finish || previous < 0) {
            int n = table[0].length;
            int m = table.length;

            int st_i = start / n;
            int st_j = start % n;

            List<Integer> neighbours = new LinkedList<>();

            for (int i = 0; i < m; ++i) {
                if (i != st_i && table[i][st_j].quantity != null) {
                    neighbours.add(i * n + st_j);
                }
            }

            neighbours.removeAll(cycle);
            neighbours.remove(previous);

            for (Integer neighbour : neighbours) {
                LinkedList<Integer> newPath = new LinkedList<>(cycle);
                newPath.add(neighbour);
                newPath = dfsHorizontal(neighbour, finish, start, newPath);
                if (newPath.getLast() == finish) {
                    path = newPath;
                    break;
                }
            }
        }

        return path;
    }

    private List<Integer> findCycle(int i, int j) {
        LinkedList<Integer> cycle = new LinkedList<>();

        int start = i * table[0].length + j;

        cycle = dfsHorizontal(start, start, -1, cycle);
        cycle.removeLast();

        return new ArrayList<>(cycle);
    }

    void step(int i, int j) {
        resRow = i;
        resCol = j;

        stateList.add(new TransportationTable(this));

        table[i][j].quantity = Fraction.ZERO;

        List<Integer> cycle = findCycle(i, j);

        Fraction min = Fraction.INFINITY;
        int mini = -1, minj = -1;
        for (int k = 0; k < cycle.size(); k += 2) {
            int element = cycle.get(k);
            int el_i = element / table[0].length;
            int el_j = element % table[0].length;
            min = Fraction.min(min, table[el_i][el_j].quantity);
            if (min.equals(table[el_i][el_j].quantity)) {
                mini = el_i;
                minj = el_j;
            }
        }
        for (int k = 0; k < cycle.size(); k += 2) { // -
            int element = cycle.get(k);
            int el_i = element / table[0].length;
            int el_j = element % table[0].length;
            table[el_i][el_j].quantity = table[el_i][el_j].quantity.subtract(min);
        }
        for (int k = 1; k < cycle.size(); k += 2) { // +
            int element = cycle.get(k);
            int el_i = element / table[0].length;
            int el_j = element % table[0].length;
            table[el_i][el_j].quantity = table[el_i][el_j].quantity.add(min);
        }

        table[i][j].quantity = min;
        table[mini][minj].quantity = null;
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
                String sign = (i == resRow && j == resCol) ? "*" : "";
                string = string.concat(String.format("%10s ", sign + table[i][j] + sign));
            }
            string = string.concat("\n");
        }

        return string;
    }
}
