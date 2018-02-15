package io.github.fnickru.math.types;

import java.math.BigInteger;

public class SquareMatrix {

    private Fraction[][] matrix;

    public SquareMatrix()
    {
        this(1);
    }

    public SquareMatrix(int size)
    {
        if (size <= 0)
            throw new IllegalArgumentException("Wrong size!");
        matrix = new Fraction[size][size];
    }

    public SquareMatrix(Fraction[][] matrix)
    {
        int size = matrix.length;
        if (size != matrix[0].length)
            throw new IllegalArgumentException("Matrix is not square!");

        this.matrix = new Fraction[size][size];
        for (int i = 0; i < size; ++i)
            System.arraycopy(matrix[i], 0, this.matrix[i], 0, size);
    }

    public Fraction get(int i, int j)
    {
        return matrix[i][j];
    }

    public void set(Fraction value, int i, int j)
    {
        matrix[i][j] = value;
    }

    public int size() {
        return matrix.length;
    }

    public Fraction[][] getMatrix() {
        return matrix;
    }

    public static Fraction determinant(SquareMatrix matrix)
    {
        int n = matrix.size();

        Fraction[][] m = new Fraction[n][n];
        for (int i = 0; i < n; ++i)
            System.arraycopy(matrix.getMatrix()[i], 0, m[i], 0, n);

        int sign = 1;
        Fraction det = Fraction.ONE;
        for (int i = 0; i < n; ++i) {
            int k = i;
            for (int j = i + 1; j < n; ++j) {
                if (m[k][i].equals(Fraction.ZERO)) {
                    k = j;
                }
            }
            if (m[k][i].equals(Fraction.ZERO))
                return Fraction.ZERO;
            if (i != k) {
                sign = -sign;
                Fraction[] t = m[i];
                m[i] = m[k];
                m[k] = t;
            }
            for (int j = i + 1; j < n; ++j) {
                Fraction kf = m[j][i].divide(m[i][i]);
                for (int p = 0; p < n; ++p) {
                    m[j][p] = m[j][p].subtract(m[i][p].multiply(kf));
                }
            }
            for (Fraction[] fractions : m) {
                for (Fraction fraction : fractions) {
                    System.out.print(fraction + " ");
                }
                System.out.println();
            }
            System.out.println();
        }
        for (int i = 0; i < n; i++)
            det = det.multiply(m[i][i]);
        if (sign < 0)
            det = det.negate();
        return det;
    }

    @Override
    public String toString() {
        String res = "";
        for (Fraction[] row : matrix) {
            for (Fraction el : row) {
                res += el.toString() + "\t";
            }
            res += "\n";
        }
        return res;
    }
}
