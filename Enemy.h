#pragma once
#include "Entity.h"
#include "Utils.h"
#include <iostream>
using namespace std;

// enemy is a type of entity  with a few extra features
class Enemy : public Entity
{
public:
	enum monsterType // every monster has a type
	{
		Unknown = 0,
		Goblin,
		Troll,
		Orc,
		TYPE_COUNTER
	};

	Enemy(); // default ctor
	Enemy(monsterType type, int monsterLevel); // ctor with parameters monstertype and monsterlevel
	Enemy(istream &in); // ctor used for deserialization of an monster
	virtual ~Enemy() {}; // the dtor, the class has no dynamic data so its empty

	// a function that generates monster's stats according to their type and level
	void generateStats(const int level,const monsterType type); 

	// a static method that returns a monster type depending on its symbol
	static monsterType getEnemyType(char symbol); 

	// a static method that is used in the game engine for creating monsters
	static Enemy* create(monsterType type, int monsterLevel)
	{
		return new Enemy(type, monsterLevel); // returns a pointer to monster
	}

	void setMonsterType(const monsterType type); // function that sets the monstertype
	void serialize(ostream &out); // method that serializes a monsters

protected:

	monsterType type; // the type of a monster

	// a static array of symbols that are found on the map
	// representing the monsters
	static char symbols[TYPE_COUNTER]; 
};