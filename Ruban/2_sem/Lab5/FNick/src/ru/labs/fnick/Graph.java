package ru.labs.fnick;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public interface Graph {

    public int getWeight();

    public ArrayList<Edge> getEdges();

    public boolean addEdge(Edge edge);

    public boolean removeEdge(Edge edge);

    public ArrayList<Integer> getVertices();

    public boolean addVertex(Integer vertex);

    public boolean removeVertex(Integer vertex);

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
