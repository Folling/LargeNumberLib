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
	largeNum(const largeNum& toSet) = default;
	template <typename T>
	explicit largeNum(T x          );
	explicit largeNum(std::string x);
	explicit largeNum(char x       );
	~largeNum();
public:
	std::vector<int>& getValue() const;
	char getSign()               const;
	void setValue(const std::vector<int>& input);
public:
	largeNum largeNum::removeZerosAtStart() const;
	int compare(const largeNum& toTest) const;		
	largeNum& toNegative()		       ;
	largeNum& toPositive()		       ;
	largeNum& changeSign()			   ;
public:
	largeNum factorial();
public:
	friend std::istream& operator >> (std::istream& is, largeNum& iutputVal  );
	friend std::ostream& operator << (std::ostream& os, const largeNum& outputVal  );
public:
	largeNum operator  + (const largeNum& summand) const;
	largeNum operator  - (const largeNum& summand) const;
	largeNum operator  * (const largeNum& summand) const;
	largeNum operator  / (const largeNum& summand) const;
	largeNum operator  % (const largeNum& summand) const;
public:
	template<typename T> largeNum operator = (const T setTo);
	largeNum operator += (const largeNum& divisor);
	largeNum operator -= (const largeNum& divisor);
	largeNum operator *= (const largeNum& divisor);
	largeNum operator /= (const largeNum& divisor);
	largeNum operator %= (const largeNum& divisor);
public:
	largeNum operator ++ (int x);
	largeNum operator -- (int x);
	largeNum operator ++ (     );
	largeNum operator -- (     );
	largeNum operator -  (     );
	largeNum operator -  (     ) const;
public:
	bool operator == (const largeNum& test) const;
	bool operator >  (const largeNum& test) const;
	bool operator <  (const largeNum& test) const;
	bool operator >= (const largeNum& test) const;
	bool operator <= (const largeNum& test) const;
	bool operator != (const largeNum& test) const;
	bool operator !  (                    ) const;
private:
	std::vector<int> value;
	char sign;
};

template <typename T> largeNum::largeNum(T input) {
	value.resize(19);
	int i = 1;
	bool isNegative = false;
	if (input < 0) {
		input *= -1;
		isNegative = true;
	}
	while (true) {
		value.at(value.size() - i) = input % 10;
		input /= 10;
		if (input == 0) break;
		i++;
	}
	while (value.at(0) == 0 && value.size() != 1) value.erase(value.begin());
	this->sign = (isNegative == true) ? '-' : '+';
}

template <typename T> largeNum largeNum::operator=(const T setTo) {
	largeNum tmp(setTo);
	while (tmp.getValue().at(0) == 0)tmp.getValue().erase(tmp.getValue().begin());
	*this = tmp;
	return *this;
}

#endif