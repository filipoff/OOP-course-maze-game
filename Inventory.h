#pragma once
#include "Item.h"
#include "Armor.h"
#include "Helmet.h"
#include "Sword.h"

// Inventory is used by hero 
// its where the items of the hero are stored
class Inventory
{
	Item** bag; // array of pointers to items
	int numberOfSlots; // the maximum number of items an inventory can store
	void copyFrom(const Inventory &other); // help function for the copy ctor
	void clear(); // function that clears the inventory
public:
	Inventory(); // the default ctor
	Inventory(int numberOfSlots); // ctor with parameter number of slots
	Inventory(const Inventory &other); // copy ctor
	Inventory(istream &in); // ctor with istream used for the deserialization of the inventory
	Inventory& operator=(const Inventory &other); // assigment operator
	~Inventory(); // the dtor
	void addItemToBag(Item* item); // a method that adds an item to the inventory
	// getters
	int getAllAttack() const;
	int getAllDefense() const;
	int getNumberOfSlots() const { return numberOfSlots; }
	const Item* getAt(int index) const;


	void setNumberOfSlots(int number) { numberOfSlots = number; } // a method that sets the number of slots
	

	void serialize(ostream &out); // serializes all items in the invetory to a stream
};