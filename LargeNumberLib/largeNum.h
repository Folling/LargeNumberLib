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
	largeNum(largeNum &x);
	template <typename T> largeNum(T x);
	largeNum(std::string x);
	largeNum(char x);
	~largeNum();
public:
	std::vector<int>& getValue();
	void setValue(const std::vector<int>& input);
	int compare(largeNum& toTest);
	largeNum& changeSign();	
	char getSign() const;
public:
	largeNum factorial();
public:
	friend std::istream& operator >> (std::istream& is, largeNum& iutputVal  );
	friend std::ostream& operator << (std::ostream& os, largeNum& outputVal  );
	friend largeNum		 operator  + (largeNum& summand1, largeNum& summand2 );
	friend largeNum	     operator  - (largeNum& minuend, largeNum& subtrahend);
	friend largeNum		 operator  * (largeNum& factor1, largeNum& factor2   );
	largeNum			 operator  / (largeNum& divisor					     );
	friend largeNum operator%(largeNum& dividend, largeNum& divisor);
public:
	//largeNum operator =(largeNum& setTo		);
	template<typename T> largeNum operator = (T setTo);
	largeNum operator+=(largeNum& addent	);
	largeNum operator-=(largeNum& subtrahend);
	largeNum operator*=(largeNum& addent	);
	largeNum operator/=(largeNum& addent	);
	largeNum operator%=(largeNum& addent	);
	largeNum operator++ (int x);
	largeNum operator-- (int x);
	largeNum operator++ (     );
	largeNum operator-- (     );
	largeNum operator - (     );	
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

template <typename T> largeNum::largeNum(T input) {
	value.resize(19);
	int i_input = input;
	int i = 1;
	while (true) {
		value.at(value.size() - i) = i_input % 10;
		i_input /= 10;
		if (i_input == 0) break;
		i++;
	}
	while (value.at(0) == 0 && value.size() != 1) value.erase(value.begin());
}

template <typename T>
largeNum largeNum::operator=(T setTo) {
	largeNum tmp(setTo);
	*this = tmp;
	return *this;
}

#endif