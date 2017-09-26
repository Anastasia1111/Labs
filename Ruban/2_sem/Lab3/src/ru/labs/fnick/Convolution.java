package ru.labs.fnick;

public class Convolution {
    public static int lastT = 0;

    static public int[] basic(int[] a, int[] b)
    {
        lastT = 0;
        int n = a.length;
        int[] c = new int[n * 2];
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
            {
                c[i + k] += a[i] * b[k];
                ++lastT;
            }
        return c;
    }
}
