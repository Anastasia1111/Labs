// Вариант 8 (Полный пребор и одновременное ветвление метода ветвей и границ

package ru.labs.fnick;

import java.util.ArrayList;
import java.util.Arrays;

public class TSP {
    static int T = 0;
    static Route bestRoute = new Route();
    final static int Infinity = Integer.MAX_VALUE;

    private static class Route
    {
        ArrayList<Integer> route;
        int lentgth;
        
        public Route()
        {
            route = new ArrayList<>();
            lentgth = 0;
        }
    }

    private static void bfRouteSearcher(int[][] c, Route r, ArrayList<Integer> verticesNotInRoute)
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

                bfRouteSearcher(c, newRoute, verticesNotInRoute);
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
        bestRoute = new Route();
        bestRoute.lentgth = Infinity;

        ArrayList<Integer> lst = new ArrayList<Integer>();
        for (int i = 2; i <= n; ++i)
            lst.add(i);
        Route route = new Route();
        route.route.add(1);

        bfRouteSearcher(c, route, lst);
    }

    public static void bnbRouteSearcher(int[][] c, Route r, ArrayList<Integer> verticesNotInRoute, int record)
    {
        int n = c.length;

        int firstIndex = r.route.get(0) - 1;
        int lastIndex = r.route.get(r.route.size() - 1) - 1;

        for(int i = 0; i<verticesNotInRoute.size(); ++i)
        {
            Integer justRemoved = (Integer) verticesNotInRoute.remove(0);
            Route newRoute = new Route();
            newRoute.route = (ArrayList<Integer>) r.route.clone();
            newRoute.route.add(justRemoved);

            if (c[lastIndex][justRemoved - 1] != Infinity)
            {
                newRoute.lentgth = r.lentgth + c[lastIndex][justRemoved - 1];

                int alpha, beta;
                int h = newRoute.lentgth;

                int[][] c_new = new int[n][n];
                for (int j = 0; j < n; ++j)
                    System.arraycopy(c[j], 0, c_new[j], 0, n);
                c_new[justRemoved - 1][firstIndex] = Infinity;

                for (Integer j = 0; j < n; ++j)
                {
                    boolean out = false;
                    if (r.route.contains(j + 1))
                        out = true;
                    if (!out)
                    {
                        alpha = Infinity;

                        for (Integer k = 0; k < n; ++k)
                        {
                            boolean in = false;
                            newRoute.route.remove(0);
                            if (newRoute.route.contains(k + 1))
                                in = true;
                            newRoute.route.add(0, firstIndex + 1);

                            if (!in)
                                alpha = Math.min(alpha, c_new[j][k]);
                        }

                        if (alpha != Infinity)
                            h += alpha;
                        else
                        {
                            h = Infinity;
                            break;
                        }

                        for (Integer k = 0; k < n; ++k)
                            if (c_new[j][k] != Infinity)
                                c_new[j][k] -= alpha;
                    }
                }

                for (Integer k = 0; k < n; ++k)
                {
                    boolean in = false;
                    newRoute.route.remove(0);
                    if (newRoute.route.contains(k + 1))
                        in = true;
                    newRoute.route.add(0, firstIndex + 1);
                    if (!in)
                    {
                        beta = Infinity;

                        for (Integer j = 0; j < n; ++j)
                        {
                            boolean out = false;
                            if (r.route.contains(j + 1))
                                out = true;

                            if (!out)
                                beta = Math.min(beta, c_new[j][k]);
                        }

                        if (beta != Infinity && h != Infinity)
                            h += beta;
                        else
                        {
                            h = Infinity;
                            break;
                        }
                    }
                }

                if (h < record)
                {
                    if (verticesNotInRoute.size() == 1)
                    {
                        Integer lastRemoved = (Integer) verticesNotInRoute.remove(0);
                        newRoute.route.add(lastRemoved);
                        newRoute.lentgth = h;
                        if (h < bestRoute.lentgth)
                            bestRoute = newRoute;
                        verticesNotInRoute.add(lastRemoved);

                        T += newRoute.route.size();
                    } else
                        bnbRouteSearcher(c, newRoute, verticesNotInRoute, record);
                } else
                    T += (newRoute.route.size() - 1);
            } else
                T += (newRoute.route.size() - 1);

            verticesNotInRoute.add(justRemoved);
        }
    }

    public static void branchNbound(int[][] c)
    {
        int n = c.length;

        bestRoute = new Route();
        bestRoute.route.add(1);
        Route route = new Route();
        route.route.add(1);

        ArrayList<Integer> lst = new ArrayList<Integer>();
        for (int i = 2; i <= n; ++i)
            lst.add(i);
        ArrayList<Integer> vertices = (ArrayList<Integer>) lst.clone();

        int lastVertex = 1;
        while (!lst.isEmpty())
        {
            Integer min = lst.get(0);
            for (Integer v : lst)
                if (c[lastVertex - 1][v - 1] < c[lastVertex - 1][min - 1])
                    min = v;
            bestRoute.route.add(min);
            if (bestRoute.lentgth != Infinity && c[lastVertex - 1][min - 1] != Infinity)
                bestRoute.lentgth += c[lastVertex - 1][min - 1];
            else
                bestRoute.lentgth = Infinity;
            lastVertex = min;
            lst.remove(min);
        }
        if (bestRoute.lentgth != Infinity && c[lastVertex - 1][0] != Infinity)
            bestRoute.lentgth += c[lastVertex - 1][0];
        else
            bestRoute.lentgth = Infinity;

        T = bestRoute.route.size();

        bnbRouteSearcher(c, route, vertices, bestRoute.lentgth);
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

        branchNbound(c);
        System.out.println("Best route: " + bestRoute.route.toString() + " for " + bestRoute.lentgth + "\nT = " + T);
    }
}
