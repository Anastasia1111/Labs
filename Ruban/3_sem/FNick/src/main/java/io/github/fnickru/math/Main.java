package io.github.fnickru.math;

import io.github.fnickru.math.types.Fraction;
import io.github.fnickru.math.types.SquareMatrix;

import java.math.BigInteger;

public class Main {

    public static void main(String[] args) {
        System.out.println(new Fraction(0.5f));
        System.out.println(new Fraction(0.5));
        System.out.println(new Fraction(BigInteger.ONE, new BigInteger("2")));
        System.out.println();
        SquareMatrix<Fraction> matrix = new SquareMatrix<>(5);
        for (int i = 1; i <= matrix.getSize(); ++i)
            for (int j = 1; j <= matrix.getSize(); ++j)
                matrix.set(new Fraction(BigInteger.valueOf(i), BigInteger.valueOf(j)), i - 1, j - 1);
        System.out.println(matrix);
    }

}
