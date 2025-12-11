#include "ScalarConverter.h"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "You have to specify one argument\n";
		return (-1);
	}
	if (ScalarConverter::convert(argv[1]) == -1)
		return (-1);
	return (0);
}
