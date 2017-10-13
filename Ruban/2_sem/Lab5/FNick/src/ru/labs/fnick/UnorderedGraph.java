package ru.labs.fnick;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public class UnorderedGraph {
    private ArrayList<Edge> edges;
    private TreeSet<Integer> vertices;

    public UnorderedGraph()
    {
        edges = new ArrayList<Edge>();
        vertices = new TreeSet<Integer>();
    }

    public UnorderedGraph(ArrayList<Edge> edges)
    {
        this.edges = new ArrayList<Edge>(edges);
        Collections.sort(this.edges);
        vertices = new TreeSet<Integer>();
        for (Edge e : edges)
        {
            vertices.add(e.v1);
            vertices.add(e.v2);
        }
    }

    public static UnorderedGraph fromVerticesArray(ArrayList<Integer> vertices)
    {
        UnorderedGraph graph = new UnorderedGraph();
        graph.vertices = new TreeSet<Integer>(vertices);
        return graph;
    }

    public ArrayList<Edge> getEdges()
    {
        ArrayList<Edge> _edges = new ArrayList<Edge>(edges);
        return _edges;
    }

    public boolean addEdge(Edge edge)
    {
        Edge e = new Edge(edge);
        vertices.add(edge.v1);
        vertices.add(edge.v2);
        boolean suc = edges.add(e);
        Collections.sort(this.edges);
        return suc;
    }

    public boolean removeEdge(Edge edge)
    {
        return edges.remove(edge);
    }

    public ArrayList<Integer> getVertices()
    {
        ArrayList<Integer> _vertices = new ArrayList<Integer>(vertices);
        return _vertices;
    }

    public boolean addVertex(Integer vertex)
    {
        Integer v = new Integer(vertex);
        return vertices.add(v);
    }

    public boolean removeVertex(Integer vertex)
    {
        for (Edge e : edges)
            if (e.v1 == vertex || e.v2 == vertex)
                removeEdge(e);
        return vertices.remove(vertex);
    }

    @Override
    public String toString()
    {
        String vert_s = "Vertices: ";
        for (Integer v : vertices)
            vert_s += (v + " ");
        String edge_s = "Edges:\n";
        for (Edge e : edges)
            edge_s += (e + "\n");
        return vert_s + "\n" + edge_s;
    }

    public static class Edge implements Comparable<Edge>
    {
        Integer v1;
        Integer v2;
        Integer weight;

        public Edge(int v1, int v2, int w)
        {
            this.v1 = Math.min(v1, v2);
            this.v2 = Math.max(v1, v2);
            weight = w;
        }

        public Edge(Edge e)
        {
            this.v1 = e.v1;
            this.v2 = e.v2;
            weight = e.weight;
        }

        @Override
        public int compareTo(Edge o) {
            return v1.compareTo(o.v1);
        }

        @Override
        public String toString()
        {
            return new String("(" + v1 + ")" + "---" + weight + "---" + "(" + v2 + ")");
        }

        @Override
        public boolean equals(Object obj)
        {
            if (obj instanceof Edge)
            {
                return v1 == ((Edge)obj).v1 && v2 == ((Edge)obj).v2 && weight == ((Edge)obj).weight;
            }
            return false;
        }
    }
}
