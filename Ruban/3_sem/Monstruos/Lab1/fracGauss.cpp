#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Frac 
{
	public:
		Frac() : numer(0), denom(1) {};
		
		Frac(int a, int b) {
			if(b) {
				numer = a;
				denom = b;
				toShorten();
				setSign();
			} else {
				numer = 0;
				denom = 1;
			}
		};
		
		Frac(double num, int pres = 1000000) {
			if(pres <= 0) {
				numer = 0;
				denom = 1;
			} else {
				numer = (int) (num * pres);
				denom = pres;
				toShorten();
				setSign();
			}
		};
		
		//+-*/
		
		Frac operator+ (const Frac& sec) {
			int resDenom = NOK(this->denom, sec.denom);
			int resNumer = this->numer * (resDenom / this->denom) + sec.numer * (resDenom / sec.denom);
			Frac res(resNumer, resDenom);
			return res;
		};
		
		Frac operator+ (const double& sec) {
			Frac tmpSec(sec);
			Frac res = *this + tmpSec;
			return res;
		};
		
		Frac operator- (const Frac& sec) {
			int resDenom = NOK(this->denom, sec.denom);
			int resNumer = this->numer * (resDenom / this->denom) - sec.numer * (resDenom / sec.denom);
			Frac res(resNumer, resDenom);
			return res;
		};
		
		Frac operator- (const double& sec) {
			Frac tmpSec(sec);
			Frac res = *this - tmpSec;
			return res;
		};
		
		Frac operator* (const Frac& sec) {
			int resDenom = this->denom * sec.denom;
			int resNumer = this->numer * sec.numer;
			Frac res(resNumer, resDenom);
			return res;
		};
		
		Frac operator* (const double& sec) {
			Frac tmpSec(sec);
			Frac res = *this * tmpSec;
			return res;
		};
		
		Frac operator/ (const Frac& sec) {
			int resDenom = this->denom * sec.numer;
			int resNumer = this->numer * sec.denom;
			Frac res(resNumer, resDenom);
			return res;
		};
		
		Frac operator/ (const double& sec) {
			Frac tmpSec(sec);
			Frac res = *this / tmpSec;
			return res;
		};
		
		//+-*/=
		
		Frac operator+= (const Frac& sec) {
			*this = *this + sec;
			return *this;
		};
		
		Frac operator+= (const double& sec) {
			Frac tmpSec(sec);
			*this = *this + tmpSec;
			return *this;
		};
		
		Frac operator-= (const Frac& sec) {
			*this = *this - sec;
			return *this;
		};
		
		Frac operator-= (const double& sec) {
			Frac tmpSec(sec);
			*this = *this - tmpSec;
			return *this;
		};
		
		Frac operator*= (const Frac& sec) {
			*this = *this * sec;
			return *this;
		};
		
		Frac operator*= (const double& sec) {
			Frac tmpSec(sec);
			*this = *this * tmpSec;
			return *this;
		};
		
		Frac operator/= (const Frac& sec) {
			*this = *this / sec;
			return *this;
		};
		
		Frac operator/= (const double& sec) {
			Frac tmpSec(sec);
			*this = *this / tmpSec;
			return *this;
		};
		
		//<>==
		
		bool operator> (const Frac& sec) {
			int resNumer = this->numer - sec.numer;
			return resNumer > 0;
		};
		
		bool operator> (const double& sec) {
			Frac tmpSec(sec);
			return *this > tmpSec;
		};
		
		bool operator< (const Frac& sec) {
			int resNumer = this->numer - sec.numer;
			return resNumer < 0;
		};
		
		bool operator< (const double& sec) {
			Frac tmpSec(sec);
			return *this < tmpSec;
		};
		
		bool operator== (const Frac& sec) {
			int resNumer = this->numer - sec.numer;
			return resNumer == 0;
		};
		
		bool operator== (const double& sec) {
			Frac tmpSec(sec);
			return *this == tmpSec;
		};
		
		
		Frac invert() {
			Frac tmp (denom, numer);
			return tmp;
		};
		
		Frac pow(int x) {
			
			Frac tmp(numer, denom);
			
			if(x < 0) {
				tmp = tmp.invert();
				x *= -1;
			}
			
			Frac res = tmp;
			
			for(int i = 0; i < x; ++i) {
				res = res * tmp;
			}
			
			return res;
		}
		
		void setNewNum(int newNumer, int newDenom) {
			numer = newNumer;
			denom = newDenom;
			setSign();
			toShorten();
		}
		
		void print() {
			printf("%7i/%i", numer, denom);
		}
	
	private:
		int numer;
		int denom;
		int GCD(int a, int b) {
			return b ? GCD(b, a%b) : a;
		};
		int NOK(int a, int b) {
			return a*b / GCD(a, b);
		};
		void toShorten() {
			int k = GCD(numer, denom);
			numer /= k;
			denom /= k;
		};
		void setSign() {
			if(denom < 0) {
				numer *= -1;
				denom *= -1;
			}
		}
};

int size;

Frac **arr;
Frac *ans;

void swap(int fst, int sec)
{
	int i;
	Frac buff;
	for(i = 0; i < (size + 1); ++i)
	{
		buff = arr[fst][i];
		arr[fst][i] = arr[sec][i];
		arr[sec][i] = buff;
	}
}

int compare(int colNum)
{
	Frac buff = arr[colNum][colNum];
	int i;
	int num = colNum;// number of row with max "a"
	for(i = colNum + 1; i < size; ++i)
	{
		if(arr[i][colNum] > buff)
		{
			buff = arr[i][colNum];
			num = i;
		}
	}
	return num;
}

void print_arr () {
	for(int k = 0; k < size; ++k)
	{
		for(int l = 0; l < size+1; ++l) {
			arr[k][l].print();
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}


int main() {
	
	int i, j, k;
	int numer;
	Frac q;
	
	FILE *f = fopen("matrix.txt", "r+");
	
	fscanf(f, "%i", &size);
	cout << "size = " << size << endl << endl;
	int bufNumer, bufDenom;
	arr = new Frac *[size];
	ans = new Frac [size];
	for(i = 0; i < size; ++i) {
		arr[i] = new Frac [size + 1];
		for(j = 0; j < size + 1; ++j) {
			fscanf(f, "%i/%i", &bufNumer, &bufDenom);
			arr[i][j].setNewNum(bufNumer, bufDenom);
			arr[i][j].print();
			cout << " ";
		}
		
		cout << endl;
	}
	
	cout << endl;
	
	for(i = 0; i < size; ++i)
	{
//		numer = compare(i);
//		if(numer != i)
//			swap(numer, i);
		Frac buf = arr[i][i];
		for(j = i; j < size+1; ++j) {
			arr[i][j] /= buf;
		}
		for(j = 0; j < size; ++j)
		{
			if(j == i) continue;
			q = arr[j][i];
			
			for(k = i; k < size+1; ++k)
			{
				arr[j][k] -= arr[i][k]*q;
			}		
		}
		print_arr();
	}
	
	printf("Pryamoi khod\n");
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size+1; ++j) {
			arr[i][j].print();
			cout << " ";
		}
		cout << endl;
	}
	
	for(i = size-1; i >= 0; --i)
	{
//		q = arr[i][size];
//		for(j = i+1; j < size; ++j)
//		{
//			q -= arr[i][j] * ans[j];
//		}
//		ans[i] = q/arr[i][i];
		ans[i] = arr[i][size];
	}
	
	printf("\nAnswers:\n");
	for(j = 0; j < size; ++j) {
		cout << "x" << j << " = ";
		ans[j].print();
		cout << endl;
	}
	
	system("pause");
	return 0;
}
