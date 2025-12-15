#include <iomanip>
#include <iostream>

static int setFixed()
{
	int default_precision = std::cout.precision();
	std::cout << std::fixed << std::setprecision(1);
	return (default_precision);
}

static void resetIOSFlags(int precision)
{
	std::cout << std::setprecision(precision);
	std::cout.unsetf(std::ios_base::floatfield);
}

void printChar(char c)
{
	std::cout << "char: ";
	if (c < 0)
		std::cout << "out of range\n";
	else if (isprint(c))
		std::cout << '\'' << c << '\'' << '\n';
	else
		std::cout << "Non displayable\n";
}

void printInt(int i)
{
	std::cout << "int: ";
	std::cout << i << '\n';
}

void printFloat(float f, bool fixed)
{
	std::cout << "float: ";
	int default_precision;
	if (fixed) {
		default_precision = setFixed();
	}
	std::cout << f << "f\n";
	if (fixed) {
		resetIOSFlags(default_precision);
	}
}

void printDouble(double d, bool fixed)
{
	std::cout << "double: ";
	int default_precision;
	if (fixed) {
		default_precision = setFixed();
	}
	std::cout << d << '\n';
	if (fixed) {
		resetIOSFlags(default_precision);
	}
}

void printException(const std::exception& e)
{
	std::cout << "Error: " << e.what() << '\n';
}
