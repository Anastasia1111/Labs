package ru.labs.fnick;

import org.graphstream.graph.Edge;

import java.util.*;

final public class GraphsUtil {
    public static long lastT = 0;

    private GraphsUtil(){}

    public static GraphAdapter spanningTree(GraphAdapter graph)
    {
        lastT = 0;

        ArrayList<Edge> edges = graph.getEdges();
        ArrayList<String> vertices = graph.getVertices();
        int k = edges.size();
        int n = vertices.size();
        HashMap<String, Integer> component = new HashMap<>();
        int i = 0;
        for (String v : vertices)
            component.put(v, ++i);
        int graphComponent = 0;

        GraphAdapter tree = new GraphAdapter(graph.isDirected());

        Collections.sort(edges, new Comparator<Edge>() {
            @Override
            public int compare(Edge o1, Edge o2) {
                return ((Integer)o1.getAttribute("weight")).compareTo(o2.getAttribute("weight"));
            }
        });
        lastT += k * (int) Math.ceil(Math.log(k)/Math.log(2));

        Edge edge = edges.get(0);
        component.replace(edge.getNode0().toString(), graphComponent);
        component.replace(edge.getNode1().toString(), graphComponent);
        lastT += 2;
        tree.addEdge(edge.getNode0().toString(), edge.getNode1().toString(), edge.getAttribute("weight"));
        edges.remove(0);
        while(tree.getEdges().size() != (n - 1))
        {
            if (edges.size() == 0)
                return null;
            edge = edges.get(0);
            int c1 = component.get(edge.getNode0().toString());
            int c2 = component.get(edge.getNode1().toString());
            if (c1 != c2)
            {
                int minComp = Math.min(c1, c2);
                for (Map.Entry<String, Integer> entry : component.entrySet())
                    if (entry.getValue().equals(c1 == minComp ? c2 : c1))
                    {
                        entry.setValue(minComp);
                        ++lastT;
                    }
                tree.addEdge(edge.getNode0().toString(), edge.getNode1().toString(), edge.getAttribute("weight"));
            }
            ++lastT;
            edges.remove(0);
        }
        return tree;
    }

    public static String[] shortestPathFB(GraphAdapter graph)
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
        if (graph.isDirected())
        {
            for (Edge e : graph.getEdges())
                C[vertices.indexOf(e.getNode0().toString())][vertices.indexOf(e.getNode1().toString())] = e.getAttribute("weight");
        } else {
            for (Edge e : graph.getEdges())
                C[vertices.indexOf(e.getNode0().toString())][vertices.indexOf(e.getNode1().toString())] = C[vertices.indexOf(e.getNode1().toString())][vertices.indexOf(e.getNode0().toString())] = e.getAttribute("weight");
        }

        int[] D = new int[n];
        String[] path = new String[n];
        path[0] = vertices.get(0);
        for (int i = 1; i < n; ++i)
        {
            D[i] = inf;
            path[i] = vertices.get(0);
        }
        int[] Dprev = D.clone();

        for (int l = 0; l < n; ++l)
        {
            lock = true;
            for (int i = 1; i < n; ++i)
            {
                int min = inf;
                int mini = -1;
                for (int j = 0; j < n; ++j)
                {
                    if (Dprev[j] != inf && C[j][i] != inf)
                    {
                        min = Math.min(min, Dprev[j] + C[j][i]);
                        if (min == Dprev[j] + C[j][i]) mini = j;
                    }
                    ++lastT;
                }
                if (D[i] != min)
                {
                    D[i] = min;
                    path[i] = path[mini] + "->" + vertices.get(i);
                    lock = false;
                }
            }
            Dprev = D.clone();
            if (lock) break;
        }
        for (int i = 0; i < n; ++i)
            path[i] += (" for " + D[i]);
        return path;
    }

    public static String[] shortestPathDijkstra(GraphAdapter graph)
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
        if (graph.isDirected())
        {
            for (Edge e : graph.getEdges())
                C[vertices.indexOf(e.getNode0().toString())][vertices.indexOf(e.getNode1().toString())] = e.getAttribute("weight");
        } else {
            for (Edge e : graph.getEdges())
                C[vertices.indexOf(e.getNode0().toString())][vertices.indexOf(e.getNode1().toString())] = C[vertices.indexOf(e.getNode1().toString())][vertices.indexOf(e.getNode0().toString())] = e.getAttribute("weight");
        }

        int[] D = new int[n];
        String[] path = new String[n];
        path[0] = vertices.get(0);
        for (int i = 1; i < n; ++i)
        {
            D[i] = C[0][i];
            path[i] = D[i] != inf ? vertices.get(0) + "->" + vertices.get(i) : "none";
        }

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
                {
                    D[i] = Math.min(D[i], D[j] + C[j][i]);
                    if (D[i] == D[j] + C[j][i]) path[i] = path[j] + "->" + vertices.get(i);
                }
                lastT += 2;
            }
        }
        for (int i = 0; i < n; ++i)
            path[i] += (D[i] != inf ? (" for " + D[i]) : "");
        return path;
    }

    public static void test()
    {
        boolean directed = false;
        GraphAdapter graph = new GraphAdapter(directed);
        /*graph.addEdge("1",  "2",  1);
        graph.addEdge("2",  "3",  1);
        graph.addEdge("3",  "7",  3);
        graph.addEdge("7",  "8",  1);
        graph.addEdge("8",  "9",  3);
        graph.addEdge("9",  "10",  5);
        graph.addEdge("10",  "4",  2);
        graph.addEdge("4",  "1",  1);
        graph.addEdge("1",  "5",  8);
        graph.addEdge("5",  "2",  4);
        graph.addEdge("2",  "6",  2);
        graph.addEdge("6",  "3",  1);
        graph.addEdge("6",  "7",  2);
        graph.addEdge("8",  "6",  1);
        graph.addEdge("6",  "9",  2);
        graph.addEdge("9",  "5",  1);
        graph.addEdge("5",  "10",  1);
        graph.addEdge("4",  "5",  7);
        graph.addEdge("5",  "6",  3);*/
        graph.addEdge("A", "B", 1);
        graph.addEdge("D", "A", 2);
        graph.addEdge("A", "G", 3);
        graph.addEdge("A", "F", 15);
        graph.addEdge("D", "B", 1);
        graph.addEdge("D", "C", 4);
        graph.addEdge("B", "C", 6);
        graph.addEdge("C", "F", 2);
        graph.addEdge("E", "F", 4);
        graph.addEdge("K", "F", 2);
        graph.addEdge("D", "E", 7);
        graph.addEdge("K", "E", 3);
        graph.addEdge("D", "K", 4);
        graph.addEdge("G", "K", 1);
        graph.addEdge("D", "G", 1);
        System.out.println("Graph:\n" + graph);
        graph.display();

        GraphAdapter tree = GraphsUtil.spanningTree(graph);
        if (tree == null)
        {
            System.out.println("Graph is disconnected");
        } else {
            System.out.println("Tree:\n" + tree + "Weight: " + tree.getWeight() + "\nT = " + lastT);
            tree.display();
        }

        String[] path = GraphsUtil.shortestPathFB(graph);
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