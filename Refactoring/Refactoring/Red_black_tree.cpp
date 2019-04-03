#include "Red_black_tree.h"


bool Elem::operator<(Elem other)
{
	return this->id < other.id;
}

bool Elem::operator<=(Elem other)
{
	return this->id <= other.id;
}

bool Elem::operator>(Elem other)
{
	return this->id > other.id;
}

bool Elem::operator>=(Elem other)
{
	return this->id >= other.id;
}

bool Elem::operator==(Elem other)
{
	return this->id == other.id;
}
