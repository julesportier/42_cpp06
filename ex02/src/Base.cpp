#include "Base.h"
#include "A.h"
#include "B.h"
#include "C.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base::~Base() {};

static void printType(char c)
{
	std::cout << c << '\n';
}

static unsigned int randui()
{
	static int next = (std::time(NULL));
	next = next * 1103515245 + 12345;
	return((unsigned)(next/65536) % 32768);
}

Base* Base::generate()
{
    switch (randui() % 3) {
		case 0:
			return (new A);
		case 1:
			return (new B);
		case 2:
			return (new C);
		// Only to silent warning as the default path will never be reached.
		default:
			return (NULL);
	}
}

void Base::identify(Base* p)
{
	A* ptrA = dynamic_cast<A*>(p);
	if (ptrA) {
		printType('A');
		return ;
	}

	B* ptrB = dynamic_cast<B*>(p);
	if (ptrB) {
		printType('B');
		return ;
	}

	C* ptrC = dynamic_cast<C*>(p);
	if (ptrC) {
		printType('C');
		return ;
	}

	std::cout << "Unidentified type\n";
}


void Base::identify(Base& p)
{
	try {
		(void)dynamic_cast<A&>(p);
		printType('A');
		return ;
	} catch (const std::exception& e) {}

	try {
		(void)dynamic_cast<B&>(p);
		printType('B');
		return ;
	} catch (const std::exception& e) {}

	try {
		(void)dynamic_cast<C&>(p);
		printType('C');
		return ;
	} catch (const std::exception& e) {}

	std::cout << "Unidentified type\n";
}
