#include <iostream>
#include <string>
#include "largeInt.h"
#include "largeFloat.h"
#include <ctime>

int main() {
	largeFloat a;
	largeFloat b;
	largeFloat x(1234, 0);
	largeInt c;
	largeInt d;
	setPrecision(1000);
	while (true) {
		try {
			std::cin >> c;
			//std::cin >> b;
			clock_t begin = clock();
			std::cout << x << std::endl;
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