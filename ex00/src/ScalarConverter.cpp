#include "ScalarConverter.h"
#include <stdexcept>
#include "conversion_helpers.h"
#include "print_helpers.h"

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
