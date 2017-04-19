#include <iostream>
#include <string>
#include <conio.h>
#include "largeNum.h"

int main() {
	largeNum a, b;
	int aint;
	while (true) {
		std::cin >> aint;
		//std::cin >> b;
		a = aint;
		try {
			std::cout << a<< std::endl;
		}
		catch(const char* msg)
		{
			std::cout << msg;
		}
	}
	_getch();
}