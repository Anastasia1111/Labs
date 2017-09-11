#include <iostream>
#include <cmath>

using namespace std;

class Complex // класс комплексных чисел  
{
public:
	
	double re, im;
	
	Complex() {};
	
	Complex (double r, double i)
	{
		re = r;
		im = i;
	};
	
	~Complex() {};
	 
	Complex & operator = (Complex &c)
	{
		re = c.re; 
		im = c.im;
		
		return (*this);
	}
	
	Complex Complex::operator + (Complex &c) 
	{  
		Complex temp;
		
		temp.re = re + c.re;
		temp.im = im + c.re;
		
		return temp;  
	}
	 
	Complex Complex::operator - (Complex &c)
	{  
		Complex temp;
		temp.re = re - c.re;
		temp.im = im - c.re;
		
		return temp;
	}
	 
	Complex Complex::operator * (Complex &c)
	{  
		Complex temp;
		temp.re = re*c.re - im*c.im;
		temp.im = re*c.im + im*c.re;
		
		return temp;
	}
	
	friend ostream& operator<<(ostream &out, const Complex& c);
};

ostream& operator<<(ostream &out, const Complex& c)
{
	out << "(" << c.re << "+" << c.im << "i)";
	
	return out;
}
