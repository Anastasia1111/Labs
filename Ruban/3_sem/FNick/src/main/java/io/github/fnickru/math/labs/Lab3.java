package io.github.fnickru.math.labs;

import org.knowm.xchart.QuickChart;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;

public class Lab3 {

    private static final int size = 10;

    public static void main(String[] args) {
        double[] xData = new double[size*2 + 1];
        double[] yData = new double[size*2 + 1];;

        for (int i = -size; i <= size; ++i) {
            xData[i + size] = i;
            yData[i + size] = i * i;
        }

        XYChart chart = QuickChart.getChart("Plot", "X", "Y", "y=x^2", xData, yData);
        new SwingWrapper(chart).displayChart();
    }

}
