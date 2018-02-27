package io.github.fnickru.math.labs;

import io.github.fnickru.math.util.Plotter;

public class Lab3 {

    public static void main(String[] args) {
        Plotter.addFunction("y=sin(x)", 0, 1080);
        Plotter.addFunction("y=cos(x)", 0, 1080);
        Plotter.addFunction("y=-sin(x)", 0, 1080);
        Plotter.addFunction("y=-cos(x)", 0, 1080);
        Plotter.show();
    }

}
