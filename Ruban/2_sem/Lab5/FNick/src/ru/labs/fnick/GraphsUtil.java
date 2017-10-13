package ru.labs.fnick;

import com.sun.corba.se.impl.orbutil.graph.Graph;

import java.util.*;

final public class GraphsUtil {
    public static long lastT = 0;

    private GraphsUtil(){}

    public static UnorderedGraph spanningTree(UnorderedGraph graph)
    {
        lastT = 0;

        ArrayList<UnorderedGraph.Edge> edges = graph.getEdges();
        ArrayList<Integer> vertices = graph.getVertices();
        int k = edges.size();
        int n = vertices.size();
        HashMap<Integer, Integer> component = new HashMap<Integer, Integer>();
        for (Integer v : vertices)
            component.put(v, v);

        UnorderedGraph tree = UnorderedGraph.fromVerticesArray(vertices);

        Collections.sort(edges, new Comparator<UnorderedGraph.Edge>() {
            @Override
            public int compare(UnorderedGraph.Edge o1, UnorderedGraph.Edge o2) {
                return o1.weight.compareTo(o2.weight);
            }
        });
        lastT += k * (int) Math.ceil(Math.log(k)/Math.log(2));

        int graphComponent = 0;
        for (Integer c : component.keySet())
            graphComponent = Math.min(graphComponent, c);
        --graphComponent;

        UnorderedGraph.Edge edge = edges.get(0);
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
    }

    public static void test()
    {
        ArrayList<UnorderedGraph.Edge> edges = new ArrayList<UnorderedGraph.Edge>();
        edges.add(new UnorderedGraph.Edge(1, 2, 20));
        edges.add(new UnorderedGraph.Edge(6, 1, 23));
        edges.add(new UnorderedGraph.Edge(5, 6, 28));
        edges.add(new UnorderedGraph.Edge(7, 5, 25));
        edges.add(new UnorderedGraph.Edge(6, 7, 36));
        edges.add(new UnorderedGraph.Edge(3, 2, 5));
        edges.add(new UnorderedGraph.Edge(3, 7, 9));
        edges.add(new UnorderedGraph.Edge(4, 3, 3));
        edges.add(new UnorderedGraph.Edge(1, 7, 1));
        edges.add(new UnorderedGraph.Edge(7, 2, 4));
        edges.add(new UnorderedGraph.Edge(4, 7, 16));
        edges.add(new UnorderedGraph.Edge(5, 4, 17));
        /*edges.add(new UnorderedGraph.Edge(1, 8, 4));
        edges.add(new UnorderedGraph.Edge(2, 3, 1));
        edges.add(new UnorderedGraph.Edge(3, 6, 7));
        edges.add(new UnorderedGraph.Edge(8, 7, 3));
        edges.add(new UnorderedGraph.Edge(7, 6, 5));
        edges.add(new UnorderedGraph.Edge(4, 5, 6));
        edges.add(new UnorderedGraph.Edge(6, 5, 2));*/
        UnorderedGraph graph = new UnorderedGraph(edges);

        System.out.println("Graph:\n" + graph);
        UnorderedGraph tree = GraphsUtil.spanningTree(graph);
        if (tree == null)
            System.out.println("Graph is disconnected");
        else
            System.out.println("Tree:\n" + tree + "T = " + lastT);
    }
}
