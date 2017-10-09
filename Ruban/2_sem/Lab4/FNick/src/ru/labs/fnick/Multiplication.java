package ru.labs.fnick;

final public class Multiplication {
    public static long lastT = 0;

    private Multiplication(){}

    static private long recursiveFastStep(int x, int y)
    {
        int n = 0;
        if (x > y)
            while ((x >> n) != 0)
                ++n;
        else
            while ((y >> n) != 0)
                ++n;
        long res;
        if (n <= 1)
            return x * y;

        int k = n / 2;
        int a = x >> k;
        int b = x & ((1 << k) - 1);
        int c = y >> k;
        int d = y & ((1 << k) - 1);
        long u;
        int sum1 = a + b;
        int sum2 = c + d;
        if (sum1 >= (1 << k) || sum2 >= (1 << k))
        {
            int a1 = sum1 >> k;
            int b1 = sum2 >> k;
            int a2 = sum1 & ((1 << k) - 1);
            int b2 = sum2 & ((1 << k) - 1);
            u = (a1 * a2) << (2 * k);
            if (a1 != 0)
            {
                if (b1 != 0)
                {
                    u += (b2 + a2) << k;
                } else {
                    u += b2 << k;
                }
            } else {
                u += a2 << k;
            }
            u += recursiveFastStep(a2, b2);
        } else {
            u = recursiveFastStep(sum1, sum2);
        }
        long v = recursiveFastStep(a, c);
        long w = recursiveFastStep(b, d);
        return (v << (2 * k)) + ((u - v - w) << k) + w;
    }

    static public long fast(int x, int y)
    {
        lastT = 0;
        return recursiveFastStep(x, y);
    }

    static public long column(int x, int y)
    {
        lastT = 0;
        int k1 = 0, k2 = 0;
        long sum = 0;
        while ((x >> k1) != 0)
            ++k1;
        while ((y >> k2) != 0)
            ++k2;
        if (k1 > k2)
            for (int i = 0; i < k2; ++i)
            {
                if (((y >> i) & 1) == 1)
                {
                    sum += x << i;
                    lastT += k1;
                }
            }
        else
            for (int i = 0; i < k1; ++i)
            {
                if (((x >> i) & 1) == 1)
                {
                    sum += y << i;
                    lastT += k2;
                }
            }
        return sum;
    }

    public static void test()
    {
        int x = 20;
        int y = 30;
        System.out.println(x + " * " + y + " = " + Multiplication.column(x, y) + "\nT = " + lastT);
        System.out.println(x + " * " + y + " = " + Multiplication.fast(x, y) + "\nT = " + lastT);
    }
}
