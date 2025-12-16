#include "Serializer.h"
#include "Data.h"
#include <iostream>

int main(void)
{
	Data *d;
	try {
		d = new Data;
	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << '\n';
		return (-1);
	}
	std::cout
		<< "Data d: id == " << d->getID()
		<< " name == " << d->getName()
		<< " address == " << d << '\n';
	uintptr_t ser = Serializer::serialize(d);
	std::cout << "Data d: ser == " << ser << '\n';
	d = Serializer::deserialize(ser);
	std::cout << "Data d address after deserialization: " << d << '\n';
	delete d;

	d = NULL;
	ser = Serializer::serialize(d);
	std::cout << "Data d(NULL): ser == " << ser << '\n';
	d = Serializer::deserialize(ser);
	std::cout << "Data d(NULL) address after deserialization: " << d << '\n';
	return (0);
}
