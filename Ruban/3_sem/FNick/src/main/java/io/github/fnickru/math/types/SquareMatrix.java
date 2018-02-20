package io.github.fnickru.math.types;

import java.util.Arrays;

public class SquareMatrix implements Matrix {

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

    public void resize(int newSize) {
        Fraction[][] newMatrix = new Fraction[newSize][newSize];
        for (int i = 0; i < newSize; ++i)
            newMatrix[i] = Arrays.copyOf(matrix[i], newSize);
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
