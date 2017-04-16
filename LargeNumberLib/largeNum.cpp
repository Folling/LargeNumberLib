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
	for (int i = 0; i < size; i++) {
		if (tmp1.at(i) > tmp2.at(i)) return 1;
		if (tmp1.at(i) < tmp2.at(i)) return -1;
	}
	return 0;
}

std::istream& operator >> (std::istream& is, largeNum& val) {
	//takes a string as input then 
	//makes a number out of that stored in a vector
	std::string s_input;
	uint i = 0;
	is >> s_input;
	if (s_input[0] == '-') {
		val.sign = '-';
		i++;
	}
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
		else returnValue.erase(returnValue.begin());
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
		//should the last addition have been larger than 10 the end number will have to be increased by one more digit 
		//e.g. 5+5 = 10

		if (storedTen == false) returnValue.erase(returnValue.begin(), returnValue.begin() + 2);
		returnNum.setValue(returnValue);
	}
	//case for when the signs are different
	else if (summand1.sign != summand2.sign) {
		if (summand1.compare(summand2) == 0) return null; // -x + x = 0
		else {
			if (summand1.compare(summand2) == 1) returnNum.sign = summand1.sign;
			else returnNum.sign = summand2.sign;
		}
		//adds all numbers together from right to left
		for (int i = size - 1; i >= 0; i--) {
			temp = 0;
			//checks whether the addition exceeds 10 to store in "storedTen"
			if (tmp1.at(i) - tmp2.at(i) - storedTen < 0) {
				temp = abs(tmp1.at(i) - tmp2.at(i) - storedTen);
				storedTen = true;
			}
			else {
				temp = tmp1.at(i) - tmp2.at(i) - storedTen;
				storedTen = false;
			}
			returnValue.at(i + 1) = temp;
		}
		//should the last addition have been larger than 10 the end number will have to be increased by one more digit
		if (storedTen == true) returnValue.erase(returnValue.begin());
		returnNum.setValue(returnValue);
	}
	return returnNum;
}


largeNum operator-(largeNum& minuend, largeNum& subtrahend) {
	largeNum returnNum;
	std::vector<int> &tmp1 = minuend.getValue();
	std::vector<int> &tmp2 = subtrahend.getValue();
	int size = 0;
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
	//value of the number that will be returned
	std::vector<int> returnValue(size + 1);
	// if a digit - a digit exceeds 10 this gets stored to be added to the next comparison
	bool storedTen = false;
	int temp = 0;
	//adds all numbers together from right to left
	for (int i = size - 1; i >= 0; i--) {
		temp = 0;
		//checks whether the addition exceeds 10 to store in "storedTen"
		if (tmp1.at(i) - tmp2.at(i) - storedTen < -9) {
			temp = tmp1.at(i) - tmp2.at(i) - storedTen - 10;
			storedTen = true;
		}
		else {
			temp = tmp1.at(i) - tmp2.at(i) - storedTen;
			storedTen = false;
		}
		returnValue.at(i + 1) = temp;
	}
	if (!storedTen) returnValue.erase(returnValue.begin());
	if (returnNum.sign == '-') returnValue.erase(returnValue.begin());
	returnNum.setValue(returnValue);
	return returnNum;
}

largeNum operator*(largeNum factor1, largeNum factor2) {
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

largeNum largeNum::operator++ (int x) {
	static largeNum tmp(*this);
	this->value[getValue().size() - 1]++;
	return tmp;
}

largeNum largeNum::operator++() {
	this->value[getValue().size() - 1]++;
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
	if (tmp1.size() == tmp2.size() && this->sign == test.sign) {
		for (uint i = 0; i < tmp1.size(); i++) {
			if (tmp1.at(i) != tmp2.at(i)) return false;
		}
		return true;
	}
	else return false;
}

bool largeNum::operator>(largeNum& test) {
	if (this->sign == '+' && test.sign == '-') return true;
	if (this->sign != test.sign) return false;
	if (this->sign == '+' && test.sign == '+') {
		if (this->getValue() == test.getValue()) return false;
		if (this->getValue() < test.getValue()) return false;
		return true;
	}
	else {
		if (this->getValue() == test.getValue()) return false;
		if (this->getValue() > test.getValue()) return false;
		return true;
	}
}

bool largeNum::operator<(largeNum& test) {
	if (this->sign == '+' && test.sign == '-') return true;
	if (this->sign != test.sign) return false;
	if (this->sign == '+' && test.sign == '+') {
		if (this->getValue() == test.getValue()) return false;
		if (this->getValue() > test.getValue()) return false;
		return true;
	}
	else {
		if (this->getValue() == test.getValue()) return false;
		if (this->getValue() < test.getValue()) return false;
		return true;
	}
}

bool largeNum::operator<=(largeNum& test) {
	if (this->getValue() == test.getValue()) return true;
	if (this->getValue()  < test.getValue()) return true;
	else return false;
}

bool largeNum::operator>=(largeNum& test) {
	if (this->getValue() == test.getValue()) return true;
	if (this->getValue()  > test.getValue()) return true;
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

