package ru.labs.fnick;

import java.util.*;

final public class GraphsUtil {
    public static long lastT = 0;

    private GraphsUtil(){}

    /*public static UndirectedGraph spanningTree(UndirectedGraph graph)
    {
        lastT = 0;

        ArrayList<UndirectedGraph.Edge> edges = graph.getEdges();
        ArrayList<String> vertices = graph.getVertices();
        int k = edges.size();
        int n = vertices.size();
        HashMap<String, String> component = new HashMap<String, String>();
        for (String v : vertices)
            component.put(v, v);

        UndirectedGraph tree = UndirectedGraph.fromVerticesArray(vertices);

        Collections.sort(edges, new Comparator<UndirectedGraph.Edge>() {
            @Override
            public int compare(UndirectedGraph.Edge o1, UndirectedGraph.Edge o2) {
                return o1.weight.compareTo(o2.weight);
            }
        });
        lastT += k * (int) Math.ceil(Math.log(k)/Math.log(2));

        int graphComponent = 0;
        for (String c : component.keySet())
            graphComponent = Math.min(graphComponent, c);
        --graphComponent;

        UndirectedGraph.Edge edge = edges.get(0);
        component.replace(edge.v1, graphComponent);
        component.replace(edge.v2, graphComponent);
        lastT += 2;
        tree.addEdge(edge);
        edges.remove(0);
        while(tree.getEdges().size() != (n - 1))
        {
            if (edges.size() == 0)
                return null;
            edge = edges.get(0);
            int c1 = component.get(edge.v1);
            int c2 = component.get(edge.v2);
            if (c1 != c2)
            {
                int minComp = Math.min(c1, c2);
                for (Map.Entry<Integer, Integer> entry : component.entrySet())
                    if (entry.getValue().equals(c1 == minComp ? c2 : c1))
                    {
                        entry.setValue(minComp);
                        ++lastT;
                    }
                tree.addEdge(edge);
            }
            ++lastT;
            edges.remove(0);
        }
        return tree;
    }*/

    public static int[] shortestPathFB(UndirectedGraph graph)
    {
        lastT = 0;
        boolean lock = false;
        ArrayList<String> vertices = graph.getVertices();
        int n = vertices.size();
        int inf = Integer.MAX_VALUE;

        int[][] C = new int[n][n];
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                C[i][j] = inf;
            C[i][i] = 0;
        }
        for (UndirectedGraph.Edge e : graph.getEdges())
            C[vertices.indexOf(e.v1)][vertices.indexOf(e.v2)] = C[vertices.indexOf(e.v2)][vertices.indexOf(e.v1)] = e.weight;

        int[] D = new int[n];
        for (int i = 1; i < n; ++i)
            D[i] = inf;
        int[] Dprev = D.clone();

        for (int l = 0; l < n; ++l)
        {
            lock = true;
            for (int i = 1; i < n; ++i)
            {
                int min = inf;
                for (int j = 0; j < n; ++j)
                {
                    if (Dprev[j] != inf && C[j][i] != inf)
                        min = Math.min(min, Dprev[j] + C[j][i]);
                    ++lastT;
                }
                if (D[i] != min)
                {
                    D[i] = min;
                    lock = false;
                }
            }
            Dprev = D.clone();
            if (lock) break;
        }
        return D;
    }

    public static int[] shortestPathDijkstra(UndirectedGraph graph)
    {
        lastT = 0;
        ArrayList<String> V = graph.getVertices();
        ArrayList<String> vertices = graph.getVertices();
        int n = vertices.size();
        int inf = Integer.MAX_VALUE;

        int[][] C = new int[n][n];
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                C[i][j] = inf;
            C[i][i] = 0;
        }
        for (UndirectedGraph.Edge e : graph.getEdges())
            C[vertices.indexOf(e.v1)][vertices.indexOf(e.v2)] = C[vertices.indexOf(e.v2)][vertices.indexOf(e.v1)] = e.weight;

        int[] D = new int[n];
        for (int i = 1; i < n; ++i)
            D[i] = C[0][i];

        ArrayList<String> S = new ArrayList<String>();
        S.add(V.get(0));
        V.remove(0);

        while (S.size() != n)
        {
            String w = V.get(0);
            for (String v : V)
                if (D[vertices.indexOf(w)] > D[vertices.indexOf(v)]) w = v;
            S.add(w);
            V.remove(w);

            for (String v : V)
            {
                int i = vertices.indexOf(v);
                int j = vertices.indexOf(w);
                if (D[j] != inf && C[j][i] != inf)
                    D[i] = Math.min(D[i], D[j] + C[j][i]);
                lastT += 2;
            }
        }
        return D;
    }

    public static void test()
    {
        ArrayList<UndirectedGraph.Edge> edges = new ArrayList<UndirectedGraph.Edge>();
        /*edges.add(new UndirectedGraph.Edge(1, 2, 20));
        edges.add(new UndirectedGraph.Edge(6, 1, 23));
        edges.add(new UndirectedGraph.Edge(5, 6, 28));
        edges.add(new UndirectedGraph.Edge(7, 5, 25));
        edges.add(new UndirectedGraph.Edge(6, 7, 36));
        edges.add(new UndirectedGraph.Edge(3, 2, 5));
        edges.add(new UndirectedGraph.Edge(3, 7, 9));
        edges.add(new UndirectedGraph.Edge(4, 3, 3));
        edges.add(new UndirectedGraph.Edge(1, 7, 1));
        edges.add(new UndirectedGraph.Edge(7, 2, 4));
        edges.add(new UndirectedGraph.Edge(4, 7, 16));
        edges.add(new UndirectedGraph.Edge(5, 4, 17));*/
        /*edges.add(new UndirectedGraph.Edge(0, 4, 2));
        edges.add(new UndirectedGraph.Edge(0, 3, 7));
        edges.add(new UndirectedGraph.Edge(0, 2, 15));
        edges.add(new UndirectedGraph.Edge(0, 1, 25));
        edges.add(new UndirectedGraph.Edge(1, 2, 6));
        edges.add(new UndirectedGraph.Edge(4, 3, 3));
        edges.add(new UndirectedGraph.Edge(2, 3, 4));*/
        edges.add(new UndirectedGraph.Edge("1",  "2",  1));
        edges.add(new UndirectedGraph.Edge("2",  "3",  1));
        edges.add(new UndirectedGraph.Edge("3",  "7",  3));
        edges.add(new UndirectedGraph.Edge("7",  "8",  1));
        edges.add(new UndirectedGraph.Edge("8",  "9",  3));
        edges.add(new UndirectedGraph.Edge("9",  "10",  5));
        edges.add(new UndirectedGraph.Edge("10",  "4",  2));
        edges.add(new UndirectedGraph.Edge("4",  "1",  1));
        edges.add(new UndirectedGraph.Edge("1",  "5",  8));
        edges.add(new UndirectedGraph.Edge("5",  "2",  4));
        edges.add(new UndirectedGraph.Edge("2",  "6",  2));
        edges.add(new UndirectedGraph.Edge("6",  "3",  1));
        edges.add(new UndirectedGraph.Edge("6",  "7",  2));
        edges.add(new UndirectedGraph.Edge("8",  "6",  1));
        edges.add(new UndirectedGraph.Edge("6",  "9",  2));
        edges.add(new UndirectedGraph.Edge("9",  "5",  1));
        edges.add(new UndirectedGraph.Edge("5",  "10",  1));
        edges.add(new UndirectedGraph.Edge("4",  "5",  7));
        edges.add(new UndirectedGraph.Edge("5",  "6",  3));
        UndirectedGraph graph = new UndirectedGraph(edges);
        System.out.println("Graph:\n" + graph);

        /*UndirectedGraph tree = GraphsUtil.spanningTree(graph);
        if (tree == null)
            System.out.println("Graph is disconnected");
        else
            System.out.println("Tree:\n" + tree + "Weight: " + tree.getWeight() + "\nT = " + lastT);*/

        int[] path = GraphsUtil.shortestPathFB(graph);
        int index = 0;
        System.out.println("Shortest path from " + graph.getVertices().get(0) + ":");
        for (String v : graph.getVertices())
            System.out.println("to " + v + ": " + path[index++]);
        System.out.println("T = " + lastT + " (by Bellman–Ford algorithm)");

        path = GraphsUtil.shortestPathDijkstra(graph);
        index = 0;
        System.out.println("Shortest path from " + graph.getVertices().get(0) + ":");
        for (String v : graph.getVertices())
            System.out.println("to " + v + ": " + path[index++]);
        System.out.println("T = " + lastT + " (by Dijkstra’s algorithm)");
    }
}