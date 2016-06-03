#pragma once
#include "Item.h"

class Helmet : public Item
{
	int defense; // the helmet gives bonus the the defense of the player
public:
	Helmet(); // the default ctor
	Helmet(int defense); // ctor with defense as parameter
	Helmet(istream &in); // ctor that is used for the deserialization of the helmet
	Helmet(const Helmet &other); // copy ctor
	// no need for assignment operator because the class has only one simple member
	virtual ~Helmet() {} // no dynamic data, so no need for specific dtor
	virtual Helmet* clone() const { return new Helmet(*this); } // clone method - returns a new helmet
	virtual int getDefense() const { return defense; }  // gets the defense of the helmet
	virtual int getAttack() const { return 0; } // the helmet has no attack so its 0
	virtual void print() const; // print method that is used by the game engine to print the item's info
	virtual void serialize(ostream &out); // the serialize method used by the game engine for saving the item
};