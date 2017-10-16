package ru.labs.fnick;

import java.util.Date;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

final public class Dynamic {
    public static long lastT = 0;

    private Dynamic(){}

    public static int Knapsack(int[] m, int[] c, int M)
    {
        int n = c.length;

        TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer>();
        for (int i = 0; i < n; ++i)
            map.put(m[i], c[i]);

        int[] f = new int[M + 1];
        for (int i = 0; i <= M; ++i)
        {
            f[i] = 0;
            for (Map.Entry<Integer, Integer> entry : map.entrySet())
            {
                if (i - entry.getKey() < 0) break;
                f[i] = Math.max(f[i], f[i - entry.getKey()] + entry.getValue());
                ++lastT;
            }
        }

        return f[M];
    }

    public static void test()
    {
        int[] m = {8, 5, 3};
        int[] c = {23, 14, 8};
        int M = 13;
        int C = Dynamic.Knapsack(m, c, 13);
        System.out.println("F(" + M + ") = " + C + "\nT = " + lastT);
    }
}
