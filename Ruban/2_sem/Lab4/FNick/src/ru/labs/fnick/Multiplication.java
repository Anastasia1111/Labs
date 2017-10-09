package ru.labs.fnick;

final public class Multiplication {
    public static long lastT = 0;

    private Multiplication(){}

    static private long recursiveFastStep(int x, int y, int n)
    {
        if (n <= 1)
            return x & y;

        long res;
        if (n % 2 != 0)
        {
            int a1 = x >> (n - 1),
                a2 = x & (~(1 << (n - 1))),
                b1 = y >> (n - 1),
                b2 = y & (~(1 << (n - 1)));
            res = (a1 & b1) << (2 * (n - 1));
            if (a1 == 0)
            {
                res += a2 << (n - 1);
            } else {
                if (b1 == 0)
                {
                    res += b2 << (n - 1);
                } else {
                    int sum = a2 + b2;
                    if (a2 != 0 && b2 != 0)
                        lastT += (n - 1) / 2;
                    res += sum << (n - 1);
                }
            }
            res += recursiveFastStep(a2, b2, (n - 1));
        } else {
            int k = n / 2;
            int a = x >> k;
            int b = x & ((1 << k) - 1);
            int c = y >> k;
            int d = y & ((1 << k) - 1);
            int apb = a + b;
            if (a != 0 && b != 0)
                lastT += k;
            int cpd = c + d;
            if (c != 0 && d != 0)
                lastT += k;
            long u;
            if (apb >= (1 << k) || cpd >= (1 << k))
            {
                u = recursiveFastStep(apb, cpd, k + 1);
            } else {
                u = recursiveFastStep(apb, cpd, k);
            }
            long v = recursiveFastStep(a, c, k);
            long w = recursiveFastStep(b, d, k);
            res = (v << n) + ((u - v - w) << k) + w;
            if (u != 0 && v != 0)
                lastT += n;
            if ((u - v) != 0 && w != 0)
                lastT += n;
        }
        return res;
    }

    static public long fast(int x, int y)
    {
        lastT = 0;
        int n = 0;
        if (x > y)
            while ((x >> n) != 0)
                ++n;
        else
            while ((y >> n) != 0)
                ++n;
        return recursiveFastStep(x, y, n);
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
    private static int T(int n)
    {
        if(n == 1) return 1;
        return 3*T(n/2) + (n % 2 != 0 ? 4*n : 3*n);
    }

    public static void test()
    {
        int x = 3869;//65535;
        int y = 8324;//65535;
        System.out.println(x + " * " + y + " = " + Multiplication.column(x, y) + "\nT = " + lastT);
        System.out.println(x + " * " + y + " = " + Multiplication.fast(x, y) + "\nT = " + lastT);
        System.out.println("Theoretical fast T = " + T(16));
    }
}
