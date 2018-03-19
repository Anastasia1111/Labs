package io.github.fnickru.math.struct;

import java.util.ArrayList;
import java.util.List;

abstract class Function {

    static List<Fraction> parseAtoms(List<String> atoms) {
        List<Fraction> coefs = new ArrayList<>();
        for (String atom : atoms) {
            String[] pair = atom.replace("\\+", "").split("x");
            Fraction coef = new Fraction(pair[0]);
            int var = Integer.valueOf(pair[1]);
            coefs.add(var, coef);
        }
        return coefs;
    }

}
