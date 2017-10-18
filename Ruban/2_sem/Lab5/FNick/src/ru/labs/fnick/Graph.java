package ru.labs.fnick;

import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public interface Graph {

    public int getWeight();

    public ArrayList<Edge> getEdges();

    public boolean addEdge(Edge edge);

    public boolean removeEdge(Edge edge);

    public ArrayList<String> getVertices();

    public boolean addVertex(String vertex);

    public boolean removeVertex(String vertex);

    public static class Edge implements Comparable<Edge>
    {
        String v1;
        String v2;
        Integer weight;

        public Edge(String v1, String v2, Integer w)
        {
            int compare = v1.compareTo(v2);
            this.v1 = compare < 0 ? v1 : v2;
            this.v2 = compare < 0 ? v2 : v1;
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
            int compareV1 = v1.compareTo(o.v1);
            int compareV2 = v2.compareTo(o.v2);
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
                return (this.compareTo((Edge)obj) == 0);
            }
            return false;
        }
    }
}
