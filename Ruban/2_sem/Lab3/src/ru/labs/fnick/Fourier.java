package ru.labs.fnick;

import edu.pronceton.cs.introcs.java.class32.Complex;

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
            ++lastT;
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
                ++lastT;
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
                ++lastT;
            }
        }

        for (int k = 0; k < n; k++)
        {
            int k1 = k % p1;
            int k2 = k / p1;
            a[k] = a2[k1][k2];
        }
    }

    private static Complex As(Complex[] f, int[] k, int s, int jsum, int add)
    {
        Complex res;
        if (s == 0)
        {
            res = new Complex(f[jsum].re(), f[jsum].im());
        } else {
            res = As(f, k, s - 1, jsum, add * 2);
            Complex tmp = As(f, k, s - 1, jsum + add, add * 2);
            double power = 0;
            for (int l = 0; l < s; ++l)
                power += k[l] * (1 << l);
            Complex exp = new Complex(0, -2.0 * power * Math.PI / (1 << s));
            exp = exp.exp();
            res = Complex.plus(res, exp.times(tmp));
            res = res.scale(0.5);
            lastT += 5;
        }
        return res;
    };

    public static void FFT(Complex[] f, Complex[] a)
    {
        lastT = 0;
        int n = f.length;
        int r = (int) (Math.log(n)/Math.log(2));

        int[] k = new int[r];
        for (int km = 0; km < n; ++km)
        {
            for (int l = 0; l < r; ++l)
                k[l] = (km >> l) & 1;
            a[km] = As(f, k, r, 0, 1);
        }
    }

    public static void main(String[] args) {
        int n = 4096;
        System.out.println("Размер массивов: " + n);
        Complex[] f = new Complex[n];
        for (int i = 0; i < n; ++i)
            f[i] = new Complex(i % 2, 0);
        Complex[] a = new Complex[n];
        Complex[] fi = new Complex[n];
        /*for (Complex c : f)
            System.out.println(c + " ");
        System.out.println();*/
        Fourier.DFT(f, a);
        /*for (Complex c : a)
            System.out.println(c + " ");*/
        System.out.println("T = " + lastT);
        Fourier.SFFT(f, a);
        /*for (Complex c : a)
            System.out.println(c + " ");*/
        System.out.println("T = " + lastT);
        Fourier.FFT(f, a);
        /*for (Complex c : a)
            System.out.println(c + " ");*/
        System.out.println("T = " + lastT);
    }
}