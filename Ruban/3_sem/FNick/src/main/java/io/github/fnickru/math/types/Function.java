package io.github.fnickru.math.types;

import java.util.Arrays;

public class Function {
    private Fraction[] args;
    private boolean isLastFreeMember;

    public Function(Fraction... args) {
        this.isLastFreeMember = false;
        this.args = Arrays.copyOf(args, args.length);
    }

    public Function(Fraction[] args, boolean isLastFreeMember) {
        this.isLastFreeMember = isLastFreeMember;
        this.args = Arrays.copyOf(args, args.length);
    }

    public Function negate() {
        Fraction[] args = Arrays.copyOf(this.args, this.args.length);
        for (int i = 0; i < args.length; ++i) {
            args[i] = args[i].negate();
        }
        return new Function(args, isLastFreeMember);
    }

    public void setFactor(int i, Fraction factor) {
        args[i] = factor;
    }

    public Fraction getFreeMember() {
        return isLastFreeMember ? args[args.length - 1] : null;
    }

    public void setLastFreeMember(boolean lastFreeMember) {
        isLastFreeMember = lastFreeMember;
    }

    public boolean isLastFreeMember() {
        return isLastFreeMember;
    }

    public int length() {
        return isLastFreeMember ? args.length - 1 : args.length;
    }

    public Function resize(int size) {
        Fraction[] args = Arrays.copyOf(this.args, size);
        for (int i = 0; i < size; ++i)
            if (args[i] == null)
                args[i] = Fraction.ZERO;

        if (isLastFreeMember) {
            args[size - 1] = this.args[this.args.length - 1];
            args[this.args.length - 1] = Fraction.ZERO;
        }

        return new Function(args, isLastFreeMember);
    }

    @Override
    public String toString() {
        String str = "";
        int i = 0;

        if (isLastFreeMember) {
            while (i < (args.length - 1) && args[i].equals((Fraction.ZERO)))
                ++i;
            if (args[i].equals(Fraction.ONE) || args[i].negate().equals(Fraction.ONE))
                str = str.concat((args[i++].isNegative() ? "-" : "") + "x" + i);
            else
                str = str.concat(args[i++] + "x" + i);

            for (; i < (args.length - 1); ++i) {
                if (args[i].equals(Fraction.ZERO))
                    continue;
                if (args[i].equals(Fraction.ONE) || args[i].negate().equals(Fraction.ONE))
                    str = str.concat((args[i].isNegative() ? "-" : "+") + "x" + (i + 1));
                else
                    str = str.concat((args[i].isNegative() ? "" : "+") + args[i] + "x" + (i + 1));
            }

            str += "=" + args[args.length - 1];
        } else {
            while (i < args.length && args[i].equals((Fraction.ZERO)))
                ++i;
            if (args[i].equals(Fraction.ONE) || args[i].negate().equals(Fraction.ONE))
                str = str.concat((args[i++].isNegative() ? "-" : "") + "x" + i);
            else
                str = str.concat(args[i++] + "x" + i);

            for (; i < args.length; ++i) {
                if (args[i].equals(Fraction.ZERO))
                    continue;
                if (args[i].equals(Fraction.ONE) || args[i].negate().equals(Fraction.ONE))
                    str = str.concat((args[i].isNegative() ? "-" : "+") + "x" + (i + 1));
                else
                    str = str.concat((args[i].isNegative() ? "" : "+") + args[i] + "x" + (i + 1));
            }
        }
        return str;
    }
}
