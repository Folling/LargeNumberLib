#include <iostream>
#include <string>
#include <conio.h>
#include "largeNum.h"

int main() {
	largeNum a, b;
	int aint;
	while (true) {
		std::cin >> a;
		std::cin >> b;
		try {
			std::cout << a/b << std::endl;
		}
		catch(const char* msg)
		{
			std::cout << msg;
		}
	}
	_getch();
}