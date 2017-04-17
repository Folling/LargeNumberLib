#include "largeNum.h"

largeNum null('0');

largeNum::largeNum()
{
	value.resize(1);
	value[0] = 0;
	if (*this >= null) sign = '+';
	else sign = '-';
}

largeNum::largeNum(std::string s_input)
{
	value.resize(s_input.size());
	for (uint i = 0; i < s_input.size(); i++) {
		value.at(i) = resolveChar(s_input[i]);
	}
	if (*this >= null) sign = '+';
	else sign = '-';
}

largeNum::largeNum(char c_input) {
	value.resize(1);
	value.at(0) = resolveChar(c_input);
	if (*this >= null) sign = '+';
	else sign = '-';
}

largeNum::~largeNum()
{
}

std::vector<int>& largeNum::getValue() {
	return value;
}

void largeNum::setValue(const std::vector<int>& input) {
	value = input;
}

int largeNum::compare(largeNum& toTest) {
	uint size;
	std::vector<int> tmp1 = this->getValue();
	std::vector<int> tmp2 = toTest.getValue();
	if (tmp1.size() >= tmp2.size()) size = tmp1.size();
	else size = tmp2.size();
	for (uint i = 0; i < size; i++) {
		if (tmp1.at(i) > tmp2.at(i)) return 1;
		if (tmp1.at(i) < tmp2.at(i)) return -1;
	}
	return 0;
}

largeNum& largeNum::changeSign(largeNum& lNparam) {
	if (lNparam.sign == '+') lNparam.sign = '-';
	else lNparam.sign = 'w';
	return lNparam;
}

std::istream& operator >> (std::istream& is, largeNum& val) {
	//takes a string as input then 
	//makes a number out of that stored in a vector
	std::string s_input;
	uint i = 0;
	is >> s_input;
	if (s_input[0] == '-') {
		val.sign = '-';
		s_input.erase(s_input.begin());
	}
	else val.sign = '+';
	std::vector<int> futureValue(s_input.size());
	try {
		for (; i < s_input.size(); i++) {
			futureValue.at(i) = resolveChar(s_input[i]);
		}
		val.setValue(futureValue);
		return is;
	}
	catch (const char* msg) {
		std::cout << msg;
		return is;
	}
}

std::ostream& operator <<(std::ostream& os, largeNum& outputVal) {
	if (outputVal.sign == '-') std::cout << '-';
	for (uint i = 0; i < outputVal.getValue().size(); i++) {
		os << outputVal.getValue().at(i);
	}
	return os;
}

largeNum largeNum::operator =(largeNum& setTo) {

	this->getValue().resize(setTo.getValue().size());
	for (uint i = 0; i < this->getValue().size(); i++) {
		this->getValue().at(i) = setTo.getValue().at(i);
	}
	this->sign = setTo.sign;
	return *this;
}

largeNum operator+(largeNum& summand1, largeNum& summand2) {
	largeNum returnNum;
	//macros to shorten the code
	std::vector<int> &tmp1 = summand1.getValue();
	std::vector<int> &tmp2 = summand2.getValue();
	int size = 0;
	bool storedTen = false;
	int temp = 0;

	//adapts the smaller vektor to the larger vector by resizing him and reversing him so 1 turns into 00...01
	if (tmp1.size() > tmp2.size()) {
		//puts as many 0s in front of the number as there are more digits in the other number
		size = tmp1.size();
		while (tmp1.size() != tmp2.size()) {
			tmp2.insert(tmp2.begin(), 0);
		}
	}
	else if (tmp2.size() > tmp1.size()) {
		//puts as many 0s in front of the number as there are more digits in the other number
		size = tmp2.size();
		while (tmp2.size() != tmp1.size()) {
			tmp1.insert(tmp1.begin(), 0);
		}
	}
	else size = tmp1.size();
	std::vector<int> returnValue(size + 1);
	// if a digit + a digit exceeds 10 this gets stored to be added to the next comparison
	if (summand1.sign == '+' && summand2.sign == '+') {
		//adds all numbers together from right to left
		for (int i = size - 1; i >= 0; i--) {
			temp = 0;
			//checks whether the addition exceeds 10 to store in "storedTen"
			if (tmp1.at(i) + tmp2.at(i) + storedTen > 9) {
				temp = tmp1.at(i) + tmp2.at(i) + storedTen - 10;
				storedTen = true;
			}
			else {
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
	else if (summand1.sign == '-' && summand2.sign == '-') {
		returnNum.sign = '-';
		//adds all numbers together from right to left
		for (int i = size - 1; i >= 0; i--) {
			temp = 0;
			//checks whether the addition exceeds 10 to store in "storedTen"
			if (tmp1.at(i) + tmp2.at(i) + storedTen > 9) {
				temp = tmp1.at(i) + tmp2.at(i) + storedTen - 10;
				storedTen = true;
			}
			else {
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
	else {
		if (summand1.compare(summand2) == 0) return null; // -x + x = 0
		else {
			if (summand1.compare(summand2) == 1) returnNum.sign = summand1.sign;
			else returnNum.sign = summand2.sign;
		}
		//for more information on how this part works check: https://www.youtube.com/watch?v=PS5p9caXS4U
		int chosenMethod;
		//turns the in the video described method, summand which will function as the subtrahend and changes it as required
		if (summand1.sign == '-') {
			chosenMethod = 1;
			for (int i = 0; i < size; i++) {
				if (i == (size - 1)) {
					tmp1.at(i) = (10 - tmp1.at(i));
					break;
				}
				tmp1.at(i) = (9 - tmp1.at(i));
			}
		}
		else {
			chosenMethod = 2;
			for (int i = 0; i < size; i++) {
				if (i == (size - 1)) {
					tmp2.at(i) = (10 - tmp2.at(i));
					break;
				}
				tmp2.at(i) = (9 - tmp2.at(i));
			}
		}
		//adds newly created vector with the original summand
		for (int i = size - 1; i >= 0; i--) {
			temp = 0;
			//checks whether the addition exceeds 10 to store in "storedTen"
			if (tmp1.at(i) + tmp2.at(i) + storedTen > 9) {
				temp = tmp1.at(i) + tmp2.at(i) + storedTen - 10;
				storedTen = true;
			}
			else {
				temp = tmp1.at(i) + tmp2.at(i) + storedTen;
				storedTen = false;
			}
			returnValue.at(i + 1) = temp;
		}
		if (storedTen == true) returnValue.insert(returnValue.begin() , 1);
		while (returnValue.at(0) == 0 && returnValue.size() != 1) returnValue.erase(returnValue.begin());
		//in case the first summand is negative and smaller than the second or the second summand is the first digit gets removed
		//otherwise the first digit has to stay due to negative numbers
		if ((chosenMethod == 1 && returnNum.sign != summand1.sign) || (chosenMethod == 2 && returnNum.sign != summand2.sign)) {
			returnValue.erase(returnValue.begin());
		}
		//method doesn't work for negative numbers so we adapt it
		//hereby we take the invert of the values
		if(returnNum.sign=='-'){
			for (int i = 0; i < returnValue.size(); i++) {				
				if (returnValue.at(i) == 0) {
					returnValue.at(i) = 0;
					continue;
				}
				//this needs to be done because with multiple of ten we have to take the extreme invert but otherwise 
				//we only need to subtract 10 at the last digit and 9 otherwise
				if (returnValue.at(returnValue.size() - 1) == 0) {
					if (i == (returnValue.size() - 1)) returnValue.at(i) = (10 - returnValue.at(i));
					else returnValue.at(i) = (10 - returnValue.at(i));
				}
				else {
					if (i == (returnValue.size() - 1)) returnValue.at(i) = (10 - returnValue.at(i));
					else returnValue.at(i) = (9 - returnValue.at(i));
				}
			}
		}
	}
	//gets rid of all 0s in front;
	while (returnValue.at(0) == 0 && returnValue.size() != 1) returnValue.erase(returnValue.begin());
	returnNum.setValue(returnValue);
	return returnNum;
}

largeNum operator-(largeNum& minuend, largeNum& subtrahend) {
	return (minuend + (-(subtrahend)));
}

largeNum operator*(largeNum factor1, largeNum factor2){
	std::vector<int> tmp1 = factor1.getValue();
	std::vector<int> tmp2 = factor2.getValue();
	if (factor2 == null) return null; //if the second factor is 0 return 0;
	largeNum result = factor1;
	//adds the first value to itself for factor 2 times;
	while (--factor2 != null) {
		result += factor1;
	}
	return result;
}

largeNum largeNum::operator+=(largeNum& addent) {
	*this = *this + addent;
	return *this;
}

largeNum largeNum::operator-=(largeNum& subtrahend) {
	*this = *this - subtrahend;
	return *this;
}

largeNum largeNum::operator++ (int x) {
	static largeNum tmp(*this);
	this->value[getValue().size() - 1]++;
	return tmp;
}

largeNum largeNum::operator++() {
	//goes with a loop through the vector until iterating a digit by +1 won't result in a ten-overflow
	for (int j = 1; j < getValue().size() - 1; j++) {
		if (((value[getValue().size() - j] + ((this->sign=='+')? 1 : - 1) % 10) == 0)) {
			value[getValue().size() - j] = 0;
		}
		else {
			if (this->sign == '+') value[getValue().size() - j] += 1;
			else value[getValue().size() - j] -= 1;
			break;
		}
	}
	return *this;
}

largeNum largeNum::operator-- (int x) {
	static largeNum tmp(*this);
	this->value[getValue().size() - 1]--;
	return tmp;
}

largeNum largeNum::operator--() {
	this->value[getValue().size() - 1]--;
	return *this;
}

largeNum largeNum::operator-() {
	if (this->sign == '+')this->sign = '-';
	else this->sign = '+';
	return *this;
}

bool largeNum::operator==(largeNum& test) {
	std::vector<int> &tmp1 = this->getValue();
	std::vector<int> &tmp2 = test.getValue();
	return (this->compare(test) == 0)? true : false;
}

bool largeNum::operator>(largeNum& test) {
	if (this->sign == '+' && test.sign == '-') return true;
	if (this->sign != test.sign) return false;
	if (this->sign == '+' && test.sign == '+') {
		if (this->compare(test) == 0) return false;
		if (this->compare(test) ==-1) return false;
		return true;
	}
	else {
		if (this->compare(test) == 0) return false;
		if (this->compare(test) == 1) return false;
		return true;
	}
}

bool largeNum::operator<(largeNum& test) {
	if (this->sign == '-' && test.sign == '+') return true;
	else if (this->sign != test.sign) return false;
	if (this->sign == '+' && test.sign == '+') {
		if (this->compare(test) == 0) return false;
		if (this->compare(test) == -1) return false;
		return true;
	}
	else {
		if (this->compare(test) == 0) return false;
		if (this->compare(test) == 1) return false;
		return true;
	}
}

bool largeNum::operator<=(largeNum& test) {
	if (this->compare(test) == 0) return true;
	if (this->compare(test) ==-1) return true;
	else return false;
}

bool largeNum::operator>=(largeNum& test) {
	if (this->compare(test) == 0) return true;
	if (this->compare(test) ==-1) return true;
	else return false;
}

bool largeNum::operator !=(largeNum& test) {
	if (this->getValue() == test.getValue()) return false;
	return true;
}

bool largeNum::operator !() {
	if (this->getValue().size() > 0) return false;
	return true;
}

