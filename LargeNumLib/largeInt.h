#ifndef _LARGEINT_H
#define _LARGEINT_H

#include <iostream>
#include <vector>
#include <string>

inline int resolveChar(char c_input) {
	switch (c_input) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: throw "Number contains non-numeric values!\n";
	}
}

typedef unsigned int uint;

namespace Decimal
{
	class largeInt
	{
	public:
		largeInt();
		largeInt(const largeInt& toSet) = default;
		explicit largeInt(long long x);
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
		largeInt operator+ (const largeInt& summand) const;
		largeInt operator- (const largeInt& subtrahend) const;
		largeInt operator* (const largeInt& factor) const;
		largeInt operator/ (const largeInt& divisor) const;
		largeInt operator% (const largeInt& divisor) const;
	public:
		largeInt operator+(const long long summand) const;
		largeInt operator-(const long long subtrahend) const;
		largeInt operator*(const long long factor) const;
		largeInt operator/(const long long divisor) const;
		largeInt operator%(const long long divisor) const;
	public:
		largeInt operator+= (const largeInt& summand);
		largeInt operator-= (const largeInt& subtrahend);
		largeInt operator*= (const largeInt& factor);
		largeInt operator/= (const largeInt& divisor);
		largeInt operator%= (const largeInt& divisor);
	public:
		largeInt& operator = (const long long setTo);
		largeInt  operator+= (const long long summand);
		largeInt  operator-= (const long long subtrahend);
		largeInt  operator*= (const long long factor);
		largeInt  operator/= (const long long divisor);
		largeInt  operator%= (const long long divisor);
	public:
		largeInt operator++ (int x);
		largeInt operator-- (int x);
		largeInt operator++ ();
		largeInt operator-- ();
		largeInt operator - () const;
		int& operator [](uint index) const;
	public:
		bool operator== (const largeInt& test) const;
		bool operator > (const largeInt& test) const;
		bool operator < (const largeInt& test) const;
		bool operator>= (const largeInt& test) const;
		bool operator<= (const largeInt& test) const;
		bool operator!= (const largeInt& test) const;
		bool operator ! () const;
	public:
		bool operator ==(const long long test) const;
		bool operator  >(const long long test) const;
		bool operator  <(const long long test) const;
		bool operator >=(const long long test) const;
		bool operator <=(const long long test) const;
		bool operator !=(const long long test) const;
	private:
		std::vector<int> value;
		char sign;
	};

}

std::istream& operator >>(std::istream& is, Decimal::largeInt& iutputVal);
std::ostream& operator <<(std::ostream& os, const Decimal::largeInt& outputVal);

#endif // LARGEINT_H
