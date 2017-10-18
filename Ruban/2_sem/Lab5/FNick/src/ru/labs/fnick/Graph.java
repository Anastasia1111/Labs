package ru.labs.fnick;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public interface Graph {

    int getWeight();

    ArrayList<Edge> getEdges();

    boolean addEdge(Edge edge);

    boolean removeEdge(Edge edge);

    ArrayList<String> getVertices();

    boolean addVertex(String vertex);

    boolean removeVertex(String vertex);

    class Edge implements Comparable<Edge>
    {
        String v1;
        String v2;
        Integer weight;

        public Edge(String v1, String v2, Integer w)
        {
            this.v1 = v1;
            this.v2 = v2;
            weight = w;
        }

        public Edge(Edge e)
        {
            this.v1 = e.v1;
            this.v2 = e.v2;
            weight = e.weight;
        }

        @Override
        public int compareTo(Edge o)
        {
            int compareV1 = v1.length() == o.v1.length() ? v1.compareTo(o.v1) : (v1.length() < o.v1.length() ? -1 : 1);
            int compareV2 = v2.length() == o.v2.length() ? v2.compareTo(o.v2) : (v2.length() < o.v2.length() ? -1 : 1);
            int compareWeight = weight.compareTo(o.weight);
            return compareV1 == 0 ? ( compareV2 == 0 ? compareWeight : compareV2 ) : compareV1;
        }

        @Override
        public String toString()
        {
            return "(" + v1 + ")" + "---" + weight + "---" + "(" + v2 + ")";
        }

        @Override
        public boolean equals(Object obj)
        {
            if (obj instanceof Edge)
            {
                return (this.compareTo((Edge) obj) == 0);
            }
            return false;
        }
    }
}
