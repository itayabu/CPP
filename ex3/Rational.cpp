/*
 * Rational.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: itayabu
 */
# include "Rational.h"



/**
 * exception thrown when dividing by zero
 */
class RationalZeroDenominatorException: std::exception
{
	std::string what()
	{
		return "cannot divide by zero";
	}

};

/**
 * Constructors getting int or default which is set to 0
 */
Rational::Rational (const long int &value)
{
	_numerator = value;
	_denominator = 1;
}

/**
 * Constructors getting numerator and denominator
 */
Rational::Rational(const long int &numerator, const long int &denominator)
{
	if (denominator == 0)
	{
		throw RationalZeroDenominatorException();
	}
	_numerator = numerator;
	_denominator = denominator;
	_fixZero();
	_makeRepresentationCoprime();
	_fixNegativity();
}

/**
 * Constructors by string "numerator/denominator"
 */
Rational::Rational(const std::string &str)
{
	std::string  middle = str.substr(0, str.find("/"));
	_numerator = atol((str.substr(0, str.find("/")).c_str()));
	_denominator = atol((str.substr(str.find("/") + 1).c_str()));
	_fixZero();
	_makeRepresentationCoprime();
	_fixNegativity();
}

/**
 * Constructors copy constructor
 */
Rational::Rational(const Rational &other)
{
	_numerator = other._numerator;
	_denominator = other._denominator;
}

/**
 * Constructors move constructor
 */
Rational::Rational (Rational && other)
{
	std::swap (_numerator, other._numerator);
	std::swap (_denominator, other._denominator);
}

/**
 * Assignment operator, use copy-and-swap idiom
 */
Rational& Rational::operator=(Rational other)
{
	std::swap (_numerator, other._numerator);
	std::swap (_denominator, other._denominator);
	return *this;
}

/**
 * Returns the numerator
 */
const long int Rational::getNumerator() const
{
	return _numerator;
}

/**
 * Returns the denominator
 */
const long int Rational::getDenominator() const
{
	return _denominator;
}

//
/**
 * Summing two Rationals
 * Addition should be calculated in the way we calculate addition of 2
 * ratios (using their common denominator).
 */
const Rational Rational::operator+(const Rational &other) const
{
	long int numerator = (this->_numerator * other._denominator) +
			(this->_denominator * other._numerator);
	long int denominator = (this->_denominator * other._denominator);
	Rational toReturn = Rational(numerator, denominator);

	return toReturn;
}

/**
 * Multiplying operator for Rational
 * Multiplication should be calculated in the way we calculate
 * multiplication of 2 ratios (separately for the numerator and for the
 * denominator).
 */
const Rational Rational::operator*(const Rational &other) const
{
	Rational toReturn = Rational (this->_numerator * other._numerator,
			this->_denominator * other._denominator);
	return toReturn;
}

/**
 * operator<< for stream insertion
 * The format is numerator/denominator w/o spaces or addional characters
 */
std::ostream& operator<<(std::ostream &os, const Rational &number)
{
	os << number._numerator << "/" << number._denominator;
	return os;
}

/**
 * if numerator is zero, denominator is set to 1
 */
void Rational::_fixZero()
{
	if (_numerator == 0)
	{
		_denominator = 1;
	}
}

/**
 * if number is negative, make the numerator negative and denominator positive.
 */
void Rational::_fixNegativity()
{
	if (_denominator < 0)
	{
		_denominator *= -1;
		_numerator *= -1;
	}
}

/**
 * making the representation co-prime.
 */
void Rational::_makeRepresentationCoprime()
{
	long int gcd = _greatestCommonDivisor(_numerator, _denominator);
	_numerator = _numerator / gcd;
	_denominator = _denominator / gcd;
}

/**
 * find the greatest common divider.
 */
const long int Rational::_greatestCommonDivisor(const long int &a, const long int &b)
{
	if (a == 0)
	{
		return b;
	}
	return _greatestCommonDivisor(b % a, a);
}



