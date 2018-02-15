package io.github.fnickru.math;

import io.github.fnickru.math.types.Fraction;
import io.github.fnickru.math.types.SquareMatrix;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        System.out.println(new Fraction(1.0f/3));
        System.out.println(new Fraction(BigInteger.ONE, new BigInteger("3")));
        System.out.println();
        /*SquareMatrix matrix = new SquareMatrix(5);
        for (int i = 1; i <= matrix.size(); ++i)
            for (int j = 1; j <= matrix.size(); ++j)
                matrix.set(new Fraction(BigInteger.valueOf(i), BigInteger.valueOf(j)), i - 1, j - 1);*/
        Fraction[][] matr = new Fraction[4][4];
        Scanner in = new Scanner(System.in);
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                matr[i][j] = new Fraction(in.nextInt());
        SquareMatrix matrix = new SquareMatrix(matr);
        System.out.println(SquareMatrix.determinant(matrix));
    }

}
