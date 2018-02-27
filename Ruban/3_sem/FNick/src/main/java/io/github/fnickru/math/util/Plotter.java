package io.github.fnickru.math.util;

import com.udojava.evalex.Expression;
import org.math.plot.Plot2DPanel;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public class Plotter {
    private static final double X_MAX = 10000;

    private static double step = 1;
    private static Plot2DPanel plot = new Plot2DPanel();
    private static JFrame frame = new JFrame("Plotter");

    /**
     * Метод отрисовки графика заданной функции
     * @param expression - матматическое выражение формата "y=expression(x)",
     *                   где expression(x) - любое корректное выражение с переменной х
     */
    public static void addFunction(String expression)
    {
        List<Double> x = new ArrayList<>();
        List<Double> y = new ArrayList<>();

        for (double i = 0; i <= X_MAX; i += step) {
            x.add(i);
            y.add(new Expression(expression.replaceFirst("y=", ""))
                    .with("x", Double.valueOf(i).toString()).eval().doubleValue());
        }

        double[] x_values = new double[x.size()];
        double[] y_values = new double[y.size()];
        for (int i = 0; i < x.size(); ++i)
        {
            x_values[i] = x.get(i);
            y_values[i] = y.get(i);
        }

        plot.addLinePlot(expression, x_values, y_values);
    }

    public static void show()
    {
        frame.setContentPane(plot);
        frame.setVisible(true);
    }

    public static void clear()
    {
        frame.setVisible(false);
        frame.setContentPane(null);
    }

    public static double getStep() {
        return step;
    }

    public static void setStep(int step) {
        Plotter.step = step;
    }
}
