#ifndef PRINT_HELPERS_H
# define PRINT_HELPERS_H

# include <exception>

# define OUT_OF_RANGE(X, TYPE) (\
		(X) > std::numeric_limits<TYPE>::max()\
		|| (X) < std::numeric_limits<TYPE>::min())

# define OUT_OF_RANGE_F(X, TYPE) (\
		(X) > std::numeric_limits<TYPE>::max()\
		|| (X) < -std::numeric_limits<TYPE>::max())

typedef enum e_type {
	character,
	integer,
	floating_point,
	double_float,
	pseudo_float,
	pseudo_double,
} str_type;

#define DIGITS "0123456789"

void printChar(char c);
void printInt(int i);
void printFloat(float f);
void printDouble(double d);
void printException(const std::exception& e);

#endif
