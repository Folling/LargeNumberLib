#include "largeNum.h"

largeNum zero('0');
largeNum one('1');
largeNum negZero = -zero;

largeNum::largeNum()
{
	value.resize(1);
	value[0] = 0;
	sign = '+';
}

largeNum::largeNum(std::string s_input)
{
	sign = '+';
	uint i = 1;
	if (s_input[0] == '-') sign = '-';
	else i--;
	value.resize(s_input.size());
	for (; i < s_input.size(); i++) {
		value.at(i) = resolveChar(s_input[i]);
	}	
}

largeNum::largeNum(char c_input) {
	value.resize(1);
	value.at(0) = resolveChar(c_input);	
	sign = '+';
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
	if (tmp1.size() > tmp2.size()) return 1;
	else if (tmp1.size() < tmp2.size()) return -1;
	else size = tmp1.size();
	for (uint i = 0; i < size; i++) {
		if (tmp1.at(i) > tmp2.at(i)) return 1;
		if (tmp1.at(i) < tmp2.at(i)) return -1;
	}
	return 0;
}

largeNum& largeNum::changeSign() {
	if (this->sign == '+') this->sign = '-';
	else this->sign = '+';
	return *this;
}

char largeNum::getSign() const{
	return this->sign;
}

/*###################################
  ##########SHIFT OPERATORS##########
  ###################################*/

std::istream& operator >> (std::istream& is, largeNum& val) {
	//takes a string as input then 
	//makes a number out of that stored in a vector
	std::string s_input;
	uint i = 0;
	val.sign = '+';
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

/*##########################################
  ##########MATHEMATICAL FUNCTIONS##########
  ##########################################*/

largeNum factorial(largeNum& input) {
	if (input > one) return (input * factorial(input-one));
	else return one;
}

/*########################################
  ##########ARITHMETIC OPERATORS##########
  ########################################*/

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
	largeNum LNtmp1 = summand1;
	largeNum LNtmp2 = summand2;
	std::vector<int> &tmp1 = LNtmp1.getValue();
	std::vector<int> &tmp2 = LNtmp2.getValue();
	int size;
	bool storedTen = false;
	int temp;
	if (LNtmp1 == zero) return summand2;
	if (LNtmp2 == zero) return summand1;
	//adapts the smaller vector to the larger vector by resizing him and reversing him so 1 turns into 00...01
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
	if (LNtmp1.sign == '+' && LNtmp2.sign == '+') {
		//adds all numbers together from right to left
		for (int i = size - 1; i >= 0; i--) {
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
	else if (LNtmp1.sign == '-' && LNtmp2.sign == '-') {
		returnNum.sign = '-';
		//adds all numbers together from right to left
		for (int i = size - 1; i >= 0; i--) {
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
		if (LNtmp1.compare(LNtmp2) == 0) return zero; // -x + x = 0
		if (LNtmp1.compare(LNtmp2) == 1) returnNum.sign = LNtmp1.sign;
		else returnNum.sign = LNtmp2.sign;
		//for more information on how this part works check: https://www.youtube.com/watch?v=PS5p9caXS4U
		//turns the in the video described method, summand which will function as the subtrahend and changes it as required
		//with the difference that it doesn't reduce it by 10 at the end since we will invert the result
		if (LNtmp1.sign == '-') {
			for (int i = 0; i < size; i++) {
				//in either case if the digit is 0 it must not be inverted due to us using negative numbers
				if (i == size - 1) {
					tmp1.at(i) = (10 - tmp1.at(i));
					break;
				}
				tmp1.at(i) = (9 - tmp1.at(i));
			}
		}
		else {
			largeNum tmp;
			if (LNtmp2 > LNtmp1) returnNum.changeSign();
			tmp = LNtmp1;
			LNtmp1 = LNtmp2;
			LNtmp2 = tmp;
			for (int i = 0; i < size; i++) {
				if (i == size - 1) {
					tmp1.at(i) = (10 - tmp1.at(i));
					break;
				}
				tmp1.at(i) = (9 - tmp1.at(i));
			}
		}
		//adds newly created vector with the original summand
		for (int i = size - 1; i >= 0; i--) {
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
		//method doesn't work for negative numbers so we adapt it
		//hereby we take the invert of the values
		//since we only want to do 10-.at(i) we check whether it's already been done
		if (returnNum.sign == '-') {
			bool addedTen = false;
			for (int i = (returnValue.size() - 1); i >= 0; i--) {
				if (returnValue.at(i) == 0 && addedTen == false) continue;
				if (addedTen == false) {
					returnValue.at(i) = 10 - returnValue.at(i);
					addedTen = true;
				}
				//inverts the result because of negativity
				else {
					returnValue.at(i) = 9 - returnValue.at(i);
				}
				if (addedTen == false)returnValue.at(returnValue.size() - 1)++;
			}
		}
		if (returnNum.sign == '+') {
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

largeNum operator-(largeNum& minuend, largeNum& subtrahend) {
	largeNum result = (minuend + -subtrahend);
	return result;
}

largeNum operator*(largeNum& factor1, largeNum& factor2){
	if (factor1 == zero || factor2 == zero || factor1 == negZero || factor2 == negZero) return zero;	
	largeNum result = zero;
	//if you multiply e.g. 4 with 4 you get 16 so 6 carryover 1	
	int carryOver = 0;
	largeNum toAdd = zero;
	//macros
	std::vector<int>& tmp1 = factor1.getValue();
	std::vector<int>& tmp2 = factor2.getValue();	
	std::vector<int>& tmp3 = toAdd.getValue();
	std::vector<int>& tmp4 = result.getValue();
	//goes through each digit from factor 2 and multiplies it with each digit from factor 1 adding the values together
	for (int i = tmp2.size() - 1; i >= 0; i--) {
		for (int j = tmp1.size() - 1; j >= 0; j--) {
			int temp = tmp1.at(j) * tmp2.at(i) + carryOver;
			carryOver = temp / 10;
			tmp3.insert(tmp3.begin(), temp % 10);						
		}
		//to adapt since the digits in this kind of multiplication are technically shifted.
		int zeroExtender = tmp2.size()-1 - i;
		while (zeroExtender != 0) {
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
	while (tmp4.at(0) == 0) tmp4.erase(tmp4.begin());
	//since multiplication disregards signs when it comes to value
	//the end sign is determined by the input signs though.
	if (factor1.sign == factor2.sign) result.sign = '+';
	else result.sign = '-';
	return result;
}

largeNum operator/(largeNum& factor1, largeNum& factor2) {
	//old method was way too slow at higher values so it was basically pointless. 
	//needs to have a more efficent way, probably with subtraction
	//or just implement the normal division you'd do by paper
	largeNum dummy('1');
	return dummy;
}

/*#############################################
  ##########OPERATOR-EQUALS OPERATORS##########
  #############################################*/

largeNum largeNum::operator+=(largeNum& addent) {
	*this = *this + addent;
	return *this;
}

largeNum largeNum::operator-=(largeNum& subtrahend) {
	*this = *this - subtrahend;
	return *this;
}

largeNum largeNum::operator*=(largeNum& factor){
	*this = *this*factor;
	return *this;
}

/*#######################################
  ##########INCREMENT OPERATORS##########
  #######################################*/

largeNum largeNum::operator++ (int x) {
	largeNum tmp(*this);
	*this += one;
	return tmp;
}

largeNum largeNum::operator++() {
	*this += one;
	return *this;
}

largeNum largeNum::operator-- (int x) {
	largeNum tmp(*this);
	*this -= one;
	return tmp;
}

largeNum largeNum::operator--() {
	*this -= one;
	return *this;
}

largeNum largeNum::operator -() const {
	largeNum result = *this;
	result.changeSign();
	return result;
}

/*######################################
  #########COMPARISON OPERATORS#########
  ######################################*/

bool largeNum::operator==(largeNum& test) {
	if (this->sign != test.sign) return false;
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
		if (this->compare(test) == 1) return false;
		return true;
	}
	else {
		if (this->compare(test) == 0) return false;
		if (this->compare(test) ==-1) return false;
		return true;
	}
}

bool largeNum::operator<=(largeNum& test) {
	if (*this == test) return true;
	if (*this  < test) return true;
	else return false;
}

bool largeNum::operator>=(largeNum& test) {
	if (*this == test) return true;
	if (*this  > test) return true;
	else return false;
}

bool largeNum::operator !=(largeNum& test){
	if (*this==test) return false;
	return true;
}

bool largeNum::operator !(){
	if (this->getValue().size() > 0) return false;
	return true;
}