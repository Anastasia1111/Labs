package ru.labs.fnick;

import java.math.BigInteger;

final public class Multiplication {
    public static long lastT = 0;

    private Multiplication(){}

    private static BigInteger recursiveFastStep(BigInteger x, BigInteger y)
    {
        int n = Math.max(x.bitLength(), y.bitLength());
        BigInteger res;
        if (n <= 1)
        {
            ++lastT;
            return x.multiply(y);
        }

        String str_x = x.toString(2);
        String str_y = y.toString(2);
        if (n % 2 == 1)
        {
            char a1 = str_x.charAt(0);
            char b1 = str_y.charAt(0);
            BigInteger a2 = new BigInteger(str_x.substring(1), 2);
            BigInteger b2 = new BigInteger(str_y.substring(1), 2);
            res = new BigInteger("0");
            if(a1 != '0' && b1 != '0')
            {
                String first_s = "1";
                for (int i = 0; i < (2 * (n - 1)); ++i)
                    first_s += "0";
                BigInteger first = new BigInteger(first_s, 2);
                res = res.add(first);
                lastT += (n - 1);
            }
            if(a1 != 0)
            {
                BigInteger b2n = new BigInteger(b2.toString());
                for (int i = 0; i < (n - 1); ++i)
                    b2n = b2n.multiply(new BigInteger("2"));
                res = res.add(b2n);
            }
            if(b1 != 0)
            {
                BigInteger a2n = new BigInteger(a2.toString());
                for (int i = 0; i < (n - 1); ++i)
                    a2n = a2n.multiply(new BigInteger("2"));
                res = res.add(a2n);
            }
            res = res.add(recursiveFastStep(a2, b2));
        } else {
            int k = n / 2;
            BigInteger a = new BigInteger(str_x.substring(0, str_x.length() - k), 2);
            BigInteger b = new BigInteger(str_x.substring(str_x.length() - k), 2);
            BigInteger c = new BigInteger(str_y.substring(0, str_y.length() - k), 2);
            BigInteger d = new BigInteger(str_y.substring(str_y.length() - k), 2);
            BigInteger u = recursiveFastStep(a.add(b), c.add(d));
            lastT += 2 * k;
            BigInteger v = recursiveFastStep(a, c);
            BigInteger vn = new BigInteger(v.toString());
            for (int i = 0; i < n; ++i)
                vn = vn.multiply(new BigInteger("2"));
            BigInteger w = recursiveFastStep(b, d);
            BigInteger uvw = u.subtract(v).subtract(w);
            BigInteger uvwk = new BigInteger(uvw.toString());
            for (int i = 0; i < k; ++i)
                uvwk = uvwk.multiply(new BigInteger("2"));
            res = vn.add(uvwk).add(w);
            lastT += 2 * n;
        }
        return res;
    }

    public static BigInteger fast(BigInteger x, BigInteger y)
    {
        lastT = 0;
        return recursiveFastStep(x, y);
    }

    public static long column(int x, int y)
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
        BigInteger x, y;
        int radix = 2;
        String value = "0";
        for (int bit_count = 0; bit_count < 2000; ++bit_count)
            value += "1";
        x = new BigInteger(value, radix);
        y = new BigInteger(value, radix);
        //System.out.println(x + " * " + y + " = " + Multiplication.column(x, y) + "\nT = " + lastT);
        System.out.println(x + " * " + y + " = " + Multiplication.fast(x, y) + "\nT = " + lastT);
    }
}