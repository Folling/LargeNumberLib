#include "largeInt.h"

//a bunch of useful numbers which can be used in calculations

const largeInt zero(0);

//quite of a funny story behind this, we do need negative zero since the sign is saved seperately
//and yes I know there are ways to go around this but it doesn't hurt and is a fun gimick

const largeInt negZero = -zero;
const largeInt one( 1);
const largeInt two( 2);
const largeInt ten(10);

/*################################
  ##########CONSTRUCTORS##########
  ################################*/

largeInt:: largeInt(                    )
{
	value.resize(1);
	value[0] = 0;
	sign = '+';
}

largeInt:: largeInt(long long input     )
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

largeInt::~largeInt(                    )
{
}

/*#######################################
  ##########SETTERS AND GETTERS##########
  #######################################*/

std::vector<int>& largeInt::getValue() const
{
	return const_cast<largeInt*>(this)->value;
}

char largeInt::getSign() const
{
	return this->sign;
}

void largeInt::setSign(char newSign)
{
	if (newSign != '-' && newSign != '+') throw "Error resolving sign!\n";
	const_cast<largeInt*>(this)->sign = newSign;
}

void largeInt::setValue(const std::vector<int>& input)
{
	value = input;
}

void largeInt::append(const largeInt& tail)
{
	for (uint i = 0; i < tail.getValue().size(); i++) {
		this->getValue().push_back(tail[i]);
	}
}

uint largeInt::size() const
{
	return this->getValue().size();
}

void largeInt::resize(int newSize, int filler = 0)
{
	this->getValue().resize(newSize, filler);
}

void largeInt::popFront()
{
	this->getValue().erase(this->getValue().begin());
}

void largeInt::popEnd()
{
	this->getValue().erase(this->getValue().end() - 1);
}

void largeInt::push_back(int tail)
{
	this->getValue().push_back(tail);
}

/*##########################
  ##########ASSETS##########
  ##########################*/

//compares the absolute values of two numbers
int largeInt::compare(const largeInt& toTest) const
{
	std::vector<int> tmp1 = this->getValue();
	std::vector<int> tmp2 = toTest.getValue();

	while (tmp1.at(0) == 0 && tmp1.size() != 1) tmp1.erase(tmp1.begin());
	while (tmp2.at(0) == 0 && tmp2.size() != 1) tmp2.erase(tmp2.begin());

	if (tmp1.size() > tmp2.size()) return 1;
	if (tmp1.size() < tmp2.size()) return -1;
	uint size = tmp1.size();

	for (uint i = 0; i < size; i++)
	{
		if (tmp1.at(i) > tmp2.at(i)) return 1;
		if (tmp1.at(i) < tmp2.at(i)) return -1;
	}
	return 0;
}

largeInt& largeInt::removeZerosAtStart()
{
	while (this->getValue().front() == 0 && this->size() != 1) this->popFront();
	return *this;
}

largeInt& largeInt::removeZerosAtEnd()
{
	while (this->getValue().back() == 0 && this->size() != 1) this->popEnd();
	return *this;
}

largeInt  largeInt::toPositive()
{
	if (this->sign == '-') this->changeSign();
	return *this;
}

largeInt  largeInt::toNegative()
{
	if (this->sign == '+') this->changeSign();
	return *this;
}

largeInt  largeInt::changeSign()
{
	if (this->sign == '+') this->sign = '-';
	else this->sign = '+';
	return *this;
}

/*#################################
  ##########I-O OPERATORS##########
  #################################*/

std::istream& operator >>(std::istream& is,       largeInt& inputVal )
{
	//takes a string as input then 
	//makes a number out of that stored in a vector
	std::string s_input;
	uint i = 0;
	inputVal.sign = '+';
	is >> s_input;
	if (s_input[0] == '-')
	{
		inputVal.sign = '-';
		s_input.erase(s_input.begin());
	}
	if (s_input[0] > 57 || s_input[0] < 48) throw "Error, please enter only one minus sign!\n";
	std::vector<int> futureValue(s_input.size());
	try
	{
		for (; i < s_input.size(); i++)
		{
			futureValue.at(i) = resolveChar(s_input[i]);
		}
		inputVal.setValue(futureValue);
		inputVal.removeZerosAtStart();
		return is;
	}
	catch (const char* msg)
	{
		std::cout << msg;
		return is;
	}
}

std::ostream& operator <<(std::ostream& os, const largeInt& outputVal)
{
	if (outputVal.sign == '-') std::cout << '-';
	const_cast<largeInt&>(outputVal).removeZerosAtStart();
	for (uint i = 0; i < outputVal.size(); i++)
	{
		os << outputVal.getValue().at(i);
	}
	return os;
}

/*##########################################
  ##########MATHEMATICAL FUNCTIONS##########
  ##########################################*/

largeInt largeInt::factorial()
{
	largeInt res = one;
	while (*this > one)
	{
		res *= *this;
		*this -= one;
	}
	return res;
}

/*########################################
  ##########ARITHMETIC OPERATORS##########
  ########################################*/

largeInt largeInt::operator+ (const largeInt& summand   ) const
{
	largeInt returnNum;
	//macros to shorten the code
	largeInt LNtmp1 = *this;
	largeInt LNtmp2 = summand;
	std::vector<int>& tmp1 = LNtmp1.getValue();
	std::vector<int>& tmp2 = LNtmp2.getValue();
	int size;
	bool storedTen = false;
	int temp;
	if (LNtmp1 == zero) return summand;
	if (LNtmp2 == zero) return *this;
	//adapts the smaller vector to the larger vector by resizing him and reversing him so 1 turns into 00...01
	if (tmp1.size() > tmp2.size())
	{
		//puts as many 0s in front of the number as there are more digits in the other number
		size = tmp1.size();
		while (tmp1.size() != tmp2.size())
		{
			tmp2.insert(tmp2.begin(), 0);
		}
	}
	else if (tmp2.size() > tmp1.size())
	{
		//puts as many 0s in front of the number as there are more digits in the other number
		size = tmp2.size();
		while (tmp2.size() != tmp1.size())
		{
			tmp1.insert(tmp1.begin(), 0);
		}
	}
	else size = tmp1.size();
	std::vector<int> returnValue(size + 1);
	// if a digit + a digit exceeds 10 this gets stored to be added to the next comparison
	if (LNtmp1.sign == '+' && LNtmp2.sign == '+')
	{
		//adds all numbers together from right to left
		for (int i = size - 1; i >= 0; i--)
		{
			//checks whether the addition exceeds 10 to store in "storedTen"
			if (tmp1.at(i) + tmp2.at(i) + storedTen > 9)
			{
				temp = tmp1.at(i) + tmp2.at(i) + storedTen - 10;
				storedTen = true;
			}
			else
			{
				temp = tmp1.at(i) + tmp2.at(i) + storedTen;
				storedTen = false;
			}
			returnValue.at(i + 1) = temp;
		}
		//should the last addition have been larger than 10 the end number will have to be increased by one more digit 
		//e.g. 5+5 = 10
		if (storedTen == 1) returnValue[0] = 1;
		returnNum.setValue(returnValue);
	}
	else if (LNtmp1.sign == '-' && LNtmp2.sign == '-')
	{
		returnNum.sign = '-';
		//adds all numbers together from right to left
		for (int i = size - 1; i >= 0; i--)
		{
			//checks whether the addition exceeds 10 to store in "storedTen"
			if (tmp1.at(i) + tmp2.at(i) + storedTen > 9)
			{
				temp = tmp1.at(i) + tmp2.at(i) + storedTen - 10;
				storedTen = true;
			}
			else
			{
				temp = tmp1.at(i) + tmp2.at(i) + storedTen;
				storedTen = false;
			}
			returnValue.at(i + 1) = temp;
		}
		if (returnValue.at(0) == 0) returnValue.erase(returnValue.begin());
		if (storedTen == 1) returnValue.insert(returnValue.begin(), 1);
		returnNum.setValue(returnValue);
	}
	//case for when the signs are different
	else
	{
		if (LNtmp1.compare(LNtmp2) == 0) return zero; // -x + x = 0
		if (LNtmp1.compare(LNtmp2) == 1) returnNum.sign = LNtmp1.sign;
		else returnNum.sign = LNtmp2.sign;
		//for more information on how this part works check: https://www.youtube.com/watch?v=PS5p9caXS4U
		//turns the in the video described method, summand which will function as the subtrahend and changes it as required
		//with the difference that it doesn't reduce it by 10 at the end since we will invert the result
		if (LNtmp1.sign == '-')
		{
			for (int i = 0; i < size; i++)
			{
				//in either case if the digit is 0 it must not be inverted due to us using negative numbers
				if (i == size - 1)
				{
					tmp1.at(i) = (10 - tmp1.at(i));
					break;
				}
				tmp1.at(i) = (9 - tmp1.at(i));
			}
		}
		else
		{
			if (LNtmp2 > LNtmp1) returnNum.changeSign();
			largeInt tmp = LNtmp1;
			LNtmp1 = LNtmp2;
			LNtmp2 = tmp;
			for (int i = 0; i < size; i++)
			{
				if (i == size - 1)
				{
					tmp1.at(i) = (10 - tmp1.at(i));
					break;
				}
				tmp1.at(i) = (9 - tmp1.at(i));
			}
		}
		//adds newly created vector with the original summand
		for (int i = size - 1; i >= 0; i--)
		{
			//checks whether the addition exceeds 10 to store in "storedTen"
			if (tmp1.at(i) + tmp2.at(i) + storedTen > 9)
			{
				temp = tmp1.at(i) + tmp2.at(i) + storedTen - 10;
				storedTen = true;
			}
			else
			{
				temp = tmp1.at(i) + tmp2.at(i) + storedTen;
				storedTen = false;
			}
			returnValue.at(i + 1) = temp;
		}
		if (storedTen == true) returnValue.insert(returnValue.begin(), 1);
		while (returnValue.at(0) == 0 && returnValue.size() != 1) returnValue.erase(returnValue.begin());
		//in case the first summand is negative and smaller than the second or the second summand is the first digit gets removed
		//otherwise the first digit has to stay due to negative numbers
		//method doesn't work for negative numbers so we adapt it
		//hereby we take the invert of the values
		//since we only want to do 10-.at(i) we check whether it's already been done
		if (returnNum.sign == '-')
		{
			bool addedTen = false;
			for (int i = (returnValue.size() - 1); i >= 0; i--)
			{
				if (returnValue.at(i) == 0 && addedTen == false) continue;
				if (addedTen == false)
				{
					returnValue.at(i) = 10 - returnValue.at(i);
					addedTen = true;
				}
				//inverts the result because of negativity
				else
				{
					returnValue.at(i) = 9 - returnValue.at(i);
				}
				if (addedTen == false)returnValue.at(returnValue.size() - 1)++;
			}
		}
		if (returnNum.sign == '+')
		{
			if (tmp1.size() > 1 && tmp2.size() > 1) returnValue.insert(returnValue.begin(), 1);
			returnValue.erase(returnValue.begin());
		}
		if (returnNum.sign == '+') returnValue.erase(returnValue.begin());
	}
	//gets rid of all 0s in front;
	while (returnValue.at(0) == 0 && returnValue.size() != 1) returnValue.erase(returnValue.begin());
	returnNum.setValue(returnValue);
	return returnNum;
}

largeInt largeInt::operator- (const largeInt& subtrahend) const
{
	//since we basically defined subtraction and negative numbers in the + operator 
	//and subtraction is the counterpart to addition we just return the addition of the
	//minuend and the negative subtrahend
	largeInt result = *this;
	return result + -subtrahend;
}

largeInt largeInt::operator* (const largeInt& factor    ) const
{
	if (*this == zero || factor == zero || *this == negZero || factor == negZero) return zero;
	largeInt LNtmp1 = *this;
	largeInt LNtmp2 = factor;
	largeInt result = zero;
	//if you multiply e.g. 4 with 4 you get 16 so 6 carryover 1
	int carryOver = 0;
	largeInt toAdd = zero;
	//macros
	std::vector<int>& tmp1 = LNtmp1.getValue();
	std::vector<int>& tmp2 = LNtmp2.getValue();
	std::vector<int>& tmp3 = toAdd.getValue();
	std::vector<int>& tmp4 = result.getValue();
	//goes through each digit from factor 2 and multiplies it with each digit from factor 1 adding the values together
	for (int i = tmp2.size() - 1; i >= 0; i--)
	{
		for (int j = tmp1.size() - 1; j >= 0; j--)
		{
			int temp = tmp1.at(j) * tmp2.at(i) + carryOver;
			carryOver = temp / 10;
			tmp3.insert(tmp3.begin(), temp % 10);
		}
		//to adapt since the digits in this kind of multiplication are technically shifted.
		int zeroExtender = tmp2.size() - 1 - i;
		while (zeroExtender != 0)
		{
			tmp3.insert(tmp3.end(), 0);
			zeroExtender--;
		}
		//in case there's still a value left over this value becomes the new 1. digit
		tmp3.insert(tmp3.begin(), carryOver);
		//then it adds the previously calculated result to the current one and resets it
		result += toAdd;
		carryOver = 0;
		toAdd = zero;
	}
	//afterwards the final digit gets added if there is one.
	//tmp4.insert(tmp4.begin(), carryOver);
	//the last digit gets removed because there is always a 0 at the end
	tmp4.erase(tmp4.end() - 1);
	if (tmp4.size() == 0) return zero;
	//since multiplication disregards signs when it comes to value
	//the end sign is determined by the input signs though.
	if (this->sign == factor.sign) result.sign = '+';
	else result.sign = '-';
	return result;
}

largeInt largeInt::operator/ (const largeInt& divisor   ) const
{	
	if (*this == divisor) return one;
	if (divisor == zero) throw "You can't divide by 0!\n";
	if (divisor == one) return *this; // x/1 = x

	//macros and declarations

	int pushedZeros = 0;

	//there are used in the calculations
	largeInt tmp1 = const_cast<largeInt&>(*this);
	largeInt tmp2 = const_cast<largeInt&>(divisor);

	//compareVals are used to identify for how long the loop would have to run
	largeInt compareVal1 = const_cast<largeInt&>(*this);
	largeInt compareVal2 = const_cast<largeInt&>(divisor);

	//the result and a temporary which is used to drag down digits
	largeInt result = const_cast<largeInt&>(zero);
	largeInt temporary = const_cast<largeInt&>(zero);

	//iterates through the given divident
	int iterator = 0;

	//if more than 1 number is dragged down a 0 is appended 
	long long dragCount = 0;

	//the current value which will then be inserted
	int currResult = 0;

	std::vector<int>& divValue = tmp1.getValue();
	std::vector<int>& rValue = result.getValue();
	std::vector<int>& tempVal = temporary.getValue();

	tmp1.toPositive();
	tmp2.toPositive();
	compareVal1.toPositive();
	compareVal2.toPositive();

	//goes from left to right subtracting every time and then adding a result	
	while (result * compareVal2 < compareVal1 - compareVal2 + one)
	{
		//drags down so many digits until it can actually be subtracted
		while (temporary < tmp2)
		{
			//to prevent out of range when having calculations with 0s in the divident
			if (divValue.size() == iterator) break;
			if (dragCount >= 1)
			{
				rValue.push_back(0);
				pushedZeros++;
			}
			tempVal.push_back(divValue.at(iterator));
			dragCount++;
			iterator++;
		}
		temporary.removeZerosAtStart();

		//subtracts the divisor from the temporary result and adds a corresponding result every time.
		while (temporary - tmp2 >= zero)
		{
			if (tmp2 == zero) break;
			temporary -= tmp2;
			currResult++;
		}
		//inserts the previously calculated result in the end result
		rValue.insert(rValue.end(), currResult);
		currResult = 0;
		dragCount = 0;
		pushedZeros = 0;
	}
	result.removeZerosAtStart();
	if (this->sign == divisor.sign) result.sign = '+';
	else result.sign = '-';
	return result;
}

largeInt largeInt::operator% (const largeInt& divisor   ) const
{
	//returns the reminder of a division
	return *this - (*this / divisor) * divisor;
}

/*#############################################
  ##########OPERATOR-EQUALS OPERATORS##########
  #############################################*/

largeInt largeInt::operator+= (const largeInt& summand   )
{
	*this = *this + summand;
	return *this;
}

largeInt largeInt::operator-= (const largeInt& subtrahend)
{
	*this = *this - subtrahend;
	return *this;
}

largeInt largeInt::operator*= (const largeInt& factor    )
{
	*this = *this * factor;
	return *this;
}

largeInt largeInt::operator/= (const largeInt& divisor   )
{
	*this = *this / divisor;
	return *this;
}

largeInt largeInt::operator%= (const largeInt& divisor   )
{
	*this = *this % divisor;
	return *this;
}

/*#######################################
  ##########INCREMENT OPERATORS##########
  #######################################*/

largeInt largeInt::operator++ (int x     )
{
	largeInt& tmp(*this);
	*this += one;
	return tmp;
}

largeInt largeInt::operator-- (int x     )
{
	largeInt& tmp(*this);
	*this -= one;
	return tmp;
}

largeInt largeInt::operator++ (          )
{
	*this += one;
	return *this;
}

largeInt largeInt::operator-- (          )
{
	*this -= one;
	return *this;
}

largeInt largeInt::operator-  (          ) const
{
	// While not changing the Numbers value it does change the sign so
	largeInt temp = const_cast<largeInt&>(*this);
	temp.changeSign();
	return temp;
}

int&     largeInt::operator[] (uint index) const
{
	if (index >= this->size()) throw "Index is out of range!\n";
	return this->getValue().at(index);
}

/*########################################
  ##########COMPARISON OPERATORS##########
  ########################################*/

bool largeInt::operator== (const largeInt& test) const
{
	if (this->sign != test.sign) return false;
	return (this->compare(test) == 0) ? true : false;
}

bool largeInt::operator>  (const largeInt& test) const
{
	if (this->sign == '+' && test.sign == '-') return true;
	if (this->sign != test.sign) return false;
	if (this->sign == '+' && test.sign == '+')
	{
		if (this->compare(test) == 0) return false;
		if (this->compare(test) == -1) return false;
		return true;
	}
	if (this->compare(test) == 0) return false;
	if (this->compare(test) == 1) return false;
	return true;
}

bool largeInt::operator<  (const largeInt& test) const
{
	if (this->sign == '-' && test.sign == '+') return true;
	if (this->sign != test.sign) return false;
	if (this->sign == '+' && test.sign == '+')
	{
		if (this->compare(test) == 0) return false;
		if (this->compare(test) == 1) return false;
		return true;
	}
	if (this->compare(test) == 0) return false;
	if (this->compare(test) == -1) return false;
	return true;
}

bool largeInt::operator>= (const largeInt& test) const
{
	if (*this == test) return true;
	if (*this > test) return true;
	return false;
}

bool largeInt::operator<= (const largeInt& test) const
{
	if (*this == test) return true;
	if (*this < test) return true;
	return false;
}

bool largeInt::operator!= (const largeInt& test) const
{
	if (*this == test) return false;
	return true;
}

bool largeInt::operator!  (                    ) const
{
	if (this->getValue().size() <= 1 && this->getValue().at(0) != 0) return false;
	return true;
}

/*########################################
  ########NORMAL VALUED OPERATIONS########
  ########################################*/

  //all the following functions are just the basic operators so they work with any kind 
  //of variable, aka adding a largeInt to a normal int
  //they work by using the template constructor above and then doing the average calculation


largeInt largeInt::operator+(const long long summand) const
{
	largeInt LNsummand(summand);
	return *this + summand;
}

largeInt largeInt::operator-(const long long subtrahend) const
{
	largeInt LNsummand(subtrahend);
	return *this - LNsummand;
}

largeInt largeInt::operator*(const long long factor) const
{
	largeInt LNfactor(factor);
	return *this * LNfactor;
}
largeInt largeInt::operator/(const long long divisor) const
{
	largeInt LNdivisor(divisor);
	return *this * LNdivisor;
}

largeInt largeInt::operator%(const long long divisor) const
{
	largeInt LNdivisor(divisor);
	return *this * LNdivisor;
}

largeInt& largeInt::operator=(const long long setTo)
{
	largeInt tmp(setTo);
	while (tmp.getValue().at(0) == 0 && tmp.size() != 0)tmp.getValue().erase(tmp.getValue().begin());
	*this = tmp;
	return *this;
}

largeInt largeInt::operator+=(const long long summand)
{
	*this = *this + summand;
	return *this;
}

largeInt largeInt::operator-=(const long long subtrahend)
{
	*this = *this - subtrahend;
	return *this;
}

largeInt largeInt::operator*=(const long long factor)
{
	*this = *this * factor;
	return *this;
}

largeInt largeInt::operator/=(const long long divisor)
{
	*this = *this / divisor;
	return *this;
}

largeInt largeInt::operator%=(const long long divisor)
{
	*this = *this % divisor;
	return *this;
}

bool largeInt::operator==(const long long test) const
{
	largeInt LNtest(test);
	return (*this == LNtest);
}

bool largeInt::operator>(const long long test) const
{
	largeInt LNtest(test);
	return (*this > LNtest);
}

bool largeInt::operator<(const long long test) const
{
	largeInt LNtest(test);
	return (*this < LNtest);
}

bool largeInt::operator>=(const long long test) const
{
	largeInt LNtest(test);
	return (*this >= LNtest);
}

bool largeInt::operator<=(const long long test) const
{
	largeInt LNtest(test);
	return (*this <= LNtest);
}

bool largeInt::operator!=(const long long test) const
{
	largeInt LNtest(test);
	return (*this != LNtest);
}