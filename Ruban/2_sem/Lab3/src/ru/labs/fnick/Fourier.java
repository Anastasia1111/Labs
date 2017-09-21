package ru.labs.fnick;

import edu.pronceton.cs.introcs.java.class32.Complex;

public class Fourier {
    public static int lastT = 0;

    public void DFT(Complex[] f, Complex[] a)
    {
        lastT = 0;
        int n = f.length;
        for (int k = 0; k < n; k++)
        {
            a[k] = new Complex(0, 0);
            for (int j = 0; j < n; ++j)
            {
                Complex exp = new Complex(0, -2.0 * k * j * Math.PI / n);
                a[k] = Complex.plus(a[k], exp.times(f[j]));
                ++lastT;
            }
            a[k] = a[k].scale(1.0/n);
        }
    }
}