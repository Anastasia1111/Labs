package io.github.fnickru.math.types;

import java.math.BigInteger;
import java.util.Objects;

public class Fraction extends Number implements Comparable<Fraction> {

    private static final long serialVersionUID = 4096120349638112571L;
    private BigInteger numerator;
    private BigInteger denominator;

    public static final Fraction ZERO = new Fraction(BigInteger.ZERO);
    public static final Fraction ONE = new Fraction(BigInteger.ONE);
    public static final Fraction TENTH = new Fraction(BigInteger.ONE, BigInteger.TEN);

    public Fraction(BigInteger numerator) {
        this.numerator = numerator;
        this.denominator = BigInteger.ONE;
    }

    public Fraction(BigInteger numerator, BigInteger denominator) {
        if(denominator.equals(BigInteger.ZERO)) {
            throw new IllegalArgumentException("Denominator is null!");
        }
        if(denominator.signum() == -1) {
            numerator.negate();
            denominator.negate();
        }
        this.numerator = numerator;
        this.denominator = denominator;

        reduce();
    }

    /**
     * Constructs a BigFraction from a floating-point number.
     *
     * @author Kip Robinson, <a href="https://github.com/kiprobinson">https://github.com/kiprobinson</a>
     */
    public Fraction(double d)
    {
        if(Double.isInfinite(d))
            throw new IllegalArgumentException("Double value is infinite");
        if(Double.isNaN(d))
            throw new IllegalArgumentException("Double value is NaN");

        if(d == 0.0)
        {
            this.numerator = BigInteger.ZERO;
            this.denominator = BigInteger.ONE;
            return;
        }

        final int sign = (int)((Double.doubleToRawLongBits(d) & 0x8000000000000000L) >>> 63);
        final int exponent = (int)((Double.doubleToRawLongBits(d) & 0x7ff0000000000000L) >>> 52) - 0x3ff;
        final long mantissa = Double.doubleToRawLongBits(d) & 0xfffffffffffffL;
        final boolean isSubnormal = ((Double.doubleToRawLongBits(d) & 0x7ff0000000000000L) == 0) && ((Double.doubleToRawLongBits(d) & 0xfffffffffffffL) != 0);

        BigInteger tmpNumerator = BigInteger.valueOf((isSubnormal ? 0L : 0x10000000000000L) + mantissa);
        BigInteger tmpDenominator = BigInteger.ONE;

        if(exponent > 52)
        {
            tmpNumerator = tmpNumerator.shiftLeft(exponent - 52);
        }
        else if (exponent < 52)
        {
            if(!isSubnormal)
            {
                int y = Math.min(tmpNumerator.getLowestSetBit(), 52 - exponent);

                tmpNumerator = tmpNumerator.shiftRight(y);
                tmpDenominator = tmpDenominator.shiftLeft(52 - exponent - y);
            }
            else
            {
                int y = Math.min(tmpNumerator.getLowestSetBit(), 1074);

                tmpNumerator = tmpNumerator.shiftRight(y);
                tmpDenominator = tmpDenominator.shiftLeft(1074 - y);
            }
        }

        if(sign != 0)
            tmpNumerator = tmpNumerator.negate();

        this.numerator = tmpNumerator;
        this.denominator = tmpDenominator;
    }

    private void reduce() {
        BigInteger gcd = numerator.gcd(denominator);
        numerator = numerator.divide(gcd);
        denominator = denominator.divide(gcd);
    }

    public BigInteger getNumerator() {
        return numerator;
    }

    public BigInteger getDenominator() {
        return denominator;
    }

    @Override
    public byte byteValue() {
        return (byte) this.doubleValue();
    }

    @Override
    public short shortValue() {
        return (short) this.doubleValue();
    }

    @Override
    public int intValue() {
        return (int) this.doubleValue();
    }

    @Override
    public long longValue() {
        return (long) this.doubleValue();
    }

    @Override
    public float floatValue() {
        return (float) this.doubleValue();
    }

    @Override
    public double doubleValue() {
        return numerator.divide(denominator).doubleValue();
    }

    public Fraction add(Fraction f){
        return new Fraction(numerator.multiply(f.getDenominator()).add(denominator.multiply(f.getNumerator())), denominator.multiply(f.getDenominator()));
    }

    public Fraction substract(Fraction f){
        return new Fraction(numerator.multiply(f.getDenominator()).subtract(denominator.multiply(f.getNumerator())), denominator.multiply(f.getDenominator()));
    }

    public Fraction multiply(Fraction f){
        return new Fraction(numerator.multiply(f.getNumerator()), denominator.multiply(f.getDenominator()));
    }

    public Fraction divide(Fraction f){
        return new Fraction(numerator.multiply(f.getDenominator()), denominator.multiply(f.getNumerator()));
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Fraction fraction = (Fraction) o;
        return Objects.equals(numerator, fraction.numerator) &&
                Objects.equals(denominator, fraction.denominator);
    }

    @Override
    public int hashCode() {
        return Objects.hash(numerator, denominator);
    }

    @Override
    public int compareTo(Fraction fraction) {
        return numerator.multiply(fraction.getDenominator()).compareTo(denominator.multiply(fraction.getNumerator()));
    }

    @Override
    public String toString() {
        return numerator + "/" + denominator;
    }
}
