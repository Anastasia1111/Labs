package ru.labs.fnick;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public class DirectedGraph implements Graph
{
    private ArrayList<Edge> edges;
    private TreeSet<String> vertices;

    public DirectedGraph()
    {
        edges = new ArrayList<Edge>();
        vertices = new TreeSet<String>();
    }

    public DirectedGraph(ArrayList<Edge> edges)
    {
        this.edges = edges;
        Collections.sort(this.edges);

        vertices = new TreeSet<String>();
        for (Edge e : edges)
        {
            vertices.add(e.v1);
            vertices.add(e.v2);
        }
    }

    public static DirectedGraph fromVerticesArray(ArrayList<String> vertices)
    {
        DirectedGraph graph = new DirectedGraph();
        graph.vertices = new TreeSet<String>(vertices);
        return graph;
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
