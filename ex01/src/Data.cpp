#include "Data.h"

Data::Data() : m_id(1), m_name("the data") {};

Data::Data(const Data& src) : m_id(src.m_id), m_name(src.m_name) {};

Data::~Data() {};

Data& Data::operator=(const Data& src)
{
	if (this != &src) {
		m_id = src.m_id;
		m_name = src.m_name;
	}
	return (*this);
}

std::string Data::getName() const
{
	return (m_name);
}

int Data::getID() const
{
	return (m_id);
}
