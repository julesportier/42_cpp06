#include "ScalarConverter.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <cstdlib>

/**************************
* CONSTRUCTORS/DESTRUCTOR *
**************************/
// Why doing that, it's nonsense
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
} str_type;

typedef struct s_scalar_types {
	char c;
	int i;
	float f;
	double d;
} scalar_types;

#define DIGITS "0123456789"

static str_type getType(std::string str)
{
	if (str.find('f') != std::string::npos && str.length() != 1) {
		return(floating_point);
	}
	else if (str.length() == 1 && isprint(str[0])) {
		return(character);
	}
	else if (str.find('.') != std::string::npos) {
		return(double_float);
	}
	else if (str.find_first_of(DIGITS) != std::string::npos) {
		return(integer);
	}
	else {
		throw std::invalid_argument("invalid input");
	}
}

static scalar_types scalarsFromChar(char c)
{
	scalar_types scalars;
	scalars.c = c;
	scalars.i = static_cast<int>(scalars.c - '0');
	scalars.f = static_cast<float>(scalars.c - '0');
	scalars.d = static_cast<double>(scalars.c - '0');
	return (scalars);
}

static scalar_types scalarsFromInt(const char* str)
{
	scalar_types scalars;
	char* end_ptr;
	long l = std::strtol(str, &end_ptr, 10);
	if (*end_ptr != '\0')
		throw std::invalid_argument("invalid input");
	// if (l > std::numeric_limits<int>::max())
	// handled by static cast ?
	scalars.i = static_cast<int>(l);
	scalars.f = static_cast<float>(l);
	scalars.d = static_cast<double>(l);
	scalars.c = static_cast<char>(l);
	return (scalars);
}

static scalar_types scalarsFromFloating(const char* str)
{
	scalar_types scalars;
	char* end_ptr;
	scalars.d = std::strtod(str, &end_ptr);
	if (*end_ptr != '\0')
		throw std::invalid_argument("invalid input");
	// if (l > std::numeric_limits<int>::max())
	// handled by static cast ?
	scalars.i = static_cast<int>(scalars.d);
	scalars.f = static_cast<float>(scalars.d);
	scalars.c = static_cast<char>(scalars.d);
	return (scalars);
}

static scalar_types generateScalars(std::string str, str_type type)
{
	scalar_types scalars;
	switch (type) {
		case character:
			scalars = scalarsFromChar(str[0]);
			break ;
		case integer:
			scalars = scalarsFromInt(str.c_str());
			break ;
		case floating_point:
			scalars = scalarsFromFloating(str.c_str());
			break ;
		case double_float:
			scalars = scalarsFromFloating(str.c_str());
			break ;
	}
	return (scalars);
}

static void printException(const std::exception& e)
{
	std::cout << "Error: " << e.what() << '\n';
}

// TODO: add correct formating
void printScalars(scalar_types scalars)
{
	std::cout << "char: " << scalars.c << '\n';
	std::cout << "int: " << scalars.i << '\n';
	std::cout << "float: " << scalars.f << '\n';
	std::cout << "double: " << scalars.d << '\n';
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
	scalar_types scalars;
	try {
		scalars = generateScalars(str, type);
	}
	catch (const std::invalid_argument& e) {
		printException(e);
		return (-1);
	}
	printScalars(scalars);
	return (0);
}
