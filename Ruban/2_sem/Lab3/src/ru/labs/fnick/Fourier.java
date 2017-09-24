package ru.labs.fnick;

import edu.pronceton.cs.introcs.java.class32.Complex;

import java.time.Clock;
import java.time.Instant;
import java.time.ZoneId;

public class Fourier {
    public static int lastT = 0;

    public static void DFT(Complex[] f, Complex[] a)
    {
        lastT = 0;
        int n = f.length;
        for (int k = 0; k < n; k++)
        {
            a[k] = new Complex(0, 0);
            for (int j = 0; j < n; ++j)
            {
                Complex exp = new Complex(0, -2.0 * k * j * Math.PI / n);
                exp = exp.exp();
                a[k] = Complex.plus(a[k], exp.times(f[j]));
                lastT += 5;
            }
            a[k] = a[k].scale(1.0 / n);
        }
    }

    public static void SFFT(Complex[] f, Complex[] a)
    {
        lastT = 0;
        int n = f.length;
        int p1 = (int) Math.sqrt(n * 1.0);
        int p2;
        while (n % p1 != 0)
            --p1;
        p2 = n / p1;

        Complex[][] a1 = new Complex[p1][p2];
        for (int k1 = 0; k1 < p1; ++k1)
        {
            for (int j2 = 0; j2 < p2; ++j2)
            {
                a1[k1][j2] = new Complex(0, 0);
                for (int j1 = 0; j1 < p1; ++j1)
                {
                    Complex exp = new Complex(0, -2.0 * k1 * j1 * Math.PI / p1);
                    exp = exp.exp();
                    a1[k1][j2] = Complex.plus(a1[k1][j2], exp.times(f[j2 + p2 * j1]));
                    lastT += 5;
                }
                a1[k1][j2] = a1[k1][j2].scale(1.0 / p1);
            }
        }

        Complex[][] a2 = new Complex[p1][p2];
        for (int k1 = 0; k1 < p1; ++k1)
        {
            for (int k2 = 0; k2 < p2; ++k2)
            {
                a2[k1][k2] = new Complex(0, 0);
                for (int j2 = 0; j2 < p2; ++j2)
                {
                    Complex exp = new Complex(0, -2.0 * (k1 + p1 * k2) * j2 * Math.PI / n);
                    exp = exp.exp();
                    a2[k1][k2] = Complex.plus(a2[k1][k2], exp.times(a1[k1][j2]));
                    lastT += 5;
                }
                a2[k1][k2] = a2[k1][k2].scale(1.0 / p2);
            }
        }

        for (int k = 0; k < n; k++)
        {
            int k1 = k % p1;
            int k2 = k / p1;
            a[k] = a2[k1][k2];
        }
    }

    private static Complex As(Complex[] f, double[] w, int s, int jsum, int add)
    {
        Complex res;
        if (s == 0)
        {
            res = new Complex(f[jsum].re(), f[jsum].im());
        } else {
            Complex a0 = As(f, w, s - 1, jsum, add * 2);
            Complex a1 = As(f, w, s - 1, jsum + add, add * 2);
            Complex exp = new Complex(0, w[s-1]);
            exp = exp.exp();
            res = Complex.plus(a0, exp.times(a1));
            ++lastT;
            res = res.scale(0.5);
            //System.out.println("s="+s+" "+lastT);
        }
        return res;
    };

    public static void FFT(Complex[] f, Complex[] a)
    {
        lastT = 0;
        int n = f.length;
        int r = (int) (Math.log(n)/Math.log(2));

        double[][] w = new double[n][r];
        for (int k = 0; k < n; ++k)
        {
            for (int s = 0; s < r; ++s) {
                w[k][s] = -1.0 * (((k << (r - s - 1)) & (n - 1)) >> (r - s - 1)) * Math.PI / (1 << s);
                //lastT += 3;
            }
        }
        Complex[][] As = new Complex[r + 1][n];
        /*for (int s = 0; s <= r; ++s)
        {
            As[s] = new Complex[n];
            for (int k = 0; k < n; ++k)
            {
                if (s == 0)
                {
                    As[s][k] = new Complex(f[k].re(), f[k].im());
                } else {
                    Complex a0 = As[s - 1][k & ~(1 << (r - s))];
                    Complex a1 = As[s - 1][k | (1 << (r - s))];
                    Complex exp = new Complex(0, w[k][s - 1]);
                    exp = exp.exp();
                    As[s][k] = Complex.plus(a0, exp.times(a1));
                    ++lastT;
                    As[s][k] = As[s][k].scale(0.5);
                }
            }
        }
        for (int k = 0; k < n; ++k)
        {
            a[k] = As[r][k];
        }*/

        for (int k = 0; k < n; ++k)
        {
            for (int s = 0; s <= r; ++s)
            {
                for (int i = k; i < n / (1 << s) + k; ++i)
                {
                    int t = i;
                    while (t >= n / (1 << s)) t = t - n / (1 << s);
                    System.out.print(t + " ");
                    if (s == 0)
                    {
                        As[s][t] = new Complex(f[t].re(), f[t].im());
                    } else {
                        Complex a0 = As[s - 1][t];
                        Complex a1 = As[s - 1][t + (1 << (r - s))];
                        Complex exp = new Complex(0, w[k][s - 1]);
                        exp = exp.exp();
                        As[s][t] = Complex.plus(a0, exp.times(a1));
                        ++lastT;
                        As[s][t] = As[s][t].scale(0.5);
                        //System.out.println("s="+s+" "+lastT);
                    }
                }
                System.out.println();
                //lastT += 3;
            }
            a[k] = As[r][0];
        }
    }

    public static void main(String[] args) {
        int n = 8;
        System.out.println("Размер массивов: " + n);
        Complex[] f = new Complex[n];
        for (int i = 0; i < n; ++i)
            f[i] = new Complex(i % 2, 0);
        Complex[] a = new Complex[n];
        Complex[] fi = new Complex[n];
        for (Complex c : f)
            System.out.println(c + " ");
        System.out.println();
        long start = System.currentTimeMillis();
        Fourier.DFT(f, a);
        for (Complex c : a)
            System.out.println(c + " ");
        long finish = System.currentTimeMillis();
        System.out.println("T = " + lastT + " Time: " + (finish - start));
        start = finish;
        Fourier.SFFT(f, a);
        for (Complex c : a)
            System.out.println(c + " ");
        finish = System.currentTimeMillis();
        System.out.println("T = " + lastT + " Time: " + (finish - start));
        start = finish;
        Fourier.FFT(f, a);
        for (Complex c : a)
            System.out.println(c + " ");
        finish = System.currentTimeMillis();
        System.out.println("T = " + lastT + " Time: " + (finish - start));
        start = finish;
    }
}