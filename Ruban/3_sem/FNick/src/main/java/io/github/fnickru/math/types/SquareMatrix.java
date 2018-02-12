package io.github.fnickru.math.types;

public class SquareMatrix<E> {

    private Object[][] matrix;
    private int size;

    public SquareMatrix()
    {
        this(1);
    }

    public SquareMatrix(int size)
    {
        this.size = size;
        matrix = new Object[size][size];
    }

    public E get(int i, int j)
    {
        return (E) matrix[i][j];
    }

    public void set(E value, int i, int j)
    {
        matrix[i][j] = value;
    }

    public int getSize() {
        return size;
    }

    @Override
    public String toString() {
        String res = "";
        for (Object[] objects : matrix) {
            for (Object o : objects) {
                res += o.toString() + " ";
            }
            res += "\n";
        }
        return res;
    }
}
