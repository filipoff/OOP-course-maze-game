#include "Utils.h"

Position :: Position()
{
	x = 0;
	y = 0;
}
Position :: Position(unsigned short x, unsigned short y)
{
	this->x = x;
	this->y = y;
}
Position& Position :: operator()(const unsigned short x, const unsigned y)
{
	this->x = x;
	this->y = y;
	return *this;
}

Position& Position :: operator=(const Position &other)
{
	if (this == &other)
		return *this;
	this->x = other.x;
	this->y = other.y;
	return *this;
}

bool Position :: operator==(const Position &other)
{
	if ( x == other.x && y == other.y)
		return true;
	else return false;
}