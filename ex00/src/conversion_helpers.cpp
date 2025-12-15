#include <iostream>
#include <limits>
#include <errno.h>
#include <cstdlib>
#include "print_helpers.h"
#include "conversion_helpers.h"

void printFromPseudo(std::string str)
{
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";
	if (str.find("nan") != std::string::npos) {
		printFloat(std::numeric_limits<float>::quiet_NaN(), false);
		printDouble(std::numeric_limits<double>::quiet_NaN(), false);
	}
	else if (str.find("-inf") != std::string::npos) {
		printFloat(-std::numeric_limits<float>::infinity(), false);
		printDouble(-std::numeric_limits<double>::infinity(), false);
	}
	else if (str.find("+inf") != std::string::npos) {
		std::cout << "float: +" << std::numeric_limits<float>::infinity() << "f\n";
		std::cout << "double: +" << std::numeric_limits<double>::infinity() << '\n';
	}
	else {
		throw std::invalid_argument("invalid input");
	}
}

void printFromChar(char c)
{
	printChar(c);
	printInt(static_cast<int>(c));
	printFloat(static_cast<float>(c), true);
	printDouble(static_cast<double>(c), true);
}

void printFromInt(const char* str)
{
	char* end_ptr;
	errno = 0;
	long l = std::strtol(str, &end_ptr, 10);
	if (*end_ptr != '\0' || errno)
		throw std::invalid_argument("invalid input");

	if (l > 127 || l < 0)
		printChar(static_cast<char>(-1));
	else
		printChar(static_cast<char>(l));

	if (OUT_OF_RANGE(l, int))
		std::cout << "int: out of range\n";
	else
		printInt(static_cast<int>(l));

	if (OUT_OF_RANGE_F(l, float))
		std::cout << "float: out of range\n";
	else
		printFloat(static_cast<float>(l), true);

	if (OUT_OF_RANGE_F(l, double))
		std::cout << "double: out of range\n";
	else
		printDouble(static_cast<double>(l), true);
}

void printFromFloating(const char* str)
{
	char* end_ptr;
	errno = 0;
	double d = std::strtod(str, &end_ptr);
	if (!(*end_ptr == '\0'
				|| (*end_ptr == 'f' && *(end_ptr + 1) == '\0'))
			|| errno)
		throw std::invalid_argument("invalid input");

	if (d > 127 || d < 0)
		printChar(static_cast<char>(-1));
	else
		printChar(static_cast<char>(d));

	if (OUT_OF_RANGE(d, int))
		std::cout << "int: out of range\n";
	else
		printInt(static_cast<int>(d));

	if (OUT_OF_RANGE_F(d, float))
		std::cout << "float: out of range\n";
	else
		printFloat(static_cast<float>(d), (d - static_cast<int>(d) == 0 ? true : false));

	printDouble(static_cast<double>(d), (d - static_cast<int>(d) == 0 ? true : false));
}
