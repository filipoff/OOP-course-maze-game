#pragma once
#include "Item.h"

class Sword : public Item
{
	int attack; // the sword gives bonus the the attack of the player
public:
	Sword(); // the default ctor
	Sword(int attack); // ctor with attack as parameter
	Sword(istream &in); // ctor that is used for the deserialization of the sword
	Sword(const Sword &other); // copy ctor
	// no need for assignment operator because the class has only one simple member
	virtual ~Sword() {} // no dynamic data, so no need for specific dtor
	virtual Sword* clone() const { return new Sword(*this); } // clone method - returns a new swor
	virtual int getDefense() const { return 0; } // the sword has no defense so its 0
	virtual int getAttack() const { return attack; } // gets the attack of the sword
	virtual void print() const; // print method that is used by the game engine to print the item's info
	virtual void serialize(ostream &out); // the serialize method used by the game engine for saving the item
};