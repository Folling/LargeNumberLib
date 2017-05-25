#include "largeNumFunctions.h"

int findFirstNonZero(std::vector<int> x) {
	int counter = 0;
	for (int i = x.size() - 1; i >= 0; i--) {
		if (x.at(i) != 0) break;
		counter++;
	}
	return counter;
}

int findIntLength(int i_input) {
	int lengthCount = 0;
	for (; i_input != 0; i_input /= 10, lengthCount++);
	return lengthCount;

}


Decimal::largeInt abs(Decimal::largeInt& value)
{
	value.toPositive();
	return value;
}