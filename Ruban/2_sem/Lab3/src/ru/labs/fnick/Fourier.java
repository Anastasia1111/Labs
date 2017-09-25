package ru.labs.fnick;

import edu.pronceton.cs.introcs.java.class32.Complex;

import java.time.Clock;
import java.time.Instant;
import java.time.ZoneId;
import java.util.SortedMap;

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

    public static void FFT(Complex[] f, Complex[] a)
    {
        lastT = 0;
        int n = f.length;
        int r = (int) (Math.log(n)/Math.log(2));

        Complex[][] As = new Complex[r + 1][n];
        for (int k = 0; k < n; ++k)
        {
            As[0][k] = f[k];
        }
        for (int s = 0; s < r; ++s)
        {
            for (int k = 0; k < n; ++k) {
                As[s + 1][k] = As[s][(k & ~(1 << (r - s - 1)))];
                int k_sum = 0;
                for (int l = 0; l <= s; ++l)
                {
                    k_sum += ((k << l) & (1 << (r - 1))) >> (r - 1 - l);
                }
                Complex arg = new Complex(0, -2.0 * Math.PI * k_sum / (1 << (s + 1)));
                Complex exp = arg.exp();
                int new_k = (k | (1 << (r - s - 1)));
                As[s + 1][k] = Complex.plus(As[s + 1][k], As[s][new_k].times(exp));
                lastT += 4;
                As[s + 1][k] = As[s+1][k].scale(0.5);
            }
        }
        for (int k = 0; k < n; ++k)
        {
            int rev = 0;
            for (int l = 0; l < r; ++l)
                rev = (rev << 1) + ((k >> l) & 1);
            a[k] = As[r][rev];
        }
    }

    public static void main(String[] args) {
        int n = 16384;
        System.out.println("Размер массивов: " + n);
        Complex[] f = new Complex[n];
        for (int i = 0; i < n; ++i)
            f[i] = new Complex(i % 2, 0);
        Complex[] a = new Complex[n];
        Complex[] fi = new Complex[n];
        /*for (Complex c : f)
            System.out.println(c + " ");*/
        System.out.println();
        long start = System.currentTimeMillis();
        Fourier.DFT(f, a);
        /*for (Complex c : a)
            System.out.println(c + " ");*/
        long finish = System.currentTimeMillis();
        System.out.println("T = " + lastT + " Time: " + (finish - start));
        start = finish;
        Fourier.SFFT(f, a);
        /*for (Complex c : a)
            System.out.println(c + " ");*/
        finish = System.currentTimeMillis();
        System.out.println("T = " + lastT + " Time: " + (finish - start));
        start = finish;
        Fourier.FFT(f, a);
        /*for (Complex c : a)
            System.out.println(c + " ");*/
        finish = System.currentTimeMillis();
        System.out.println("T = " + lastT + " Time: " + (finish - start));
        start = finish;
    }
}