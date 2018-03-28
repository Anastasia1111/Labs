package io.github.fnickru.math.struct;

import java.math.BigInteger;
import java.util.Objects;

public class Fraction extends Number implements Comparable<Fraction> {

    private static final long serialVersionUID = 4096120349638112571L;
    private BigInteger numerator;
    private BigInteger denominator;

    public static final Fraction ZERO = new Fraction(BigInteger.ZERO);
    public static final Fraction ONE = new Fraction(BigInteger.ONE);
    public static final Fraction INFINITY = new Fraction(Long.MAX_VALUE);

    public Fraction(BigInteger numerator) {
        this.numerator = numerator;
        this.denominator = BigInteger.ONE;
    }

    public Fraction(long numerator) {
        this(BigInteger.valueOf(numerator));
    }

    public Fraction(double d)
    {
        this(d, 8);
    }

    public Fraction(double d, int precision)
    {
        if (precision <= 0)
            throw new IllegalArgumentException("Wrong precision!");
        if (Double.isInfinite(d))
            throw new IllegalArgumentException("Double value is infinite!");
        if (Double.isNaN(d))
            throw new IllegalArgumentException("Double value is NaN!");

        if(d == 0.0)
        {
            this.numerator = BigInteger.ZERO;
            this.denominator = BigInteger.ONE;
            return;
        }
        long denominator = (long) Math.pow(10, precision);
        long numerator = (long) (d * denominator);

        this.numerator = BigInteger.valueOf(numerator);
        this.denominator = BigInteger.valueOf(denominator);

        reduce();
    }

    public Fraction(BigInteger numerator, BigInteger denominator) {
        if(denominator.equals(BigInteger.ZERO)) {
            throw new IllegalArgumentException("Denominator is null!");
        }
        if(denominator.signum() == -1) {
            numerator = numerator.negate();
            denominator = denominator.negate();
        }
        this.numerator = numerator;
        this.denominator = denominator;

        reduce();
    }

    public Fraction(long numerator, long denominator) {
        if(denominator == 0) {
            throw new IllegalArgumentException("Denominator is null!");
        }
        if(denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
        this.numerator = BigInteger.valueOf(numerator);
        this.denominator = BigInteger.valueOf(denominator);

        reduce();
    }

    public Fraction(String value)
    {
        try {
            if (value.contains(".")) {
                double d = Double.valueOf(value);
                if(d == 0.0)
                {
                    this.numerator = BigInteger.ZERO;
                    this.denominator = BigInteger.ONE;
                    return;
                }
                long denominator = (long) Math.pow(10, 16);
                long numerator = (long) (d * denominator);

                this.numerator = BigInteger.valueOf(numerator);
                this.denominator = BigInteger.valueOf(denominator);

                reduce();
                return;
            }
            if (value.contains("/")) {
                String[] parts = value.split("/");
                this.numerator = new BigInteger(parts[0]);
                this.denominator = new BigInteger(parts[1]);

                reduce();
            } else {
                this.numerator = new BigInteger(value);
                this.denominator = BigInteger.ONE;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
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
        return numerator.doubleValue()/denominator.doubleValue();
    }

    public Fraction add(Fraction f) {
        return new Fraction(numerator.multiply(f.getDenominator()).add(denominator.multiply(f.getNumerator())), denominator.multiply(f.getDenominator()));
    }

    public Fraction subtract(Fraction f) {
        return new Fraction(numerator.multiply(f.getDenominator()).subtract(denominator.multiply(f.getNumerator())), denominator.multiply(f.getDenominator()));
    }

    public Fraction multiply(Fraction f) {
        return new Fraction(numerator.multiply(f.getNumerator()), denominator.multiply(f.getDenominator()));
    }

    public Fraction divide(Fraction f) {
        return new Fraction(numerator.multiply(f.getDenominator()), denominator.multiply(f.getNumerator()));
    }

    public Fraction abs() {
        return new Fraction(numerator.abs(), denominator);
    }

    public Fraction pow(int power) {
        return new Fraction(numerator.pow(power), denominator.pow(power));
    }

    public Fraction negate() {
        return new Fraction(numerator.negate(), denominator);
    }

    public Fraction invert() {
        return new Fraction(denominator, numerator);
    }

    public boolean isNegative() {
        return this.numerator.signum() == -1;
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
        if (denominator.equals(BigInteger.ONE))
            return numerator.toString();
        return numerator + "/" + denominator;
    }
}
