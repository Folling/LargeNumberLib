#pragma once

#include "largeInt.h"
#include <conio.h>

class largeFloat
{
public:
	largeFloat();
	largeFloat(const largeFloat& toSet) = default;
	template <typename T>
	explicit largeFloat(T x);
	explicit largeFloat(std::string x);
	explicit largeFloat(char x);
	~largeFloat();
public:
	largeInt& getPreDValue() const;
	largeInt& getPostDValue() const;
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
	largeFloat operator  + (const largeFloat& summand   ) const;
	largeFloat operator  - (const largeFloat& subtrahend) const;
	largeFloat operator  * (const largeFloat& factor    ) const;
	largeFloat operator  / (const largeFloat& divisor   ) const;
	largeFloat operator  % (const largeFloat& divisor   ) const;
public:
	largeFloat operator += (const largeFloat& summand   );
	largeFloat operator -= (const largeFloat& subtrahend);
	largeFloat operator *= (const largeFloat& factor    );
	largeFloat operator /= (const largeFloat& divisor   );
	largeFloat operator %= (const largeFloat& divisor   );

public:
	largeFloat operator ++ (int x);
	largeFloat operator -- (int x);
	largeFloat operator ++ (     );
	largeFloat operator -- (     );
	largeFloat operator -  (     ) const;
private:
	//Pre and post decimal values
	largeInt preDecValue;
	largeInt postDecValue;
	char sign;
};


