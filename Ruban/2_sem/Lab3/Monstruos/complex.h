#ifndef COMPLEX_CLASS
#define COMPLEX_CLASS

class Complex
{
private:
	double re;
	double im;
public:
	Complex() : re(0), im(0) {};
	Complex(double real, double image) : re(real), im(image) {};
	Complex operator+ (const Complex& sec) {
		Complex tmp(re + sec.re, im + sec.im);
		return tmp;
	}
	Complex operator- (const Complex& sec) {
		Complex tmp(re - sec.re, im - sec.im);
		return tmp;
	}
	Complex operator* (const Complex& sec) {
		Complex tmp(re*sec.re - im*sec.im, re*sec.im + im*sec.re);
		return tmp;
	}
	Complex operator/ (const Complex& sec) {
		Complex tmp((re*sec.re + im*sec.im)/(im*im + sec.im*sec.im), 
			(im*sec.re - re*sec.im)/(im*im + sec.im*sec.im));
		return tmp;
	}
	Complex operator+ (const double& sec) {
		Complex tmp(re + sec, im);
		return tmp;
	}
	Complex operator- (const double& sec) {
		Complex tmp(re - sec, im);
		return tmp;
	}
	Complex operator* (const double& sec) {
		Complex tmp(re*sec, im*sec);
		return tmp;
	}
	Complex operator/ (const double& sec) {
		Complex tmp(re/sec, im/sec);
		return tmp;
	}
	Complex operator+= (const Complex& sec) {
		this->re += sec.re;
		this->im += sec.im;
		return *this;
	}
	Complex operator+= (const double& sec) {
		this->re += sec;
		return *this;
	}
	Complex operator*= (const Complex& sec) {
		this->set(re*sec.re - im*sec.im, re*sec.im + im*sec.re);
		return *this;
	}
	Complex operator= (const Complex& sec) {
		this->re = sec.re;
		this->im = sec.im;
		return *this;
	}
	Complex operator= (const double& sec) {
		this->re = sec;
		this->im = 0.0;
		return *this;
	}
	Complex operator/= (const double& sec) {
		this->re /= sec;
		this->im /= sec;
		return *this;
	}
	void print() {
		printf("(%.4f + %4.4fi)", re, im);
		return;
	}
	void set(double real, double image) {
		re = real;
		im = image;
		return;
	}
};

#endif //COMPLEX_CLASS
