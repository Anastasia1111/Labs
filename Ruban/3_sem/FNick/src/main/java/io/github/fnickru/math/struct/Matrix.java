package io.github.fnickru.math.struct;

import java.util.Arrays;

public class Matrix {

    private boolean isSquare;

    private Fraction[][] matrix;

    public Matrix()
    {
        this(1);
    }

    public Matrix(int size)
    {
        this(size, size);
    }

    public Matrix(int rows, int columns)
    {
        if (rows <= 0 || columns <= 0)
            throw new IllegalArgumentException("Wrong size!");

        isSquare = rows == columns;
        matrix = new Fraction[rows][columns];
    }

    public Matrix(Fraction[][] matrix)
    {
        if (matrix == null)
            throw new IllegalArgumentException("Matrix is null!");

        int rows = matrix.length;
        int columns = matrix[0].length;

        isSquare = rows == columns;

        this.matrix = new Fraction[rows][];
        for (int i = 0; i < rows; ++i)
            this.matrix[i] = Arrays.copyOf(matrix[i], columns);
    }

    public Fraction get(int i, int j)
    {
        Fraction element = null;
        try {
            element = matrix[i][j];
        } catch (Exception e) {
            e.printStackTrace();
        }
        return element;
    }

    public void set(Fraction value, int i, int j)
    {
        try {
            matrix[i][j] = value;
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public int rows() {
        return matrix.length;
    }

    public int columns() {
        return matrix[0].length;
    }

    public Fraction[][] getMatrix() {
        return matrix.clone();
    }

    public void resize(int rows, int columns) {
        if (rows <= 0 || columns <= 0)
            throw new IllegalArgumentException("Wrong size!");

        isSquare = rows == columns;

        Fraction[][] newMatrix = new Fraction[rows][];
        for (int i = 0; i < rows; ++i)
            newMatrix[i] = Arrays.copyOf(matrix[i], columns);
        this.matrix = newMatrix;
    }

    public void addRow(Fraction[] row)
    {
        int rows = matrix.length;
        int columns = matrix[0].length;

        this.resize(rows + 1, columns);

        for (int i = 0; i < columns; ++i)
            this.set(row[i], rows, i);
    }

    public void addColumn(Fraction[] column)
    {
        int rows = matrix.length;
        int columns = matrix[0].length;

        this.resize(rows, columns + 1);

        for (int i = 0; i < rows; ++i)
            this.set(column[i], i, columns);
    }

    static public Fraction determinant(Matrix matrix) {
        if (matrix == null)
            throw new IllegalArgumentException("Matrix is null!");
        if (matrix.rows() != matrix.columns())
            throw new IllegalArgumentException("Matrix is not square!");

        int n = matrix.rows();

        Fraction[][] m = matrix.getMatrix();

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
                res = res.concat(el.toString() + "\t");
            }
            res = res.concat("\n");
        }
        return res;
    }
}
