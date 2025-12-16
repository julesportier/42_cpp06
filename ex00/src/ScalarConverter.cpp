#include "ScalarConverter.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include <errno.h>
#include "helpers.h"

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

static void printFromPseudo(std::string str)
{
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";
	if (str.find("nan") != std::string::npos) {
		printFloat(std::numeric_limits<float>::quiet_NaN());
		printDouble(std::numeric_limits<double>::quiet_NaN());
	}
	else if (str.find("-inf") != std::string::npos) {
		printFloat(-std::numeric_limits<float>::infinity());
		printDouble(-std::numeric_limits<double>::infinity());
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
	printFloat(static_cast<float>(c));
	printDouble(static_cast<double>(c));
}

static void printFromNumber(const char* str)
{
	char* end_ptr;
	errno = 0;
	double d = std::strtod(str, &end_ptr);
	if (*end_ptr != '\0' || errno) {
		errno = 0;
		throw std::invalid_argument("invalid input");
	}

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
		printFloat(static_cast<float>(d));

	if (OUT_OF_RANGE_F(d, double))
		std::cout << "double: out of range\n";
	else
		printDouble(static_cast<double>(d));
}

static void printScalars(std::string str, str_type type)
{
	switch (type) {
		case character:
			printFromChar(str[0]);
			break ;
		case integer:
			printFromNumber(str.c_str());
			break ;
		case floating_point:
			printFromNumber(str.c_str());
			break ;
		case double_float:
			printFromNumber(str.c_str());
			break ;
		case pseudo_float:
			printFromPseudo(str);
			break ;
		case pseudo_double:
			printFromPseudo(str);
			break ;
	}
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
	try {
		printScalars(str, type);
	}
	catch (const std::invalid_argument& e) {
		printException(e);
		return (-1);
	}
	return (0);
}
