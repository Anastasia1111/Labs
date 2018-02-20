package io.github.fnickru.math.types;

public interface Matrix {

    Fraction get(int i, int j);

    void set(Fraction value, int i, int j);

    int size();

    Fraction[][] getMatrix();

    static Fraction determinant(Matrix matrix) {
        if (matrix == null)
            throw new IllegalArgumentException("Matrix is null!");

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
}
