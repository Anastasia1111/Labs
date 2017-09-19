package ru.labs.fnick;

import java.util.*;
import java.lang.*;
import java.io.*;

public class Main {
    public static int[] a, b, c;
    public static int T;
    public static Random rand = new Random();

    public static void main(String[] args) {
        System.out.println("Введите размеры массивов А и В: ");
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        if (n > m)
        {
            a = new int[n];
            b = new int[n];
        } else {
            a = new int[m];
            b = new int[m];
        }
        for (int i = 0; i < n; ++i)
        {
            a[i] = rand.nextInt(2*n) - n;
        }
        for (int i : a)
            System.out.print(i + " ");
        System.out.println();
        for (int i = 0; i < m; ++i)
        {
            b[i] = rand.nextInt(2*m) - m;
        }
        for (int i : b)
            System.out.print(i + " ");
        System.out.println();
        int[] c = Convolution.basic(a, b);
        T = Convolution.lastT;
        for (int i : c)
            System.out.print(i + " ");
        System.out.println();
        System.out.print("T = " + T);
    }
}
