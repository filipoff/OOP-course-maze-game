#pragma once
#include <iostream>
using namespace std;

// all entity have position on the map
struct Position
{
	unsigned short x;
	unsigned short y;
	Position();
	Position(unsigned short x, unsigned short y);
	Position& operator()(const unsigned short x, const unsigned y);
	Position& operator=(const Position &other);
	bool operator==(const Position &other);
};