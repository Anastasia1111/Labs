package ru.labs.fnick;

import java.util.*;

final public class Dynamic {
    public static long lastT = 0;

    private Dynamic(){}

    public static String knapsack(int[] m, int[] c, int M)
    {
        lastT = 0;
        int n = c.length;

        ArrayList<AbstractMap.SimpleEntry<Integer, Integer>> items = new ArrayList<>();
        for (int i = 0; i < n; ++i)
            items.add(new AbstractMap.SimpleEntry<>(m[i], c[i]));
        Collections.sort(items, new Comparator<AbstractMap.SimpleEntry<Integer, Integer>>() {
            @Override
            public int compare(AbstractMap.SimpleEntry<Integer, Integer> o1, AbstractMap.SimpleEntry<Integer, Integer> o2) {
                return o1.getKey().compareTo(o2.getKey());
            }
        });

        int[] f = new int[M + 1];
        String[] set = new String[M + 1];
        for (int i = 0; i <= M; ++i)
        {
            f[i] = 0;
            set[i] = "Knapsack:[";
            int maxj = -1;
            for (int j = 0; j < n; ++j)
            {
                int mj = items.get(j).getKey();
                int cj = items.get(j).getValue();
                if (i - mj < 0) break;
                f[i] = Math.max(f[i], f[i - mj] + cj);
                if (f[i] == (f[i - mj] + cj)) maxj = j;
                ++lastT;
            }
            if (maxj != -1) set[i] = set[i - items.get(maxj).getKey()] + items.get(maxj).getKey() + "(" + items.get(maxj).getValue() + ") ";
        }
        set[M] = set[M].trim() + "] C = " + f[M];

        return set[M];
    }

    public static String matrix(int[] r)
    {
        lastT = 0;
        int n = r.length - 1;
        int[][] f = new int[n + 1][n + 1];
        String[][] bkt = new String[n + 1][n + 1];
        for (int i = 1; i <= n; ++i)
        {
            f[i][i] = 0;
            bkt[i][i] = ("M" + i);
        }
        for (int t = 1; t < n; ++t)
            for (int k = 1; k <= (n - t); ++k)
            {
                int min = Integer.MAX_VALUE;
                int minj = 0;
                for (int j = k; j < (k + t); ++j)
                {
                    int prevmin = min;
                    min = Math.min(min, f[k][j] + f[j + 1][k + t] + r[k - 1] * r[j] * r[k + t]);
                    if (min != prevmin) minj = j;
                    ++lastT;
                }
                bkt[k][k + t] = "(" + bkt[k][minj] + ")(" + bkt[minj + 1][k + t] + ")";
                f[k][k + t] = min;
            }
        bkt[1][n] += (" for " + f[1][n]);
        return bkt[1][n];
    }

    public static void test()
    {
        /*int[] m = {10, 100, 55, 4};
        int[] c = {15, 400, 300, 5};
        int M = 100;
        System.out.println("F(" + M + ") : " + Dynamic.knapsack(m, c, M) + "\nT = " + lastT);*/

        int[] r = {30, 40, 100, 1, 45, 37};
        System.out.println(matrix(r) + "\nT = " + lastT);
    }
}
