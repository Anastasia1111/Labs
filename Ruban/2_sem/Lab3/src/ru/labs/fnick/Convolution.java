package ru.labs.fnick;

public class Convolution {
    public static int lastT = 0;

    static public int[] basic(int[] a, int[] b)
    {
        lastT = 0;
        int n = a.length;
        int[] c = new int[n * 2];
        for (int i = 0; i < n; ++i)
            for (int k = 0; k <= i; ++k)
            {
                c[i] += a[k]*b[i-k];
                c[2*n-2-i] += a[n-1-k]*b[n-1-i+k];
                lastT+=2;
            }
        return c;
    }
}
