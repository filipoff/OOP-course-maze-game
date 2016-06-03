#pragma once
#include "Utils.h"
#include "Entity.h"
#include "Inventory.h"

// hero is a type of entity

class Hero : public Entity
{
	int  expToLevelUp; // experience needed to be reached for the new level of the hero
	Inventory* equipment; // an inventory used for storing the hero's items
public:
	Hero(); // the default ctor
	Hero(istream &in); // the ctor used for deserializing the hero
	virtual ~Hero(); // the dtor
	virtual void levelUp(); // needs to be written

	//getters
	int  getExpToLevelUp() const { return expToLevelUp; }
	Inventory* getEquipment() { return equipment; } // gives access to hero's equipment
	virtual int getAttack() const;
	virtual int getDefense() const; 

	// method that serializes the hero, also calls the serialize method
	// of entity
	virtual void serialize(ostream &out); 
};