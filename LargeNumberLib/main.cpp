#include <iostream>
#include <string>
#include <conio.h>
#include "largeNum.h"

int main() {
	largeNum a, b;
	largeNum null("0");
	while (true) {
		std::cin >> a;
		//std::cin >> b;
		a++;
		std::cout << a << std::endl;
	}
	_getch();
}