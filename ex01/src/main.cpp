#include "Serializer.h"
#include "Data.h"
#include <iostream>

static void printBold(std::string str)
{
	std::cout << "\e[1m" << str << "\e[0m\n";
}

int main(void)
{
	printBold("serialization of right address");
	Data d = {.name = "my data", .id = 1};
	Data* d_ptr = &d;
	std::cout
		<< "Data d: id == " << d.id
		<< " name == " << d.name
		<< " address == " << d_ptr << '\n';
	uintptr_t serial = Serializer::serialize(d_ptr);
	std::cout << "Data d_ptr: serial == " << serial << '\n';
	d_ptr = Serializer::deserialize(serial);
	std::cout << "Data d_ptr address after deserialization: " << d_ptr << '\n';

	printBold("serialization of NULL");
	d_ptr = NULL;
	serial = Serializer::serialize(d_ptr);
	std::cout << "Data d_ptr(NULL): serial == " << serial << '\n';
	d_ptr = Serializer::deserialize(serial);
	std::cout << "Data d_ptr(NULL) address after deserialization: " << d_ptr << '\n';
	return (0);
}
