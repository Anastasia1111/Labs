class Complex
{
private:
	double re;
	double im;
public:
	Complex() : re(0), im(0) {};
	Complex(double real, double image) : re(real), im(image) {};
	Complex operator+ (const Complex& sec) {
		Complex tmp(this->re + sec.re, this->im + sec.im);
		return tmp;
	}
	Complex operator- (const Complex& sec) {
		Complex tmp(this->re - sec.re, this->im - sec.im);
		return tmp;
	}
	Complex operator* (const Complex& sec) {
		Complex tmp(this->re*sec.re - this->im*sec.im, this->re*sec.im + this->im*sec.re);
		return tmp;
	}
	Complex operator/ (const Complex& sec) {
		Complex tmp((this->re*sec.re + this->im*sec.im)/(this->im*this->im + sec.im*sec.im), 
			(this->im*sec.re - this->re*sec.im)/(this->im*this->im + sec.im*sec.im));
		return tmp;
	}
	Complex operator+ (const double& sec) {
		Complex tmp(this->re + sec, this->im);
		return tmp;
	}
	Complex operator- (const double& sec) {
		Complex tmp(this->re - sec, this->im);
		return tmp;
	}
	Complex operator* (const double& sec) {
		Complex tmp(this->re*sec, this->im*sec);
		return tmp;
	}
	Complex operator/ (const double& sec) {
		Complex tmp(this->re/sec, this->im/sec);
		return tmp;
	}
	void print(){
		printf("(%f + %fi)", re, im);
		return;
	}
};
