package ru.labs.fnick;

final public class Convolution {
    public static int lastT = 0;

    private Convolution(){}

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

    public static void test() {
        int[] a, b;
        int n = 4;
        a = new int[n];
        b = new int[n];
        for (int i = 0; i < n; ++i)
        {
            a[i] = i + 1;
            b[i] = i + 1;
        }
        for (int i : a)
            System.out.print(i + " ");
        System.out.println();
        for (int i : b)
            System.out.print(i + " ");
        System.out.println();
        int[] c = Convolution.basic(a, b);
        for (int i : c)
            System.out.print(i + " ");
        System.out.println();
        System.out.print("T = " + lastT);
    }
}
