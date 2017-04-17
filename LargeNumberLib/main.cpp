#include <iostream>
#include <string>
#include <conio.h>
#include "largeNum.h"

int main() {
	largeNum a, b;	
	while (true) {		
		std::cin >> a;
		std::cin >> b;
		std::cout << a*b << std::endl;
	}
	_getch();
}