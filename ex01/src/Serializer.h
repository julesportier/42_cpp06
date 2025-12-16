#ifndef SERIALIZER_H
# define SERIALIZER_H

# include "Data.h"
# include <stdint.h>

class Serializer {
public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
private:
	Serializer();
	Serializer(const Serializer&);
	~Serializer();
	Serializer& operator=(const Serializer&);
};

#endif
