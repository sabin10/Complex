/*
	Filename: Complex.cpp
	Costin-Sabin Hantu, 254
	Complex Number Class
	Project 1
*/

#include "pch.h"
#include <iostream>
#include "Complex.hpp"

Complex::Complex(double pReal, double pImg) : mReal(pReal)
											, mImg(pImg)
{}

Complex::Complex(std::string s)
{
	double pReal, pImg;
	int posI = s.find("i"); // return -1 if "i" is not found

	if (posI == -1) {
		// mReal != 0 and mImg == 0
		std::stringstream realStream(s);
		realStream >> pReal;
		pImg = 0;
	}
	else { // mImg != 0
		if (posI == 0 || posI == 1) // mReal == 0
			pReal = 0;
		else { // mReal != 0
			std::string subReal = s.substr(0, posI - 1);
			std::stringstream realStream(subReal);
			realStream >> pReal;
		}
		std::string subImg = s.substr(posI + 2);
		std::stringstream imgStream(subImg);
		imgStream >> pImg;
		//sign of mImg (+ or -)
		std::string subImgSign = s.substr(posI - 1, 1);
		if (subImgSign == "-")
			pImg *= -1;
	}

	mReal = pReal;
	mImg = pImg;
}


Complex::Complex(const Complex &z)
{
	mReal = z.mReal;
	mImg = z.mImg;
}

void Complex::setReal(double pReal)
{
	mReal = pReal;
}

double Complex::getReal() const
{
	return mReal;
}

void Complex::setImg(double pImg)
{
	mImg = pImg;
}

double Complex::getImg() const
{
	return mImg;
}

/*
void Complex::operator=(const Complex &z)
{
	setReal(z.getReal());
	setImg(z.getImg());
}
*/

Complex & Complex::operator=(const Complex & z)
{
	this->mReal = z.getReal();
	this->mImg = z.getImg();

	return *this;
}

void Complex::operator=(const double pReal)
{
	setReal(pReal);
	setImg(0);
}

Complex Complex::operator+=(const Complex &z)
{
	this->mReal = this->getReal() + z.getReal();
	this->mImg = this->getImg() + z.getImg();

	return *this;
}

Complex Complex::operator+=(const double pReal)
{
	this->mReal = this->getReal() + pReal;

	return *this;
}

Complex Complex::operator-=(const Complex &z)
{
	this->mReal = this->getReal() - z.getReal();
	this->mImg = this->getImg() - z.getImg();

	return *this;
}

Complex Complex::operator-=(const double pReal)
{
	this->mReal = this->getReal() - pReal;

	return *this;
}

Complex Complex::operator*=(const Complex &z)
{
	// http://www.experior.ro/Docs/Inmultirea_numerelor_complexe
	double pReal = this->getReal();

	this->mReal = this->getReal() * z.getReal() - this->getImg() * z.getImg();
	this->mImg = pReal * z.getImg() + this->getImg() * z.getReal();

	return *this;
}

Complex Complex::operator*=(const double pReal)
{
	this->mReal = this->getReal() * pReal;
	this ->mImg = this->getImg() * pReal;

	return *this;
}

Complex Complex::operator/=(const Complex &z)
{
	// https://www.youtube.com/watch?v=eKkVavfBCNU
	double pReal = this->getReal();
	// saved mReal in a variable because it changes after setReal() call;

	this->mReal = 
		(getReal() * z.getReal() + getImg() * z.getImg()) /
		(pow(z.getReal(), 2) + pow(z.getImg(), 2))
	;
	this->mImg = 
		(z.getReal() * getImg() - pReal * z.getImg()) /
		(pow(z.getReal(), 2) + pow(z.getImg(), 2))
	;

	return *this;
}

Complex Complex::operator/=(const double nr)
{	
	if (nr == 0)
		throw std::invalid_argument("divide by 0 NOT OKAY");
	else {
		this->mReal = this->getReal() / nr;
		this->mImg = this->getImg() / nr;

		return *this;
	}
}

std::string Complex::toString()
{
	std::string s,
				subReal,
				subImg,
				subImgSign = "+";

	if (getReal() == 0 && getImg() == 0)
		return "0";

	if (getReal() != 0) {
		subReal = std::to_string(getReal());
	}

	if (getImg() == 0)
		return subReal;
	else {
		if (getImg() < 0) {
			subImgSign = "-";
			subImg = std::to_string(getImg() * (-1));
		}
		else
			subImg = std::to_string(getImg());
	}

	if (getReal() == 0 && getImg() > 0) {
		s = "i*" + subImg;
	}
	else
		s = subReal + subImgSign + "i*" + subImg;

	return s;
}

void Complex::conjugate()
{
	setImg(-1 * getImg());
}

Complex::operator std::string() const
{
	/*
	conversion operator std::string
	how to call:

	Complex z(1, 2);
	std::string s = z;
	*/
	Complex z(mReal, mImg);
	std::string s = z.toString();
	return s;
}

std::istream & operator>>(std::istream &stream, Complex &z)
{
	// same algorithm as string constructor
	std::string s;
	stream >> s;
	double pReal = 0, pImg = 0;

	int posI = s.find("i"); 
	if (posI == -1) {
		std::stringstream realStream(s);
		realStream >> pReal;
		pImg = 0;
	}
	else { 
		if (posI == 0 || posI == 1) 
			pReal = 0;
		else {
			std::string subReal = s.substr(0, posI - 1);
			std::stringstream realStream(subReal);
			realStream >> pReal;
		}
		std::string subImg = s.substr(posI + 2);
		std::stringstream imgStream(subImg);
		imgStream >> pImg;

		std::string subImgSign = s.substr(posI - 1, 1);
		if (subImgSign == "-")
			pImg *= -1;
	}
	z.setReal(pReal);
	z.setImg(pImg);

	return stream;
}

std::ostream & operator<<(std::ostream &stream, const Complex &z)
{
	if (z.getReal() == 0 && z.getImg() == 0) {
		stream << 0;
	}
	else if (z.getReal() == 0 && z.getImg() > 0) {
		stream << "i*" << z.getImg();
	}
	else if (z.getReal() == 0 && z.getImg() < 0) {
		stream << "-i*" << -z.getImg();
	}
	else if (z.getReal() > 0 && z.getImg() == 0) {
		stream << z.getReal();
	}
	else if (z.getReal() > 0 && z.getImg() > 0){
		stream << z.getReal() << "+i*" << z.getImg();
	}
	else if (z.getReal() > 0 && z.getImg() < 0) {
		stream << z.getReal() << "-i*" << -z.getImg();
	}
	else if (z.getReal() < 0 && z.getImg() == 0) {
		stream << z.getReal();
	}
	else if (z.getReal() < 0 && z.getImg() > 0) {
		stream << z.getReal() << "+i*" << z.getImg();
	}
	else if (z.getReal() < 0 && z.getImg() < 0) {
		stream << z.getReal() << "-i*" << -z.getImg();
	}

	return stream;
}

Complex operator+(const Complex &z)
{
	return Complex(z.getReal(), z.getImg());
}

Complex operator-(const Complex &z)
{
	return Complex(-z.getReal(), -z.getImg());
}

Complex operator+(const Complex &z1, const Complex &z2)
{
	return Complex(z1.getReal() + z2.getReal(), z1.getImg() + z2.getImg());
}

Complex operator+(const double pReal, const Complex &z)
{
	return Complex(pReal + z.getReal(), z.getImg());
}

Complex operator+(const Complex &z, const double pReal)
{
	return Complex(z.getReal() + pReal, z.getImg());
}

Complex operator-(const Complex &z1, const Complex &z2)
{
	return Complex(z1.getReal() - z2.getReal(), z1.getImg() - z2.getImg());
}

Complex operator-(const double pReal, const Complex &z)
{
	return Complex(pReal - z.getReal(), -z.getImg());
}

Complex operator-(const Complex &z, const double pReal)
{
	return Complex(z.getReal() - pReal, z.getImg());
}

Complex operator*(const Complex &z1, const Complex &z2)
{
	return Complex(
		z1.getReal() * z2.getReal() - z1.getImg() * z2.getImg(),
		z1.getReal() * z2.getImg() + z2.getReal() * z1.getImg()
	);
}

Complex operator*(const double nr, const Complex &z)
{
	return Complex(nr * z.getReal(), nr * z.getImg());
}

Complex operator*(const Complex &z, const double nr)
{
	return Complex(nr * z.getReal(), nr * z.getImg());
}

Complex operator/(const Complex &z1, const Complex &z2)
{
	return Complex(
		(z1.getReal()*z2.getReal() + z1.getImg()*z2.getImg()) /
		(pow(z2.getReal(), 2) + pow(z2.getImg(), 2)) ,
		(z2.getReal()*z1.getImg() - z1.getReal()*z2.getImg()) /
		(pow(z2.getReal(), 2) + pow(z2.getImg(), 2))
	);
}

Complex operator/(const double nr, const Complex &z)
{
	return Complex(
		(nr*z.getReal()) / (pow(z.getReal(), 2) - pow(z.getImg(), 2)),
		-1* (nr*z.getImg()) / (pow(z.getReal(), 2) - pow(z.getImg(), 2))
	);
}

Complex operator/(const Complex &z, const double nr)
{
	return Complex(z.getReal() / nr, z.getImg() / nr);
}

Complex operator^(const Complex &z, int n)
{
	// Moivre
	double r = sqrt(pow(z.getReal(), 2) + pow(z.getImg(), 2));
	double theta = acos(z.getReal() / r);
	return Complex(
		pow(r, n) * cos(n*theta),
		pow(r, n) * sin(n*theta)
	);
}

bool operator==(const Complex &z1, const Complex &z2)
{
	return z1.getReal() == z2.getReal() && z1.getImg() == z2.getImg();
}

bool operator==(const double pReal, const Complex &z)
{
	if (z.getImg() == 0 && pReal == z.getReal())
		return true;
	return false;
}

bool operator==(const Complex &z, const double pReal)
{
	if (z.getImg() == 0 && pReal == z.getReal())
		return true;
	return false;
}

bool operator!=(const Complex &z1, const Complex &z2)
{
	if (z1.getReal() == z2.getReal() && z1.getImg() == z2.getImg())
		return false;
	return true;
}

bool operator!=(const double pReal, const Complex &z)
{
	if (z.getImg() == 0 && z.getReal() == pReal)
		return false;
	return true;
}

bool operator!=(const Complex &z, const double pReal)
{
	if (z.getImg() == 0 && z.getReal() == pReal)
		return false;
	return true;
}

double getModule(const Complex &z)
{
	return sqrt(pow(z.mReal, 2) + pow(z.mImg, 2));
}

Complex getSquareRoot(const Complex &z, unsigned short int k)
{
	//http://www.math.md/stireal/matematica/candidat/numere_complexe.pdf
	double r = sqrt(pow(z.getReal(), 2) + pow(z.getImg(), 2));
	double theta = acos(z.getReal() / r);
	double pi = 3.14;

	return Complex(
		sqrt(r) * cos((theta + 2*k*pi) / 2),
		sqrt(r) * sin((theta + 2 * k*pi) / 2)
	);
}

