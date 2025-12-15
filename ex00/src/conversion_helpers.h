#ifndef CONVERSION_HELPERS_H
# define CONVERSION_HELPERS_H

# include <string>

# define OUT_OF_RANGE(X, TYPE) (\
		(X) > std::numeric_limits<TYPE>::max()\
		|| (X) < std::numeric_limits<TYPE>::min())

#define DIGITS "0123456789"

typedef enum e_type {
	character,
	integer,
	floating_point,
	double_float,
	pseudo_float,
	pseudo_double,
} str_type;

void printFromPseudo(std::string str);
void printFromChar(char c);
void printFromInt(const char* str);
void printFromFloating(const char* str);

#endif
