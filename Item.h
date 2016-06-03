#pragma once
#include <iostream>
using namespace std;

/// Item is a abstract class
/// its used by the game engine and the Hero class
class Item
{
public:
	enum ItemType // the types of items that the player can get in the game
	{
		helmet,
		armor,
		sword
	};
private:
	ItemType type; // every item has a type
public:

	Item(ItemType type) { this->type = type; } // ctor with type as parameter used for the child classes
	virtual ~Item() {} // virtual dtor of the class, every child class can overload it if it has dynamic data
	virtual void print() const = 0; // virtual method used by the child classes for printing the item info
	virtual Item* clone() const = 0; // virtual method used by the child classes for cloning
	virtual int getAttack() const = 0; // gets the attack of the item
	virtual int getDefense() const = 0; // gets the defense of the item

	// base serializing method - writes the type of the item in a stream and
	// its used in the child classes

	virtual void serialize(ostream &out); 
	Item* deserialize(istream &in);
	ItemType getItemType() const { return type; }
};