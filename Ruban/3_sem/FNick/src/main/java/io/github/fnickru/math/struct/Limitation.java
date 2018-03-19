package io.github.fnickru.math.struct;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Limitation extends Function {

    public enum LimitationSign { LE, EQ, GE }

    private Fraction[] coefs;
    private LimitationSign sign;
    private Fraction freeTerm;

    public Limitation(Fraction[] coefs, LimitationSign sign, Fraction freeTerm) {
        this.coefs = coefs;
        this.sign = sign;
        this.freeTerm = freeTerm;
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

        switch(sign) {

            case LE:
                string += "<= ";
                break;

            case EQ:
                string += "= ";
                break;

            case GE:
                string += ">= ";
                break;

            default:
                break;
        }

        string += freeTerm;

        return string;
    }

    public Fraction getCoef(int variable) {
        if (variable < coefs.length)
            return coefs[variable];
        return Fraction.ZERO;
    }

    public Fraction[] getCoefs() {
        return coefs;
    }

    public int getLength() {
        return coefs.length;
    }

    public LimitationSign getSign() {
        return sign;
    }

    public Fraction getFreeTerm() {
        return freeTerm;
    }

    public static Limitation valueOf(String expression) {
        LimitationSign sign;

        if (expression.contains("<=")) {
            if (expression.contains(">="))
                throw new IllegalArgumentException("Incorrect limitation sign");
            sign = Limitation.LimitationSign.LE;
        } else if (expression.contains(">=")) {
            sign = Limitation.LimitationSign.GE;
        } else
            sign = Limitation.LimitationSign.EQ;

        if (!expression.contains("="))
            throw new IllegalArgumentException("Limitation sign is not specified");

        expression = expression.replaceAll("\\s|<|>", "");

        ArrayList<String> atoms = new ArrayList<>(Arrays.asList(expression.split("=|(?=\\+)|(?=\\-)")));
        Fraction freeTerm = new Fraction(atoms.remove(atoms.size() - 1));

        List<Fraction> coefs = parseAtoms(atoms);

        return new Limitation(coefs.toArray(new Fraction[coefs.size()]), sign, freeTerm);
    }

}