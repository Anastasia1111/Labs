// Вариант 8 (Полный пребор и одновременное ветвление метода ветвей и границ

package ru.labs.fnick;

import java.util.ArrayList;

public class TSP {
    static int T = 0;
    static Route bestRoute = new Route();
    final static int Infinity = Integer.MAX_VALUE;

    private static class Route
    {
        ArrayList<Integer> route;
        int lentgth = 0;
        
        public Route()
        {
            route = new ArrayList<>();
            lentgth = 0;
        }
    }

    private static void findBestRoute(int[][] c, Route r, ArrayList<Integer> verticesNotInRoute)
    {
        int firstIndex = r.route.get(0) - 1;
        int lastIndex = r.route.get(r.route.size() - 1) - 1;
        if(!verticesNotInRoute.isEmpty())
        {
            for(int i = 0; i<verticesNotInRoute.size(); ++i)
            {
                Integer justRemoved = (Integer) verticesNotInRoute.remove(0);
                Route newRoute = new Route();
                newRoute.route = (ArrayList<Integer>) r.route.clone();
                newRoute.route.add(justRemoved);
                if (c[lastIndex][justRemoved - 1] != Infinity && r.lentgth != Infinity)
                    newRoute.lentgth = r.lentgth + c[lastIndex][justRemoved - 1];
                else
                    newRoute.lentgth = Infinity;

                findBestRoute(c, newRoute, verticesNotInRoute);
                verticesNotInRoute.add(justRemoved);
            }
        }
        else
        {
            T += r.route.size();
            if (c[lastIndex][firstIndex] == Infinity || r.lentgth == Infinity)
                return;
            r.lentgth += c[lastIndex][firstIndex];
            if(r.lentgth < bestRoute.lentgth)
                bestRoute = r;
        }

    }

    public static void bruteforce(int[][] c)
    {
        T = 0;
        int n = c.length;
        bestRoute.lentgth = Infinity;
        ArrayList<Integer> lst = new ArrayList<Integer>();
        for (int i = 2; i <= n; ++i)
            lst.add(i);
        Route route = new Route();
        route.route.add(1);
        findBestRoute(c, route, lst);
    }

    public static void branchNbound(int[][] c)
    {
        int n = c.length;
        int[] di = new int[n];
        int[] dj = new int[n];
        for (int i = 0; i < n; ++i)
        {
            di[i] = Infinity;
            for (int j = 0; j < n; ++j)
                di[i] = Math.min(di[i], c[i][j]);
            for (int j = 0; j < n; ++j)
                c[i][j] -= di[i];
        }
        for (int j = 0; j < n; ++j)
        {
            dj[j] = Infinity;
            for (int i = 0; i < n; ++i)
                dj[j] = Math.min(dj[j], c[i][j]);
            for (int i = 0; i < n; ++i)
                c[i][j] -= dj[j];
        }
        int dSum = 0;
        for (int i = 0; i < n; ++i)
            dSum += (di[i] + dj[i]);
        int newMi, newMj, newM = -1;
        for (int i = 0; i < n; ++i)
        {
            di[i] = Infinity;
            dj[i] = Infinity;
            for (int j = 0; j < n; ++j)
            {
                if (c[i][j] != 0) di[i] = Math.min(di[i], c[i][j]);
                if (c[j][i] != 0) dj[j] = Math.min(dj[j], c[j][i]);
            }
            for (int j = 0; j < n; ++j)
            {
                if (c[i][j] == 0 && (di[i] + dj[j]) > newM)
                {
                    newMi = i;
                    newMj = j;
                    newM = di[i] + dj[j];
                }
            }
        }
    }

    public static void main(String[] args)
    {
        int b = Infinity;
        int[][] c = {{b, 13, 7, 5, 2, 9},
                     {8, b, 4, 7, 5, b},
                     {8, 4, b, 3, 6, 2},
                     {5, 8, 1, b, 0, 1},
                     {b, 6, 1, 4, b, b},
                     {0, 0, b, 3, 7, b}};
        bruteforce(c);
        System.out.println("Best route: " + bestRoute.route.toString() + " for " + bestRoute.lentgth + "\nT = " + T);
    }
}
