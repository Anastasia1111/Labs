#include <cstdlib>
#include <iostream>

using namespace std;

int multi(short int x, short int y, int k2);
int capacity(short int x);
int max(int a, int b);
int theory_labour (int n);

// only for integer 2^16 numbers
// don't know about labour

int main(int argc, char const *argv[])
{
	int T = 0;
	short int x, y;
	cin >> x >> y;
	int sign = 0;
	if(x < 0) x *= -1, sign++;
	if(y < 0) y *= -1, sign++;
	sign &= 1;
	int n = max(capacity(x), capacity(y));
	int res = multi(x, y, n);
	if(sign)
		res *= -1;
	cout << x << " * " << y << " = " << res << endl;
	cout << "numbers length = " << n << endl;
	cout << "thoretical T(" << n << ") = " << theory_labour(n) << endl;
	cout << "practical T(" << n << ") = " << T << endl;
	system("pause");
	return 0;
}

int multi(short int x, short int y, int k2) {
	if( k2 <= 1 ) 
		return x*y;
	int res;
	if( k2 % 2 )
	{
		int a1 = x >> k2-1;
		int b1 = y >> k2-1;
		int a2 = x & (~(1 << (k2-1)));
		int b2 = y & (~(1 << (k2-1)));
		res = ( (x >> (k2-1))  * (y >> (k2-1)) << 2*(k2-1) );
		res += ( multi(a1, b2, k2-1) << (k2-1) );
		res += ( multi(a2, b1, k2-1) << (k2-1) );
		res += multi(a2, b2, k2-1);
	} else {
		int k = k2 / 2;
		int a = ((x & ((1 << k2) - 1)) & ~((1 << k) - 1)) >> k;
		int b = (x & ((1 << k) - 1));
		int c = ((y & ((1 << k2) - 1)) & ~((1 << k) - 1)) >> k;
		int d = (y & ((1 << k) - 1));
		
		int u1 = a + b, u2 = c + d;
		int u; 
		if((capacity(u1) > k) || (capacity(u2) > k))
			u = multi(u1, u2, k + 1);
		else
			u = multi(u1, u2, k);
		int v = multi(a, c, k);
		int w = multi(b, d, k);
		res = (v << k2) + ((u - v - w) << k) + w;
	}
	return res;
}

int capacity(short int x) {
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
	return 3*theory_labour(n/2) + (n % 2 ? 5*n : 4*n);

}
