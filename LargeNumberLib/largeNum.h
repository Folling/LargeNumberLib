#ifndef _LARGENUM_
#define _LARGENUM_

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "functions.h"

typedef unsigned int uint;

class largeNum
{
public:
	largeNum();
	largeNum(std::string x);
	largeNum(char x);
	~largeNum();
public:
	std::vector<int>& getValue();
	void setValue(const std::vector<int>& input);
	int compare(largeNum& toTest);
public:
	friend std::istream& operator >> (std::istream& is, largeNum& iutputVal);
	friend std::ostream& operator << (std::ostream& os, largeNum& outputVal);
	friend largeNum operator+(largeNum& summand1, largeNum& summand2);
	friend largeNum operator-(largeNum& minuend, largeNum& subtrahend);
	friend largeNum operator*(largeNum factor1, largeNum factor2);
	friend largeNum operator/(largeNum& dividend, largeNum& divisor);
	friend largeNum operator%(largeNum& dividend, largeNum& divisor);
public:
	largeNum operator =(largeNum& setTo);
	largeNum operator+=(largeNum& addent);
	largeNum operator-=(largeNum& addent);
	largeNum operator*=(largeNum& addent);
	largeNum operator/=(largeNum& addent);
	largeNum operator%=(largeNum& addent);
	largeNum operator++ (int x);
	largeNum operator-- (int x);
	largeNum operator++();
	largeNum operator--();
	largeNum operator -();
public:
	bool operator ==(largeNum& test);
	bool operator > (largeNum& test);
	bool operator < (largeNum& test);
	bool operator >=(largeNum& test);
	bool operator <=(largeNum& test);
	bool operator !=(largeNum& test);
	bool operator  !();

private:
	std::vector<int> value;
	char sign;
};
#endif

