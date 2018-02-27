package io.github.fnickru.math.util;

import com.udojava.evalex.Expression;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;
import org.knowm.xchart.XYChartBuilder;

public class Plotter {
    private static int precision = 100;
    private static XYChart chart = new XYChartBuilder()
            .width(800)
            .height(600)
            .title("Plotter")
            .xAxisTitle("X")
            .yAxisTitle("Y")
            .build();
    private static SwingWrapper<XYChart> wrapper = new SwingWrapper<>(chart);
    private static boolean isFirstDisplay = true;

    /**
     * Метод отрисовки графика заданной функции
     * @param expression - матматическое выражение формата "y=expression(x)",
     *                   где expression(x) - любое корректное выражение с переменной х
     */
    public static void addFunction(String expression)
    {
        addFunction(expression, 0, 100);
    }

    /**
     * Метод отрисовки графика заданной функции
     * @param expression - матматическое выражение формата "y=expression(x)",
     *                   где expression(x) - любое корректное выражение с переменной х
     * @param xmin - минимальное значение х на экране
     * @param xmax - максимальное значение х на экране
     */
    public static void addFunction(String expression, double xmin, double xmax)
    {
        double[] xData = new double[precision + 1];
        double[] yData = new double[precision + 1];

        for (int i = 0; i <= precision; ++i) {
            xData[i] = xmin + i * (xmax - xmin) / precision;
            yData[i] = new Expression(expression.replaceFirst("y=", ""))
                    .with("x", Double.valueOf(xData[i]).toString()).eval().doubleValue();
        }

        chart.addSeries(expression, xData, yData);
    }

    public static void show()
    {
        if (isFirstDisplay) {
            wrapper.displayChart();
            isFirstDisplay = false;
        } else {
            wrapper.repaintChart();
        }
    }

    public static void clear()
    {
        chart = new XYChartBuilder()
                .width(800)
                .height(600)
                .title("Plotter")
                .xAxisTitle("X")
                .yAxisTitle("Y")
                .build();
    }

    public static int getPrecision() {
        return precision;
    }

    public static void setPrecision(int precision) {
        Plotter.precision = precision;
    }
}
