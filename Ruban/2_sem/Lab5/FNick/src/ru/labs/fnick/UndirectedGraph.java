package ru.labs.fnick;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public class UndirectedGraph implements Graph
{
    private ArrayList<Edge> edges;
    private TreeSet<String> vertices;

    public UndirectedGraph()
    {
        edges = new ArrayList<Edge>();
        vertices = new TreeSet<String>();
    }

    public UndirectedGraph(ArrayList<Edge> edges)
    {
        ArrayList<Edge> _edges = new ArrayList<Edge>();
        vertices = new TreeSet<String>();
        for (Edge e : edges)
        {
            int compare = e.v1.length() == e.v2.length() ? e.v1.compareTo(e.v2) : (e.v1.length() < e.v2.length() ? -1 : 1);
            String v1 = compare < 0 ? e.v1 : e.v2;
            String v2 = compare < 0 ? e.v2 : e.v1;
            _edges.add(new Edge(v1, v2, e.weight));
            vertices.add(e.v1);
            vertices.add(e.v2);
        }
        this.edges = _edges;
        Collections.sort(this.edges);
    }

    public int getWeight()
    {
        int weight = 0;
        for (Edge e : edges)
            weight += e.weight;
        return weight;
    }

    public ArrayList<Edge> getEdges()
    {
        ArrayList<Edge> _edges = new ArrayList<Edge>(edges);
        return _edges;
    }

    public boolean addEdge(Edge edge)
    {
        int compare = edge.v1.length() == edge.v2.length() ? edge.v1.compareTo(edge.v2) : (edge.v1.length() < edge.v2.length() ? -1 : 1);
        String v1 = compare < 0 ? edge.v1 : edge.v2;
        String v2 = compare < 0 ? edge.v2 : edge.v1;
        Edge e = new Edge(v1, v2, edge.weight);
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

    public ArrayList<String> getVertices()
    {
        ArrayList<String> _vertices = new ArrayList<String>(vertices);
        return _vertices;
    }

    public boolean addVertex(String vertex)
    {
        String v = vertex;
        return vertices.add(v);
    }

    public boolean removeVertex(String vertex)
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
        for (String v : vertices)
            vert_s += (v + " ");
        String edge_s = "Edges:\n";
        for (Edge e : edges)
            edge_s += (e + "\n");
        return vert_s + "\n" + edge_s;
    }
}
