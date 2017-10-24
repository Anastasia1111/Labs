package ru.labs.fnick;

import java.util.*;

import org.graphstream.graph.Graph;
import org.graphstream.graph.Edge;
import org.graphstream.graph.Node;
import org.graphstream.graph.implementations.*;

public class GraphAdapter
{
    private DefaultGraph graph;
    private boolean directed;
    private static int count = 0;

    public GraphAdapter()
    {
        this(false);
    }

    public GraphAdapter(boolean isDirected)
    {
        directed = isDirected;
        String id = (directed ? "Directed " : "Undirected ") + "graph " + count;
        ++count;
        graph = new DefaultGraph(id, false, true);
    }

    public GraphAdapter(DefaultGraph graph)
    {
        this(graph, false);
    }

    public GraphAdapter(DefaultGraph graph, boolean isDirected)
    {
        directed = isDirected;
        ++count;
        graph.setStrict(false);
        graph.setAutoCreate(true);
        this.graph = graph;
    }

    public int getWeight()
    {
        int weight = 0;
        for (Edge e : graph.getEdgeSet())
            weight += (int) e.getAttribute("weight");
        return weight;
    }

    public boolean isDirected()
    {
        return directed;
    }

    public ArrayList<Edge> getEdges()
    {
        ArrayList<Edge> edges = new ArrayList<>();
        edges.addAll(graph.getEdgeSet());
        return edges;
    }

    public void addEdge(String from, String to, Integer weight)
    {
        String id, v1, v2;
        if (directed)
        {
            v1 = from;
            v2 = to;
        } else {
            int compare = from.length() == to.length() ? from.compareTo(to) : (from.length() < to.length() ? -1 : 1);
            v1 = compare < 0 ? from : to;
            v2 = compare < 0 ? to : from;
        }
        id = v1 + "to" + v2;
        Edge e = graph.addEdge(id, v1, v2, directed);
        e.addAttribute("weight", weight);
        e.addAttribute("ui.label", weight);
    }

    public void removeEdge(String from, String to)
    {
        graph.removeEdge(from, to);
    }

    public ArrayList<String> getVertices()
    {
        ArrayList<String> vertices = new ArrayList<>();
        for (Node v : graph.getNodeSet())
            vertices.add(v.toString());
        return vertices;
    }

    public void addVertex(String vertex)
    {
        graph.addNode(vertex);
    }

    public void removeVertex(String vertex)
    {
        graph.removeNode(vertex);
    }

    public void display()
    {
        for (Node v : graph.getNodeSet()) {
            v.addAttribute("ui.label", v.getId());
        }
        graph.addAttribute("ui.stylesheet","node {fill-color: gray;}");
        graph.display();
    }

    @Override
    public String toString()
    {
        String vert_s = "Vertices: ";
        TreeSet<String> vertices = new TreeSet<>();
        for (Node v : graph.getNodeSet())
            vertices.add(v.toString());
        for (String v : vertices)
            vert_s += (v + " ");
        String edge_s = "Edges:\n";
        ArrayList<Edge> edges = new ArrayList<>();
        edges.addAll(graph.getEdgeSet());
        Collections.sort(edges, new Comparator<Edge>() {
            @Override
            public int compare(Edge o1, Edge o2) {
                int compareV1 = o1.getNode0().toString().length() == o2.getNode0().toString().length()
                        ? o1.getNode0().toString().compareTo(o2.getNode0().toString())
                        : (o1.getNode0().toString().length() < o2.getNode0().toString().length() ? -1 : 1);
                int compareV2 = o1.getNode0().toString().length() == o2.getNode0().toString().length()
                        ? o1.getNode1().toString().compareTo(o2.getNode1().toString())
                        : (o1.getNode1().toString().length() < o2.getNode1().toString().length() ? -1 : 1);
                return compareV1 == 0 ? compareV2 : compareV1;
            }
        });
        for (Edge e : edges)
            edge_s += ("(" + e.getNode0() + ")--" + e.getAttribute("weight").toString() + "--(" + e.getNode1() + ")\n");
        return graph.getId() + ":\n" + vert_s + "\n" + edge_s;
    }
}
