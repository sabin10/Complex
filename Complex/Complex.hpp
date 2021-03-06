/*
	Filename: Complex.hpp
*/
#include <string>
#include <math.h>
#include <sstream>
#include <stdexcept>


class Complex {
public:
	Complex(double pReal = 0, double pImg = 0);
	Complex(std::string s);
	Complex(const Complex &z);

	void setReal(double pReal);
	double getReal() const;

	void setImg(double pImg);
	double getImg() const;

	//void operator= (const Complex &z); //multiple assignments doesnt work
	Complex & operator= (const Complex &z); //multiple assignments work ex: obj1 = obj2 = obj3;
	void operator= (const double pReal);

	Complex operator+= (const Complex &z);
	Complex operator+= (const double pReal);

	Complex operator-= (const Complex &z);
	Complex operator-= (const double pReal);

	Complex operator*= (const Complex &z);
	Complex operator*= (const double pReal);

	Complex operator/= (const Complex &z);
	Complex operator/= (const double pReal);

	friend Complex operator+ (const Complex &z);
	friend Complex operator- (const Complex &z);

	friend Complex operator+ (const Complex &z1, const Complex &z2);
	friend Complex operator+ (const double pReal, const Complex &z);
	friend Complex operator+ (const Complex &z, const double pReal);

	friend Complex operator- (const Complex &z1, const Complex &z2);
	friend Complex operator- (const double pReal, const Complex &z);
	friend Complex operator- (const Complex &z, const double pReal);

	friend Complex operator* (const Complex &z1, const Complex &z2);
	friend Complex operator* (const double nr, const Complex &z);
	friend Complex operator* (const Complex &z, const double nr);

	friend Complex operator/ (const Complex &z1, const Complex &z2);
	friend Complex operator/ (const double nr, const Complex &z);
	friend Complex operator/ (const Complex &z, const double nr);

	friend Complex operator^ (const Complex &z, int n);

	friend bool operator== (const Complex &z1, const Complex &z2);
	friend bool operator== (const double pReal, const Complex &z);
	friend bool operator== (const Complex &z, const double pReal);

	friend bool operator!= (const Complex &z1, const Complex &z2);
	friend bool operator!= (const double pReal, const Complex &z);
	friend bool operator!= (const Complex &z, const double pReal);

	friend std::istream & operator>> (std::istream & stream, Complex &z);
	friend std::ostream & operator<< (std::ostream & stream, const Complex &z);

	std::string toString();

	void conjugate();

	operator std::string() const;

	friend double getModule(const Complex &z);

	friend Complex getSquareRoot(const Complex &z, unsigned short int k); // k = 0 or 1

private:
	double mReal;
	double mImg;
};