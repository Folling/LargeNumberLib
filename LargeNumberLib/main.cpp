#include <iostream>
#include <string>
#include <conio.h>
#include "largeNum.h"

int main() {
	largeNum a, b;
	while (true) {
		std::cin >> a;
		//std::cin >> b;
		try {
			std::cout << factorial(a) << std::endl;
			std::cout << a;
		}
		catch(const char* msg)
		{
			std::cout << msg;
		}
	}
	_getch();
}