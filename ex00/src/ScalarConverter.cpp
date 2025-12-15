#include "ScalarConverter.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <iomanip>
#include <ios>

// #define DEBUG
/**************************
* CONSTRUCTORS/DESTRUCTOR *
**************************/
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& src) {
	(void)src;
}

/************
* OPERATORS *
************/
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& src)
{
	(void)src;
	return (*this);
}

/**********
* METHODS *
**********/
typedef enum e_type {
	character,
	integer,
	floating_point,
	double_float,
	pseudo_float,
	pseudo_double,
} str_type;

#define DIGITS "0123456789"

static str_type getType(std::string str)
{
	if (str == "-inff" || str == "+inff" || str == "nanf") {
		return(pseudo_float);
	}
	else if (str == "-inf" || str == "+inf" || str == "nan") {
		return(pseudo_double);
	}
	else if (str.find('f') != std::string::npos && str.length() != 1) {
		return(floating_point);
	}
	else if (str.find('.') != std::string::npos && str.length() != 1) {
		return(double_float);
	}
	else if (str.find_first_of(DIGITS) != std::string::npos) {
		return(integer);
	}
	else if (str.length() == 1 && isprint(str[0])) {
		return(character);
	}
	else {
		throw std::invalid_argument("invalid input");
	}
}

static void printChar(char c)
{
	std::cout << "char: ";
	if (c < 0)
		std::cout << "out of range\n";
	else if (isprint(c))
		std::cout << '\'' << c << '\'' << '\n';
	else
		std::cout << "Non displayable\n";
}

static void printInt(int i)
{
	std::cout << "int: ";
	std::cout << i << '\n';
}

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

static void printFloat(float f, bool fixed)
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

static void printDouble(double d, bool fixed)
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

static void printFromPseudo(std::string str)
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

static void printFromChar(char c)
{
	printChar(c);
	printInt(static_cast<int>(c));
	printFloat(static_cast<float>(c), true);
	printDouble(static_cast<double>(c), true);
}

#define OUT_OF_RANGE(X, TYPE) (\
		(X) > std::numeric_limits<TYPE>::max()\
		|| (X) < std::numeric_limits<TYPE>::min())

static void printFromInt(const char* str)
{
	char* end_ptr;
	errno = 0;
	long l = std::strtol(str, &end_ptr, 10);
	std::cout << *end_ptr << '\n';
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

	if (OUT_OF_RANGE(l, float))
		std::cout << "float: out of range\n";
	else
		printFloat(static_cast<float>(l), true);

	if (OUT_OF_RANGE(l, double))
		std::cout << "double: out of range\n";
	else
		printDouble(static_cast<double>(l), true);
}

static void printFromFloating(const char* str)
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

	if (OUT_OF_RANGE(d, float))
		std::cout << "float: out of range\n";
	else
		printFloat(static_cast<float>(d), (d - static_cast<int>(d) == 0 ? true : false));

	// useless check as it's tested at conversion
	if (OUT_OF_RANGE(d, double))
		std::cout << "double: out of range\n";
	else
		printDouble(static_cast<double>(d), (d - static_cast<int>(d) == 0 ? true : false));
}

static void printScalars(std::string str, str_type type)
{
	switch (type) {
		case character:
			printFromChar(str[0]);
			break ;
		case integer:
			printFromInt(str.c_str());
			break ;
		case floating_point:
			printFromFloating(str.c_str());
			break ;
		case double_float:
			printFromFloating(str.c_str());
			break ;
		case pseudo_float:
			printFromPseudo(str);
			break ;
		case pseudo_double:
			printFromPseudo(str);
			break ;
	}
}

static void printException(const std::exception& e)
{
	std::cout << "Error: " << e.what() << '\n';
}

int ScalarConverter::convert(std::string str)
{
	str_type type;
	try {
		type = getType(str);
	}
	catch (const std::invalid_argument& e) {
		printException(e);
		return (-1);
	}
	// std::cout << type << '\n';
	try {
		printScalars(str, type);
	}
	catch (const std::invalid_argument& e) {
		printException(e);
		return (-1);
	}
	return (0);
}
