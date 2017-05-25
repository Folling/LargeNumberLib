#include <iostream>
#include <string>
#include "largeInt.h"
#include "largeFloat.h"
#include <ctime>

int main() {
	Decimal::largeFloat a;
	Decimal::largeFloat b;
	Decimal::largeInt c;
	Decimal::largeInt d;
	Decimal::setPrecision(1000);
	while (true) {
		try {
			std::cin >> a;
			std::cin >> b;
			clock_t begin = clock();
			std::cout << (a/b) << std::endl;
			clock_t end = clock();
			double elapsed_secs = static_cast<double>(end - begin)*1000/ CLOCKS_PER_SEC;
			std::cout << "Time needed :" << elapsed_secs << "ms\n";
		}
		catch (const char* msg)
		{
			std::cerr << msg;
		}
	}
}