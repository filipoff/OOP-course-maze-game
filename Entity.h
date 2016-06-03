#pragma once
#include "Utils.h"
#include <math.h>


// this is the main class used for the monsters and for the hero
class Entity
{
protected:
	// each Entity has :
	int maxHP; // maximum HealthPoints an entity can have
	int currentHP; // the HealthPoints an entity has in during battles
	unsigned char level; // entity's level
	int exp; // the experience
	int attack; // the attack
	int defense; // the defense
	char displaySymbol; // the symbol that is used to show where the entity is on the map
	Position currentPos; // the current posiotion of the entity on the map
	bool isAlive; // the status of the entity : dead or alive
public:
	Entity(char displaySymbol, int maxHP, int currentHP, unsigned char level, 
		int exp, int attack, int defense); // the ctor that sets the stats

	// a ctor that is used for deserialization
	// its called in the child classes for their deserialization
	Entity(istream &in); 

	// the virtual dtor of the class
	// this class has no dynamic data so its empty
	virtual ~Entity() {}
	
	
	char getDisplaySymbol() const { return displaySymbol;} // returns the symbol of the entity
	// getters
	int getMaxHp() const { return maxHP; }
	int getCurrentHp() const { return currentHP; }
	int getExp() const { return exp; }
	int getLevel() const { return level; }
	bool getIsAlive() const { return isAlive; }
	virtual int getAttack() const { return attack; }
	virtual int getDefense() const { return defense; }
	virtual int getExpToLevelUp() const { return 0; }
	Position getPos() const { return currentPos; }


	virtual void levelUp() {}  // method used in the hero class when hero levels up

	// method that serializes the entity
	// its called in the child classes aswell
	// game engine uses it to save the game
	virtual void serialize(ostream &out);

	// setters
	void setPos(Position pos); 
	void setMaxHP(int maxHp) { this->maxHP = maxHp; }
	void setCurrentHP(int currentHp) { this->currentHP = currentHp; }
	void setExp(int exp) { this->exp = exp; }
	void setIsAlive(bool status) { isAlive = status; }

};