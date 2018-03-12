package io.github.fnickru.math.types;

import java.util.Arrays;

public class Simplex {
    private Fraction[] function;
    private Fraction[][] constraints;

    Simplex(Fraction[] function, Fraction[]... constraints)
    {
        this.function = Arrays.copyOf(function, function.length);

    }

    public static void main(String[] args) {
        Fraction[] args1 = new Fraction[5];
        args1[0] = new Fraction("0");
        args1[1] = new Fraction("0");
        args1[2] = new Fraction("0");
        args1[3] = new Fraction("1");
        args1[4] = new Fraction("-1");
        Function function = new Function(args1);
        System.out.println(function);
    }
}
