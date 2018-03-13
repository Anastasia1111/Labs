package io.github.fnickru.math.types;

import io.github.fnickru.math.util.FileWorker;

import java.util.ArrayList;
import java.util.Arrays;

public class Simplex {
    private Function function;
    private ArrayList<Function> constraints = new ArrayList<>();

    Simplex(Function function, boolean max, Function... constraints)
    {
        int length = function.length();
        for (Function constraint : constraints)
            length = Math.max(constraint.length(), length);

        this.function = max
                ? function.resize(length + constraints.length + 1)
                : function.negate().resize(length + constraints.length + 1);

        for (int i = 0; i < constraints.length; ++i) {
            if (!constraints[i].isLastFreeMember())
                throw new IllegalArgumentException(constraints[i] + " is not constraint");
            Function cons = constraints[i].resize(length + constraints.length + 1);
            if (cons.getFreeMember().isNegative())
                cons = cons.negate();
            cons.setFactor(length + i, Fraction.ONE);
            this.constraints.add(cons);
        }
    }

    /*public Fraction[][] getSimplexTable()
    {

    }*/

    @Override
    public String toString() {
        String str = "Function:\n" + function + "\nConstraints:\n";
        for (Function constraint : constraints) {
            str = str.concat(constraint + "\n");
        }
        return str;
    }

    public static void main(String[] args) {
        Function[] functions = FileWorker.readAllFunction("./src/main/resources/simplex.txt");
        for (int i = 1; i < functions.length; ++i)
            functions[i].setLastFreeMember(true);
        Function[] constraints = Arrays.copyOfRange(functions, 1, functions.length);
        Simplex simplex = new Simplex(functions[0], true, constraints);
        System.out.println(simplex);
    }
}
