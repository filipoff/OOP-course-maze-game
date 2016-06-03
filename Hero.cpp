#include "Hero.h"


const int maxNumberOfItems = 3; // maximum number of items that a hero can have

Hero :: Hero() : // the default ctor calls the entity's ctor
	Entity( '@', // displaySymbol
	10, // currentHP
	10, // maxHP
	1, // level
	0, // exp
	12, // attack
	15) // defense

{
	equipment = new Inventory(maxNumberOfItems); // creates the inventory
	expToLevelUp = 20;
}

Hero :: Hero(istream &in) :
	Entity(in) // ctor used for deserialization of the hero, calls the deserialization method of entity first
{
	in.read((char*)&expToLevelUp,sizeof(expToLevelUp));
	equipment = new Inventory(in);
}

Hero :: ~Hero()
{
	delete equipment;
}
void Hero :: levelUp() // what happens when the hero levels up
{
	int startMaxHP = 10;
	int startAttack = 5;
	int startDefense = 5;
	int maxLevelMaxHP = 1500;
	int maxLevelAttack = 1000;
	int maxLevelDefense = 800;
	level++;
	maxHP = (int)floor((.8 + level / 50) * level * ((maxLevelMaxHP - startMaxHP) / 275.222) + startMaxHP + .1);
	currentHP = maxHP;
	attack = (int)floor((.8 + level / 50) * level * ((maxLevelAttack - startAttack) / 275.222) + startAttack + .1);
	defense = (int)floor((.8 + level / 50) * level * ((maxLevelDefense - startDefense) / 275.222) + startDefense + .1);
	expToLevelUp =(int) exp*(1.2 * level);

}

int Hero :: getAttack() const
{
	return attack + equipment->getAllAttack();
}
int Hero :: getDefense() const
{
	return defense + equipment->getAllDefense();
}
void Hero :: serialize(ostream &out)
{
	Entity :: serialize(out);
	out.write((char*)&expToLevelUp,sizeof(expToLevelUp)); // writes the members to a stream
	equipment->serialize(out); // and calls the serialization method of the equipment to save all the items

}
