#include "Base.h"
#include <exception>
#include <iostream>

static void printException(const std::exception& e)
{
	std::cout << "Error: " << e.what() << '\n';
}

static void printBold(std::string str)
{
	std::cout << "\e[1m" << str << "\e[0m\n";
}

int main(void)
{
	Base* r;

	printBold("identify *");
	for (int i = 0; i < 10; ++i) {
		try {
			r = Base::generate();
		} catch (const std::exception& e) {
			printException(e);
			return (-1);
		}
		Base::identify(r);
		delete r;
	}

	printBold("identify &");
	for (int i = 0; i < 10; ++i) {
		try {
			r = Base::generate();
		} catch (const std::exception& e) {
			printException(e);
			return (-1);
		}
		Base::identify(*r);
		delete r;
	}

	printBold("identify NULL");
	r = NULL;
	Base::identify(r);
	Base::identify(*r);
	return (0);
}
