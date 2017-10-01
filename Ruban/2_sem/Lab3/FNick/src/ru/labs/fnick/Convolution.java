package ru.labs.fnick;

import edu.pronceton.cs.introcs.java.class32.Complex;

final public class Convolution {
    public static long lastT = 0;

    private Convolution(){}

    static public long[] basic(long[] a, long[] b)
    {
        lastT = 0;
        int n = a.length;
        long[] c = new long[n * 2];
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
            {
                c[i + k] += a[i] * b[k];
                ++lastT;
            }
        return c;
    }

    static public long[] DFTbased(long[] a, long[] b)
    {
        lastT = 0;
        int n = a.length;

        Complex[] af = new Complex[n * 2];
        Complex[] aa = new Complex[n * 2];
        for (int i = 0; i < n; ++i)
            af[i] = new Complex(a[i], 0);
        for (int i = n; i < 2 * n; ++i)
            af[i] = new Complex(0, 0);
        Complex[] bf = new Complex[n * 2];
        Complex[] ba = new Complex[n * 2];
        for (int i = 0; i < n; ++i)
            bf[i] = new Complex(b[i], 0);
        for (int i = n; i < 2 * n; ++i)
            bf[i] = new Complex(0, 0);

        Fourier.DFT(af, aa);
        lastT += Fourier.lastT;
        Fourier.DFT(bf, ba);
        lastT += Fourier.lastT;

        Complex[] ca = new Complex[2 * n];
        Complex[] cf = new Complex[2 * n];
        for (int i = 0; i < 2 * n; ++i)
            ca[i] = aa[i].times(ba[i]).scale(2 * n);
        lastT += 2 * n;
        Fourier.RDFT(ca, cf);
        lastT += Fourier.lastT;

        long[] c = new long[2 * n];
        for (int i = 0; i < 2 * n; ++i)
            c[i] = Math.round(cf[i].re());

        return c;
    }

    static public long[] SFFTbased(long[] a, long[] b)
    {
        lastT = 0;
        int n = a.length;

        Complex[] af = new Complex[n * 2];
        Complex[] aa = new Complex[n * 2];
        for (int i = 0; i < n; ++i)
            af[i] = new Complex(a[i], 0);
        for (int i = n; i < 2 * n; ++i)
            af[i] = new Complex(0, 0);
        Complex[] bf = new Complex[n * 2];
        Complex[] ba = new Complex[n * 2];
        for (int i = 0; i < n; ++i)
            bf[i] = new Complex(b[i], 0);
        for (int i = n; i < 2 * n; ++i)
            bf[i] = new Complex(0, 0);

        Fourier.SFFT(af, aa);
        lastT += Fourier.lastT;
        Fourier.SFFT(bf, ba);
        lastT += Fourier.lastT;

        Complex[] ca = new Complex[2 * n];
        Complex[] cf = new Complex[2 * n];
        for (int i = 0; i < 2 * n; ++i)
            ca[i] = aa[i].times(ba[i]).scale(2 * n);
        lastT += 2 * n;
        Fourier.RSFFT(ca, cf);
        lastT += Fourier.lastT;

        long[] c = new long[2 * n];
        for (int i = 0; i < 2 * n; ++i)
            c[i] = Math.round(cf[i].re());

        return c;
    }

    static public long[] FFTbased(long[] a, long[] b)
    {
        lastT = 0;
        int n = a.length;

        Complex[] af = new Complex[n * 2];
        Complex[] aa = new Complex[n * 2];
        for (int i = 0; i < n; ++i)
            af[i] = new Complex(a[i], 0);
        for (int i = n; i < 2 * n; ++i)
            af[i] = new Complex(0, 0);
        Complex[] bf = new Complex[n * 2];
        Complex[] ba = new Complex[n * 2];
        for (int i = 0; i < n; ++i)
            bf[i] = new Complex(b[i], 0);
        for (int i = n; i < 2 * n; ++i)
            bf[i] = new Complex(0, 0);

        Fourier.FFT(af, aa);
        lastT += Fourier.lastT;
        Fourier.FFT(bf, ba);
        lastT += Fourier.lastT;

        Complex[] ca = new Complex[2 * n];
        Complex[] cf = new Complex[2 * n];
        for (int i = 0; i < 2 * n; ++i)
            ca[i] = aa[i].times(ba[i]).scale(2 * n);
        lastT += 2 * n;
        Fourier.RFFT(ca, cf);
        lastT += Fourier.lastT;

        long[] c = new long[2 * n];
        for (int i = 0; i < 2 * n; ++i)
            c[i] = Math.round(cf[i].re());

        return c;
    }

    public static void test() {
        long[] a, b, c;
        int n = 1024;
        a = new long[n];
        b = new long[n];
        for (int i = 0; i < n; ++i)
        {
            a[i] = i + 1;
            b[i] = i + 1;
        }
        for (long i : a)
            System.out.print(i + " ");
        System.out.println();
        for (long i : b)
            System.out.print(i + " ");
        System.out.println();

        c = Convolution.basic(a, b);
        for (long i : c)
            System.out.print(i + " ");
        System.out.println();
        System.out.println("T = " + lastT);

        c = Convolution.DFTbased(a, b);
        for (long i : c)
            System.out.print(i + " ");
        System.out.println();
        System.out.println("T = " + lastT);

        c = Convolution.SFFTbased(a, b);
        for (long i : c)
            System.out.print(i + " ");
        System.out.println();
        System.out.println("T = " + lastT);

        c = Convolution.FFTbased(a, b);
        for (long i : c)
            System.out.print(i + " ");
        System.out.println();
        System.out.println("T = " + lastT);
    }
}
