/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
	public static int[] a, b;
	public static int T;
	public static Random rand = new Random(); 
	
	static public int[] conv()
	{
		T = 0;
		int n = a.length;
		int[] c = new int[n * 2];
		for (int i = 0; i < 2 * n - 1; ++i)
			for (int k = 0; k <= i && k < n; ++k).
			{
				if (i >= n)
				{
					c[i] += a[i-n+1+k]*b[n-1-k]
				}
				c[i] += a[k]*b[i-k];
				++T;
			}
		return c;
	}
	
	public static void main(String args[])
	{
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
		int[] c = conv();
		for (int i : c)
			System.out.print(i + " ");
		System.out.println();
		System.out.print("T = " + T);
	}
}