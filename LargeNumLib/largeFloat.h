#ifndef _LARGEFLOAT_H
#define _LARGEFLOAT_H

#include "largeInt.h"
#include <conio.h>

class largeFloat
{
public:
	largeFloat();
	explicit largeFloat(long double);
	largeFloat(long long x, int decPos);
	largeFloat(const largeFloat& toSet) = default;
	~largeFloat();
public:
	largeInt& getPreDValue() const;
	largeInt& getPostDValue() const;
	int getPrecision() const;
	char getSign() const;
public:
	int compare(const largeFloat& toTest) const;
	largeFloat& removeZerosAtStart();
	largeFloat& removeZerosAtEnd();
	largeFloat toPositive();
	largeFloat toNegative();
	largeFloat changeSign();
	largeFloat adaptSigns();	
public:
	friend std::istream& operator >> (std::istream& is, largeFloat& iutputVal);
	friend std::ostream& operator << (std::ostream& os, const largeFloat& outputVal);
public:
	largeFloat operator  + (const largeFloat& summand    ) const;
	largeFloat operator  - (const largeFloat& subtrahend ) const;
	largeFloat operator  * (const largeFloat& factor     ) const;
	largeFloat operator  / (const largeFloat& divisor    ) const;
public:
	largeFloat operator += (const largeFloat& summand    );
	largeFloat operator -= (const largeFloat& subtrahend );
	largeFloat operator *= (const largeFloat& factor     );
	largeFloat operator /= (const largeFloat& divisor    );
	largeFloat operator %= (const largeFloat& divisor    );

public:
	largeFloat operator ++ (int x);
	largeFloat operator -- (int x);
	largeFloat operator ++ (     );
	largeFloat operator -- (     );
	largeFloat operator -  (     ) const;
public:
	bool operator ==(const largeFloat& test ) const;
	bool operator  >(const largeFloat& test ) const;
	bool operator  <(const largeFloat& test ) const;
	bool operator >=(const largeFloat& test ) const;
	bool operator <=(const largeFloat& test ) const;
	bool operator !=(const largeFloat& test ) const;
	bool operator  !(                       ) const;
public:
	static int precision;
private:
	//Pre and post decimal values
	largeInt preDecValue;
	largeInt postDecValue;
	char sign;
};

inline void setPrecision(const int toSet)
{
	largeFloat::precision = toSet;
}

#endif // LARGEFLOAT_H