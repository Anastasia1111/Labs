package io.github.fnickru.math.labs;

import io.github.fnickru.math.util.Plotter;

public class Graph {

    public static void main(String[] args) {
        Plotter.addFunction("y=sin(x)");
        Plotter.addFunction("y=cos(x)");
        Plotter.addFunction("y=-sin(x)");
        Plotter.addFunction("y=-cos(x)");
        Plotter.show();
    }

}
