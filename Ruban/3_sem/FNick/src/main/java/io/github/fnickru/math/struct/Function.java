package io.github.fnickru.math.struct;

import java.util.ArrayList;
import java.util.List;

abstract class Function {

    static List<Fraction> parseAtoms(List<String> atoms) {
        while (atoms.remove(""));
        List<Fraction> coefs = new ArrayList<>();
        for (String atom : atoms) {
            String[] pair = atom.replace("\\+", "").split("x");
            Fraction coef = new Fraction(pair[0]);
            int var = Integer.valueOf(pair[1]);
            while (var >= coefs.size())
                coefs.add(Fraction.ZERO);
            coefs.set(var, coef);
        }
        return coefs;
    }

}
