#ifndef _LNFUNCTIONS_
#define _LNFUNCTIONS_

#include "largeInt.h"

class largeFloat;
class largeInt;

int resolveChar(char c_input);
int findFirstNonZero(std::vector<int>);
int findIntLength(int i_input);
largeInt abs(largeInt& value);
//largeNum root  (largeNum& value);
//largeNum nthRoot(largeNum& radicand, largeNum& index);
//largeNum pow(largeNum& base, largeNum& exponent);
//largeNum log(largeNum& value);

#endif