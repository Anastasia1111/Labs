package ru.labs.fnick;

final public class Multiplication {
    public static long lastT = 0;
    private static final int INT_LENGTH = 32;

    private Multiplication(){}

    /*static private int[] summator(int[] a, int[] b)
    {
        int n = a.length;
        int pi, po;
        int[] s = new int[n + 1];
    }*/

    static private long recursiveColumnStep(int[] x, int[] y)
    {
        int n = x.length;
        int k = n / 2;
        int[] a = new int[k];
        int[] b = new int[k];
        int[] c = new int[k];
        int[] d = new int[k];
        for (int i = 0; i < k; ++i)
        {
            a[i] = x[i];
            b[i] = x[i + k];
            c[i] = y[i];
            d[i] = y[i + k];
        }
        long ac, ad, bc, bd;
        if (k == 1)
        {
            ac = a[0] * c[0];
            ad = a[0] * d[0];
            bc = b[0] * c[0];
            bd = b[0] * d[0];
        } else {
            ac = recursiveColumnStep(a, c);
            ad = recursiveColumnStep(a, d);
            bc = recursiveColumnStep(b, c);
            bd = recursiveColumnStep(b, d);
        }
        lastT += 4;
        long res = (ac << n) + ((ad + bc) << k) + bd;
        lastT += k;
        System.out.println(lastT);
        return res;
    }

    static public long inColumn(int x, int y)
    {
        lastT = 0;
        int n = INT_LENGTH;
        int[] arrx = new int[n];
        int[] arry = new int[n];
        for (int i = 0; i < n; ++i)
        {
            arrx[i] = (x << i) >>> (n - 1);
            arry[i] = (y << i) >>> (n - 1);
        }
        return recursiveColumnStep(arrx, arry);
    }

    public static void test() {
        System.out.println(Multiplication.inColumn(32000, 32000) + "\nT = " + lastT);
    }
}
