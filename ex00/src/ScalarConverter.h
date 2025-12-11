#ifndef SCALARCONVERTER_H
# define SCALARCONVERTER_H

# include <string>

class ScalarConverter {
public:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& src);
	ScalarConverter& operator=(const ScalarConverter& src);
	virtual ~ScalarConverter() = 0;

	static int convert(std::string str);
};

#endif
