package io.github.fnickru.math.labs;

import io.github.fnickru.math.struct.Fraction;
import io.github.fnickru.math.struct.Matrix;
import io.github.fnickru.math.util.FileWorker;

import java.math.BigInteger;

public class FracMatrix {

    public static void main(String[] args) {
        System.out.println(new Fraction(1.0f/3, 3));
        System.out.println(new Fraction(BigInteger.ONE, new BigInteger("3")));
        System.out.println();
        Matrix matrix = FileWorker.readMatrix("./src/main/resources/matrix/matrix.txt");
        System.out.println(matrix);
        System.out.println(Matrix.determinant(matrix));
    }

}
