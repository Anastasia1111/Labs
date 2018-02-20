package io.github.fnickru.math.labs;

import io.github.fnickru.math.types.Fraction;
import io.github.fnickru.math.types.Matrix;
import io.github.fnickru.math.types.SquareMatrix;
import io.github.fnickru.math.util.FileWorker;

import java.math.BigInteger;

public class Lab2 {

    public static void main(String[] args) {
        System.out.println(new Fraction(1.0f/3, 3));
        System.out.println(new Fraction(BigInteger.ONE, new BigInteger("3")));
        System.out.println();
        SquareMatrix matrix = FileWorker.readSquareMatrix("./src/main/resources/matrix.txt");
        System.out.println(Matrix.determinant(matrix));
    }

}
