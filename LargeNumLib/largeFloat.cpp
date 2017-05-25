#include "largeFloat.h"

using namespace Decimal;

int largeFloat::precision = 100;

const largeFloat zero(0);

largeFloat::largeFloat()
{
	preDecValue.getValue().resize(1);
	preDecValue.getValue().at(0) = 0;
	postDecValue.getValue().resize(1);
	postDecValue.getValue().at(0) = 0;
	sign = '+';
}

largeFloat::largeFloat(long double x)
{
	sign = x < 0 ? '-' : '+';
	preDecValue = static_cast <long long>(x);
	long double temp = x - static_cast <long long>(x);
	while (temp - static_cast <long long>(temp) != 0) temp *= 10;
	postDecValue = static_cast <long long>(temp);
	adaptSigns();
}

largeFloat::largeFloat(long long x, int decPos)
{
	sign = x < 0 ? '-' : '+';
	preDecValue = x;
	if (decPos == 0) return;
	int counter = preDecValue.size() - decPos;
	if (decPos < 0)
	{
		decPos *= -1;
		postDecValue = x;
		preDecValue = 0;
		while (--decPos)
		{
			postDecValue.getValue().insert(postDecValue.getValue().begin(), 0);
		}
		return;
	}
	while(--counter)
	{		
		postDecValue.getValue().insert(postDecValue.getValue().begin(), preDecValue.getValue().back());
		preDecValue.popEnd();
		postDecValue.removeZerosAtEnd();
	}
	adaptSigns();
}

largeFloat::~largeFloat()
{
}

/*#######################################
  ##########SETTERS AND GETTERS##########
  #######################################*/

largeInt& largeFloat::getPreDValue() const
{
	return const_cast<largeFloat*>(this)->preDecValue;
}

largeInt& largeFloat::getPostDValue() const
{
	return const_cast<largeFloat*>(this)->postDecValue;
}

int largeFloat::getPrecision() const
{
	return precision;
}

char largeFloat::getSign() const
{
	return this->sign;
}

/*##########################
  ##########ASSETS##########
  ##########################*/

//compares the absolute value of two numbers
int largeFloat::compare(const largeFloat& toTest) const
{
	//would disturb the size comparisons
	const_cast<largeFloat*>(this)->removeZerosAtStart();
	const_cast<largeFloat&>(toTest).removeZerosAtStart();
	//a float is split up in the value before and after 
	//the decimal point
	largeInt tmp1 = this->getPreDValue();
	largeInt tmp2 = toTest.getPreDValue();

	//if one of the preDecValues is larger it's obviously larger in general
	if (tmp1.getValue().size() > tmp2.getValue().size()) return 1;
	if (tmp1.getValue().size() < tmp2.getValue().size()) return -1;
	uint size = tmp1.getValue().size();

	//otherwise it scans whether one of the digits is larger than one of the others at the same position
	for (uint i = 0; i < size; i++)
	{
		if (tmp1.getValue().at(i) > tmp2.getValue().at(i)) return 1;
		if (tmp1.getValue().at(i) < tmp2.getValue().at(i)) return -1;
	}

	//afterwards we do the same for the post decimal point value
	tmp1 = this->getPostDValue();
	tmp2 = toTest.getPostDValue();

	if (tmp1.getValue().size() > tmp2.getValue().size()) return 1;
	if (tmp1.getValue().size() < tmp2.getValue().size()) return -1;
	size = tmp1.getValue().size();
	for (uint i = 0; i < size; i++)
	{
		if (tmp1.getValue().at(i) > tmp2.getValue().at(i)) return 1;
		if (tmp1.getValue().at(i) < tmp2.getValue().at(i)) return -1;
	}
	return 0;
}

largeFloat& largeFloat::removeZerosAtStart()
{
	largeInt& sVal = this->getPreDValue();
	if (sVal.size() == 0) return *this;
	while (sVal.getValue().front() == 0 && sVal.size() != 1) sVal.getValue().erase(sVal.getValue().begin());
	return *this;
}

largeFloat& largeFloat::removeZerosAtEnd()
{
	largeInt& sVal = this->getPostDValue();
	if (sVal.size() == 0) return *this;
	while (sVal.getValue().back() == 0 && sVal.size() != 0) sVal.popEnd();
	return *this;
}

largeFloat largeFloat::toPositive()
{
	if (this->sign == '-') this->changeSign();
	this->adaptSigns();
	return *this;
}

largeFloat largeFloat::toNegative()
{
	if (this->sign == '+') this->changeSign();
	this->adaptSigns();
	return *this;
}

largeFloat largeFloat::changeSign()
{
	if (this->sign == '+') this->sign = '-';
	else this->sign = '+';
	this->adaptSigns();
	return *this;
}

largeFloat largeFloat::adaptSigns()
{
	this->preDecValue.setSign(this->sign);
	this->postDecValue.setSign(this->sign);
	return *this;
}

/*#################################
  ##########I-O OPERATORS##########
  #################################*/


std::istream& operator >>(std::istream& is, largeFloat& val)
{
	val.getPreDValue().getValue().clear();
	val.getPostDValue().getValue().clear();
	//takes a string as input then 
	//makes a number out of that stored in a vector
	std::string s_input;
	val.getPreDValue().setSign('+');
	is >> s_input;
	if (s_input[0] == '-')
	{
		val.getPreDValue().toNegative();
		s_input.erase(s_input.begin());
	}
	for (uint i = 0; i < s_input.size(); i++)
	{
		if (s_input.at(i) == '.') break;
		if (s_input.at(i) == 0 && s_input.size() != 1) s_input.erase(s_input.begin());
	}
	if (s_input[0] > 57 || s_input[0] < 48 && s_input[0] != 44 && s_input[0] != 46) throw "Error: Please only enter one minus sign!\n";
	std::vector<int> futureValue(s_input.size());
	try
	{
		uint i = 0;
		for (; i < s_input.size(); i++)
		{
			if (s_input[i] == '.')
			{
				if (i == 0) val.getPreDValue().getValue().insert(val.getPreDValue().getValue().begin(), 0);
				i++;
				break;
			}
			if (val.getPreDValue().size() == 0) val.getPreDValue().getValue().insert(val.getPreDValue().getValue().begin(), resolveChar(s_input[i]));
			else val.getPreDValue().push_back(resolveChar(s_input[i]));
		}
		for (; i < s_input.size(); i++)
		{
			if (s_input[i] == '.') throw "Error, can't enter more than one decimal point\n";
			if (val.getPostDValue().size() == 0) val.getPostDValue().getValue().insert(val.getPostDValue().getValue().begin(), resolveChar(s_input[i]));
			else val.getPostDValue().push_back(resolveChar(s_input[i]));
		}
		val.getPostDValue().setSign(val.getPreDValue().getSign());
	}
	catch (const char* msg)
	{
		std::cout << msg;
		return is;
	}
	return is;
}

std::ostream& operator <<(std::ostream& os, const largeFloat& outputVal)
{
	if (outputVal.getPreDValue().getSign() == '-') std::cout << '-';
	const_cast<largeFloat&>(outputVal).removeZerosAtStart();
	for (uint i = 0; i < outputVal.getPreDValue().size(); i++)
	{
		os << outputVal.getPreDValue()[i];
	}
	outputVal.getPostDValue().removeZerosAtEnd();
	if (outputVal.getPostDValue().size() > 0)
	{
		if (outputVal.getPostDValue().size() == 1 && outputVal.getPostDValue()[0] == 0) return os;
		std::cout << '.';
		for (uint i = 0; i < outputVal.getPostDValue().size(); i++)
		{
			os << outputVal.getPostDValue()[i];
		}
	}
	return os;
}

/*########################################
  ##########ARITHMETIC OPERATORS##########
  ########################################*/

largeFloat largeFloat::operator+ (const largeFloat& summand    ) const
{
	//basic macros
	largeFloat result;
	largeInt summand1 = this->getPreDValue();
	largeInt summand2 = summand.getPreDValue();

	//required size to adjust the postDecValues of each summand
	uint size = this->postDecValue.size() > summand.postDecValue.size() ? this->postDecValue.size() : summand.postDecValue.size();

	//we can simply add the two preDecValues
	largeInt rPreDVal = summand1 + summand2;
	largeInt rPostDVal;

	//changing summand1 and summand2 to be the postDvaluse to reuse them
	summand1 = this->getPostDValue();
	summand2 = summand.getPostDValue();

	//resizing both of them to the previously evaluated size
	summand1.resize(size, 0);
	summand2.resize(size, 0);


	//in case there is no postDecValue it's like basic integer addition
	if (summand1.size() == 0 && summand2.size() == 0)
	{
		result.preDecValue = rPreDVal;
		return result;
	}

	//otherwise this gets a little tricky
	//if either of the sizes is just 0 we can set them to just the other
	if (summand1.size() == 0) rPostDVal = summand2;
	else if (summand2.size() == 0) rPostDVal = summand1;

	//otherwise we'll calculate it
	else
	{
		//in case they're not equal we have to adjust them just a little
		//take the exampe 3.3 and -3.4 which would currently return 0.7 because .3+.4 = 7 
		//but we set them both negative so it would return .3-.4 which would be -.1, we actually want
		//-.9 though so we add a 1 at the start of the .3 making it .13 and then subtracting .4 making the desired .9
		if (summand1.getSign() != summand2.getSign())
		{
			if (summand1 < 0 && summand1.compare(summand2) == 1)
			{
				if (rPreDVal > 0)
				{
					summand2.getValue().insert(summand2.getValue().begin(), 1);
					rPreDVal--;
				}
				else rPreDVal.toNegative();
			}
			if (summand2 < 0 && summand2.compare(summand1) == 1)
			{
				if (rPreDVal > 0)
				{
					summand1.getValue().insert(summand1.getValue().begin(), 1);
					rPreDVal--;
				}
				else rPreDVal.toNegative();
			}
		}
		//afterwards we basically just add them again
		rPostDVal = summand1 + summand2;
	}

	if (rPostDVal.size() > size && rPostDVal.size() != 0)
	{
		rPreDVal++;
		rPostDVal.getValue().erase(rPostDVal.getValue().begin());
	}
	result.preDecValue = rPreDVal;

	rPostDVal.removeZerosAtEnd();
	result.postDecValue = rPostDVal;
	result.sign = result.preDecValue < 0 ? '-' : '+';
	return result;
}

largeFloat largeFloat::operator- (const largeFloat& subtrahend ) const
{
	return *this + -subtrahend;
}

largeFloat largeFloat::operator* (const largeFloat& factor     ) const
{
	//factors to multiply: x.y * w.z = wy * wz and then moving the decimal point
	largeInt factor1 = this->getPreDValue();
	factor1.append(this->getPostDValue());

	largeInt factor2 = factor.getPreDValue();
	factor2.append(factor.getPostDValue());

	//actual result value, we first multiply it and then we simply drag over the values:
	//1.3 * 1.3 = 13*13 with shifted decimal point (1.69 169)
	largeFloat result;
	result.preDecValue = factor1*factor2;

	//dragging process
	for(uint i = 0; i < this->getPostDValue().size() + factor.getPostDValue().size(); i++)
	{
		//drags one value to the other
		result.postDecValue.getValue().insert(result.postDecValue.getValue().begin(), result.getPreDValue()[result.preDecValue.size() - 1]);
		result.preDecValue.getValue().pop_back();
	}
	result.postDecValue.removeZerosAtEnd();

	result.sign = (this->sign == factor.sign) ? '+' : '-';
	return result;
}

largeFloat largeFloat::operator/ (const largeFloat& divisor    ) const
{
	if (divisor.compare(zero) == 0) throw "You can't divide by zero\n";
	if (this->compare(divisor) == 1) return largeFloat(1);
	if (this->compare(zero) == 0) return largeFloat(0);

	largeInt LNdividend = this->getPreDValue();
	LNdividend.append(this->getPostDValue());

	largeInt LNdivisor = divisor.getPreDValue();
	LNdivisor.append(divisor.getPostDValue());

	largeFloat result;
	result.preDecValue = LNdividend / LNdivisor;
	largeInt reminder = LNdividend % LNdivisor;

	for (uint i = 0; i < this->getPostDValue().size() + divisor.getPostDValue().size(); i++)
	{
		result.postDecValue.getValue().insert(result.postDecValue.getValue().begin(), result.getPreDValue()[result.preDecValue.size() - 1]);
		result.preDecValue.getValue().pop_back();
	}
	bool wasZero = false;
	if (result.postDecValue == 0) wasZero = true;

	result.postDecValue.removeZerosAtEnd();
	for (int i = 0; i < precision; i++)
	{
		reminder.push_back(0);
		if (reminder == 0) break;			
		result.postDecValue.append(reminder / LNdivisor);
		reminder %= LNdivisor;
	}
	if (wasZero) result.postDecValue.popFront();
	result.sign = (this->sign == divisor.sign) ? '+' : '-';
	return result;
}

/*#############################################
  ##########OPERATOR-EQUALS OPERATORS##########
  #############################################*/

largeFloat largeFloat::operator+= (const largeFloat& summand    )
{
	*this = *this + summand;
	return *this;
}

largeFloat largeFloat::operator-= (const largeFloat& subtrahend )
{
	*this = *this - subtrahend;
	return *this;
}

largeFloat largeFloat::operator*= (const largeFloat& factor     )
{
	*this = *this * factor;
	return *this;
}

largeFloat largeFloat::operator/= (const largeFloat& divisor    )
{
	*this = *this / divisor;
	return *this;
}

largeFloat largeFloat::operator++ (int x)
{
	largeFloat temp = *this;
	this->preDecValue++;
	return temp;
}

largeFloat largeFloat::operator-- (int x)
{
	largeFloat temp = *this;
	this->preDecValue++;
	return temp;
}

largeFloat largeFloat::operator++ ()
{
	this->preDecValue++;
	return *this;
}

largeFloat largeFloat::operator-- ()
{
	this->preDecValue--;
	return *this;
}

largeFloat largeFloat::operator - () const
{
	largeFloat temp = const_cast<largeFloat&>(*this);
	temp.changeSign();
	return temp;
}

/*########################################
  ##########COMPARISON OPERATORS##########
  ########################################*/


bool largeFloat::operator== (const largeFloat& test ) const
{
	if (this->preDecValue == test.preDecValue && this->postDecValue == test.postDecValue) return true;
	return false;
} 

bool largeFloat::operator > (const largeFloat& test ) const
{
	if (this->preDecValue  > test.preDecValue) return true;	
	if (this->postDecValue > test.postDecValue) return true;
	return false;
}

bool largeFloat::operator < (const largeFloat& test ) const
{
	if (this->preDecValue  < test.preDecValue) return true;
	if (this->postDecValue < test.postDecValue) return true;
	return false;
}

bool largeFloat::operator>= (const largeFloat& test ) const
{
	if (this->preDecValue  >= test.preDecValue) return true;
	if (this->postDecValue >= test.postDecValue) return true;
	return false;
}

bool largeFloat::operator<= (const largeFloat& test ) const
{
	if (this->preDecValue  <= test.preDecValue) return true;
	if (this->postDecValue <= test.postDecValue) return true;
	return false;
}

bool largeFloat::operator!= (const largeFloat& test ) const
{
	if (*this == test) return false;
	return true;
}

bool largeFloat::operator!  (                       ) const
{
	if (this->preDecValue.size() == 0 && this->postDecValue == 0) return true;
	return false;
}
