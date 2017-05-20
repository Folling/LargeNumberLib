#include "largeFloat.h"



largeFloat::largeFloat()
{
	preDecValue.getValue().resize(1);
	preDecValue.getValue().at(0) = 0;
	postDecValue.getValue().resize(1);
	postDecValue.getValue().at(0) = 0;
	sign = '+';
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

char largeFloat::getSign() const
{
	return this->sign;
}

/*##########################
  ##########ASSETS##########
  ##########################*/

/**
 * \brief compares the absolute value of two numbers
 * \param toTest 
 * \return 
 */
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
	while (sVal.getValue().at(0) == 0 && sVal.getValue().size() != 1) sVal.getValue().erase(sVal.getValue().begin());
	return *this;
}

largeFloat largeFloat::toPositive()
{
	if (this->sign == '-') this->changeSign();
	return *this;
}

largeFloat largeFloat::toNegative()
{
	if (this->sign == '+') this->changeSign();
	return *this;
} 

largeFloat largeFloat::changeSign()
{
	if (this->sign == '+') this->sign = '-';
	else this->sign = '+';
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
	for(uint i = 0; i < s_input.size(); i++)
	{
		if (s_input.at(i) == 0 && s_input.size() != 1) s_input.erase(s_input.begin());
	}
	if (s_input[0] > 57 || s_input[0] < 48 && s_input[0] != 44 && s_input[0] != 46) throw "Error: Please only enter one minus sign!\n";
	std::vector<int> futureValue(s_input.size());
	try
	{
		uint i = 0;
		for (; i < s_input.size(); i++)
		{
			if (s_input[i] == '.') {
				if (i == 0) val.getPreDValue().getValue().insert(val.getPreDValue().getValue().begin(), 0);
				i++;
				break;				
			}
			if (val.getPreDValue().size() == 0) val.getPreDValue().getValue().insert(val.getPreDValue().getValue().begin(), resolveChar(s_input[i]));
			else val.getPreDValue().push_back(resolveChar(s_input[i]));
		}
		for(; i < s_input.size(); i++)
		{
			if (s_input[i] == '.') throw "Error, can't enter more than one decimal point\n";
			if (val.getPostDValue().size() == 0) val.getPostDValue().getValue().insert(val.getPostDValue().getValue().begin(), resolveChar(s_input[i]));
			else val.getPostDValue().push_back(resolveChar(s_input[i]));
		}
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
	if (outputVal.preDecValue.getSign() == '-') std::cout << '-';
	const_cast<largeFloat&>(outputVal).removeZerosAtStart();
	for (uint i = 0; i < outputVal.getPreDValue().size(); i++)
	{
		os << outputVal.getPreDValue()[i];
	}
	if(outputVal.getPostDValue().size() > 0)
	{
		if (outputVal.getPostDValue().size() == 1 && outputVal.getPostDValue()[0] == 0) return os;
		std::cout << '.';
		for(uint i = 0; i < outputVal.getPostDValue().size(); i++)
		{
			os << outputVal.getPostDValue()[i];
		}
	}
	return os;
}

largeFloat largeFloat::operator+(const largeFloat& summand) const
{
	largeFloat result;
	largeInt summand1 = this->getPreDValue();
	largeInt summand2 = summand.getPreDValue();
	uint size = this->postDecValue.size() > summand.postDecValue.size() ? this->postDecValue.size() : summand.postDecValue.size();
	largeInt rPreDVal = summand1 + summand2;
	summand1 = this->getPostDValue();
	summand2 = summand.getPostDValue();
	result.preDecValue = rPreDVal;
	largeInt rPostDVal;
         if (summand1.size() > summand2.size()) summand2.resize(summand1.size(), 0);
	else if (summand1.size() < summand2.size()) summand1.resize(summand2.size(), 0);
	if (summand1.size() == 0 && summand2.size() == 0) return result;
	if(summand1.size() == 0) rPostDVal = summand2;
	else if(summand2.size() == 0) rPostDVal = summand1;
	else rPostDVal = summand1 + summand2;	
	if(rPostDVal.size() > size && rPostDVal.size() != 0)
	{
		rPreDVal.push_back(rPostDVal[0]);
		rPostDVal.getValue().erase(rPostDVal.getValue().begin());
	}
	result.postDecValue = rPostDVal;
	result.sign = result.preDecValue < 0 ? '-' : '+';
	return result;
	//set up negative numbers and subtraction in here as well
}