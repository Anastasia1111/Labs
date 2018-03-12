package io.github.fnickru.math.types;

import java.util.Arrays;

public class Function {
    private Fraction[] args;

    Function(Fraction[] args) {
        this.args = Arrays.copyOf(args, args.length);
    }

    @Override
    public String toString() {
        String str = "";
        for (int i = 0; i < args.length; ++i) {
            if (args[i].equals(Fraction.ZERO))
                continue;
            if (args[i].equals(Fraction.ONE) || args[i].negate().equals(Fraction.ONE))
                str = str.concat((args[i].isNegative() ? "" : "+") + "x" + (i + 1));
            str = str.concat((args[i].isNegative() ? "" : "+") + args[i] + "x" + (i + 1));
        }
        return str;
    }
}
