#pragma once
#ifndef _LARGENUM_
#define _LARGENUM_

#include <iostream>
#include <vector>
#include <string>
#include "largeNumFunctions.h"

typedef unsigned int uint;

class largeInt
{
public:
	largeInt();
	largeInt(const largeInt& toSet) = default;
	template <typename T>
	explicit largeInt(T x);
	explicit largeInt(std::string x);
	explicit largeInt(char x);
	~largeInt();
public:
	std::vector<int>& getValue() const;
	char getSign() const;
	void setSign(char newSign);
	void setValue(const std::vector<int>& input);
	void append(const largeInt& tail);
	uint size() const;
	void resize(int newSize, int filler);
	void popFront();
	void popEnd();
	void push_back(int tail);
public:
	int compare(const largeInt& toTest) const;
	largeInt& removeZerosAtStart();
	largeInt& removeZerosAtEnd();
	largeInt toPositive();
	largeInt toNegative();
	largeInt changeSign();
public:
	largeInt factorial();
public:
	friend std::istream& operator >>(std::istream& is, largeInt& iutputVal);
	friend std::ostream& operator <<(std::ostream& os, const largeInt& outputVal);
public:
	largeInt operator +(const largeInt& summand   ) const;
	largeInt operator -(const largeInt& subtrahend) const;
	largeInt operator *(const largeInt& factor    ) const;
	largeInt operator /(const largeInt& divisor   ) const;
	largeInt operator %(const largeInt& divisor   ) const;
public:
	template <typename T>
	largeInt operator +(const T summand   ) const;
	template <typename T>
	largeInt operator -(const T subtrahend) const;
	template <typename T>
	largeInt operator *(const T factor    ) const;
	template <typename T>
	largeInt operator /(const T divisor   ) const;
	template <typename T>
	largeInt operator %(const T divisor   ) const;
public:
	largeInt operator +=(const largeInt& summand   );
	largeInt operator -=(const largeInt& subtrahend);
	largeInt operator *=(const largeInt& factor    );
	largeInt operator /=(const largeInt& divisor   );
	largeInt operator %=(const largeInt& divisor   );
public:
	template <typename T>
	largeInt& operator =(const T setTo     );
	template <typename T>
	largeInt operator +=(const T summand   );
	template <typename T>
	largeInt operator -=(const T subtrahend);
	template <typename T>
	largeInt operator *=(const T factor    );
	template <typename T>
	largeInt operator /=(const T divisor   );
	template <typename T>
	largeInt operator %=(const T divisor   );
public:
	largeInt operator ++(int x);
	largeInt operator --(int x);
	largeInt operator ++();
	largeInt operator --();
	largeInt operator  -() const;
	int& operator [](uint index) const;
public:
	bool operator ==(const largeInt& test) const;
	bool operator  >(const largeInt& test) const;
	bool operator  <(const largeInt& test) const;
	bool operator >=(const largeInt& test) const;
	bool operator <=(const largeInt& test) const;
	bool operator !=(const largeInt& test) const;
	bool operator  !(                    ) const;
public:
	template <typename T>
	bool operator ==(const T test) const;
	template <typename T>
	bool operator  >(const T test) const;
	template <typename T>
	bool operator  <(const T test) const;
	template <typename T>
	bool operator >=(const T test) const;
	template <typename T>
	bool operator <=(const T test) const;
	template <typename T>
	bool operator !=(const T test) const;
	template <typename T>
	bool operator  !(            ) const;
private:
	std::vector<int> value;
	char sign;
};

template <typename T>
largeInt::largeInt(T input)
{
	value.resize(19);
	int i = 1;
	bool isNegative = false;
	if (input < 0)
	{
		input *= -1;
		isNegative = true;
	}
	while (true)
	{
		value.at(value.size() - i) = input % 10;
		input /= 10;
		if (input == 0) break;
		i++;
	}
	while (value.at(0) == 0 && value.size() != 1) value.erase(value.begin());
	this->sign = (isNegative == true) ? '-' : '+';
}

//all the following functions are just the basic operators so they work with any kind 
//of variable, aka adding a largeInt to a normal int
//they work by using the template constructor above and then doing the average calculation

template <typename T>
largeInt largeInt::operator+(const T summand) const
{
	largeInt LNsummand(summand);
	return *this + summand;
}

template <typename T>
largeInt largeInt::operator-(const T subtrahend) const
{
	largeInt LNsummand(subtrahend);
	return *this - subtrahend;
}

template <typename T>
largeInt largeInt::operator*(const T factor) const
{
	largeInt LNsummand(factor);
	return *this * factor;
}

template <typename T>
largeInt largeInt::operator/(const T divisor) const
{
	largeInt LNsummand(divisor);
	return *this * divisor;
}

template <typename T>
largeInt largeInt::operator%(const T divisor) const
{
	largeInt LNsummand(divisor);
	return *this * divisor;
}

template <typename T>
largeInt& largeInt::operator=(const T setTo)
{
	largeInt& tmp(setTo);
	while (tmp.getValue().at(0) == 0)tmp.getValue().erase(tmp.getValue().begin());
	*this = tmp;
	return *this;
}

template <typename T>
largeInt largeInt::operator+=(const T summand)
{
	*this = *this + summand;
	return *this;
}

template <typename T>
largeInt largeInt::operator-=(const T subtrahend)
{
	*this = *this - subtrahend;
	return *this;
}

template <typename T>
largeInt largeInt::operator*=(const T factor)
{
	*this = *this * factor;
	return *this;
}

template <typename T>
largeInt largeInt::operator/=(const T divisor)
{
	*this = *this / divisor;
	return *this;
}

template <typename T>
largeInt largeInt::operator%=(const T divisor)
{
	*this = *this % divisor;
	return *this;
}

template <typename T>
bool largeInt::operator==(const T test) const
{
	largeInt LNtest(test);
	return (*this == LNtest);
}

template <typename T>
bool largeInt::operator>(const T test) const
{
	largeInt LNtest(test);
	return (*this > LNtest);
}

template <typename T>
bool largeInt::operator<(const T test) const
{
	largeInt LNtest(test);
	return (*this < LNtest);
}

template <typename T>
bool largeInt::operator>=(const T test) const
{
	largeInt LNtest(test);
	return (*this >= LNtest);
}

template <typename T>
bool largeInt::operator<=(const T test) const
{
	largeInt LNtest(test);
	return (*this <= LNtest);
}

template <typename T>
bool largeInt::operator!=(const T test) const
{
	largeInt LNtest(test);
	return (*this != LNtest);
}

template <typename T>
bool largeInt::operator!() const
{
	largeInt LNtest(*this);
	return !LNtest;
}

#endif
