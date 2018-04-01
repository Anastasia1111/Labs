package io.github.fnickru.math.struct.simplex;

import io.github.fnickru.math.struct.Fraction;

import java.util.Arrays;
import java.util.List;

public class CostFunction extends Function {

    private Fraction[] coefs;
    private boolean minimize;

    private CostFunction(Fraction[] coefs, boolean minimize) {
        this.coefs = coefs;
        this.minimize = minimize;
    }

    Fraction getCoef(int variable) {
        if (variable < coefs.length)
            return coefs[variable];
        return Fraction.ZERO;
    }

    int getLength() {
        return coefs.length;
    }

    boolean shouldBeMinimized() {
        return minimize;
    }

    public static CostFunction valueOf(String expression) {
        expression = expression.replaceAll("\\s", "");

        if (!expression.contains("min") && !expression.contains("max"))
            throw new IllegalArgumentException("Optimization direction is not specified");
        if (expression.contains("min") && expression.contains("max"))
            throw new IllegalArgumentException("Multiple optimization directions are specified");
        boolean shouldBeMinimized = expression.contains("min");

        expression = expression.replaceAll("-->(max|min)", "");
        List<String> atoms = Arrays.asList(expression.split("(?=\\+)|(?=\\-)"));

        List<Fraction> coefs = parseAtoms(atoms);

        return new CostFunction(coefs.toArray(new Fraction[0]), shouldBeMinimized);
    }

    public String toString() {
        String string = "";

        int i = 0;
        while (coefs[i].equals(Fraction.ZERO))
            ++i;

        string += coefs[i] + "x" + i + " ";

        for (++i; i < coefs.length; ++i) {
            if (!coefs[i].equals(Fraction.ZERO)) {
                if (!coefs[i].isNegative())
                    string = string.concat("+ ");
                else
                    string = string.concat("- ");

                string = string.concat(coefs[i].abs() + "x" + i + " ");
            }
        }

        string += "--> " + (minimize ? "min" : "max");

        return string;
    }
}
