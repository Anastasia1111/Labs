package io.github.fnickru.math.struct.simplex;

import io.github.fnickru.math.struct.Fraction;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

abstract class Function {

    static List<Fraction> parseAtoms(List<String> atoms) {
        atoms.removeAll(Arrays.asList("", null));
        List<Fraction> coefs = new ArrayList<>();
        for (String atom : atoms) {
            String[] pair = atom.split("x");
            if (pair[0].equals("+") || pair[0].equals("-") || pair[0].equals(""))
                pair[0] += "1";
            Fraction coef = new Fraction(pair[0]);
            int var = Integer.valueOf(pair[1]);
            while (var >= coefs.size())
                coefs.add(Fraction.ZERO);
            coefs.set(var, coef);
        }
        return coefs;
    }

}
