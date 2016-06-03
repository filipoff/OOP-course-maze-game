#pragma once
#include "Item.h"

class Armor : public Item
{
	int defense; // the armor gives bonus the the defense of the player
public:
	Armor(); // the default ctor
	Armor(int defense); // ctor with defense as parameter
	Armor(istream &in); // ctor that is used for the deserialization of the armor
	Armor(const Armor &other); // copy ctor
	// no need for assignment operator because the class has only one simple member
	virtual ~Armor() {} // no dynamic data, so no need for specific dtor
	virtual Armor* clone() const { return new Armor(*this); } // clone method - returns a new armor
	virtual int getDefense() const { return defense; } // gets the defense of the armor
	virtual int getAttack() const { return 0; } // the armor has no attack so its 0
	virtual void print() const; // print method that is used by the game engine to print the item's info
	virtual void serialize(ostream &out); // the serialize method used by the game engine for saving the item
};