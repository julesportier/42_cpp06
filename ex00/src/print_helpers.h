#ifndef PRINT_HELPERS_H
# define PRINT_HELPERS_H

# include <exception>

void printChar(char c);
void printInt(int i);
void printFloat(float f, bool fixed);
void printDouble(double d, bool fixed);
void printException(const std::exception& e);

#endif
