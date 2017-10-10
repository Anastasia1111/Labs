#include <cstdlib>
#include <iostream>

using namespace std;

long long multi(int x, int y, int k2);
int capacity(int x);
int max(int a, int b);
int theory_labour (int n);

// only for integer 2^16 numbers
// don't know about labour
int T;
int main(int argc, char const *argv[])
{
	T = 0;
	int x, y;
	cin >> x >> y;
	int sign = 0;
	int n = max(capacity(x), capacity(y));
	long long res = multi(x, y, n);
	cout << x << " * " << y << " = " << (long long)res << endl;
	cout << "numbers length = " << n << endl;
	cout << "thoretical T(" << n << ") = " << theory_labour(n) << endl;
	cout << "practical T(" << n << ") = " << T << endl;
	system("pause");
	return 0;
}

long long multi(int x, int y, int k2) {
	if( k2 <= 1 )
	{
		T++;
		return (long long)x&y;
	}
	long long res = 0;
	if( k2 % 2 )
	{
		int a1 = x >> k2-1;
		int b1 = y >> k2-1;
		int a2 = x & (~(1 << (k2-1)));
		int b2 = y & (~(1 << (k2-1)));
		if(a1 && b1)
		{
			res = ( (long long)1 << 2*(k2-1) );
			T += k2 - 1;
		}
		if(a1)
			res += ( ((long long)b2) << (k2-1) );
		if(b1)
			res += ( ((long long)a2) << (k2-1) );
		res += multi(a2, b2, k2-1);
	} else {
		int k = k2 / 2;
		int a = (x & ~((1 << k) - 1)) >> k;
		int b = (x & ((1 << k) - 1));
		int c = (y & ~((1 << k) - 1)) >> k;
		int d = (y & ((1 << k) - 1));
		
		int u1 = a + b, u2 = c + d;
		T += k * 2;
		long long u; 
		if((capacity(u1) > k) || (capacity(u2) > k))
			u = multi(u1, u2, k + 1);
		else
			u = multi(u1, u2, k);
		long long v = multi(a, c, k);
		long long w = multi(b, d, k);
		res = (long long)((v << k2) + ((u - v - w) << k) + w);
		T += k2 * 2;
	}
	return res;
}

int capacity(int x) {
	if(x == 0) return 1;
	int i = 0;
    for (; x ; x >>= 1)
        ++i;
    return i;
}

int max(int a, int b){
	return a > b ? a : b;
}

int theory_labour (int n)
{
	if(n == 1) return 1;
	return 3*theory_labour(n/2) + (n % 2 ? 4*n: 3*n);

}
