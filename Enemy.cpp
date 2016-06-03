#include "Enemy.h"

Enemy :: Enemy() : // the default ctor calls the entity's ctor
		Entity( 'M', // displaySymbol - dafault symbol, not used 
			0, // currentHP
			0, // maxHP
			0, // level
			0, // exp
			0, // attack
			0) // defense
{
	type = Unknown; // default type
}

Enemy :: Enemy(istream &in) : Entity(in) // method that is used for deserialization of an monster
										 // first calls the entities deserialization
{
	in.read((char*)&type,sizeof(type)); // reads the type of a monsters
}

void Enemy :: setMonsterType(const monsterType type)
{
	this->type = type;
}

void Enemy :: generateStats(const int level,const monsterType type) // generates the stats of monsters
{
	int startMaxHP = 15;
	int startAttack = 10;
	int startDefense = 8;
	int maxLevelMaxHP = 1000;
	int maxLevelAttack = 500;
	int maxLevelDefense = 300;

	maxHP = (int)floor((.8 + level / 50) * level * ((maxLevelMaxHP - startMaxHP) / 275.222) + startMaxHP + .1);
	currentHP = maxHP;
	attack = (int)floor((.8 + level / 50) * level * ((maxLevelAttack - startAttack) / 275.222) + startAttack + .1);
	defense = (int)floor((.8 + level / 50) * level * ((maxLevelDefense - startDefense) / 275.222) + startDefense + .1);
	exp = (int)floor(exp*1.2 + 5); // ???

	switch(type) // bonuses for different monster types
	{
	case Goblin:
		attack += (int)floor(15*attack/100);
		break;
	case Troll:
		defense += (int)floor(15*defense/100);
		break;
	case Orc:
		maxHP += (int)floor(15*maxHP/100);
		currentHP = maxHP;
		break;
	}

}

Enemy :: Enemy(const monsterType type, const int level) : // a ctor that takes type and level for parameters
			Entity( symbols[type], // displaySymbol
			0, // currentHP
			0, // maxHP
			0, // level 
			0, // exp
			0, // attack
			0) // defense
			, type(type)
{
	this->level = level;
	generateStats(level,type);
}

// the static array of monster symbols found on the map
// its static because they are common for all monsters
char Enemy :: symbols[TYPE_COUNTER] = {'\0','G','T','O'}; 

Enemy :: monsterType Enemy :: getEnemyType(char symbol)
{
	for (int i=1; i<TYPE_COUNTER; i++)
	{

		if (symbol == symbols[i])
			return (monsterType)i;
	}
	return Unknown;
}

void Enemy :: serialize(ostream &out) // serialization method
{
	Entity :: serialize(out); // first it calls the serialization method of the entity class
	out.write((char*)&type,sizeof(type));
}