#include "Entity.h"

Entity :: Entity(char displaySymbol, int maxHP, int currentHP, unsigned char level, 
				 int exp, int attack, int defense) : currentPos(0,0) , isAlive(true)
{
	this->displaySymbol = displaySymbol;
	this->maxHP = maxHP;
	this->currentHP = currentHP;
	this->level = level;
	this->exp = exp;
	this->attack = attack;
	this->defense = defense;
}

Entity :: Entity(istream &in) // this ctor is called when deserializing an entity
{
	in.read((char*)&displaySymbol,sizeof(displaySymbol));
	in.read((char*)&maxHP,sizeof(maxHP));
	in.read((char*)&currentHP,sizeof(currentHP));
	in.read((char*)&level,sizeof(level));
	in.read((char*)&exp,sizeof(exp));
	in.read((char*)&attack,sizeof(attack));
	in.read((char*)&defense,sizeof(defense));
	in.read((char*)&currentPos,sizeof(currentPos));
	in.read((char*)&isAlive,sizeof(isAlive));
}

void Entity :: setPos(Position pos)
{
	currentPos = pos;
}
void Entity :: serialize(ostream &out) // this method writes the entity's members to stream
{
	out.write((char*)&displaySymbol,sizeof(displaySymbol));
	out.write((char*)&maxHP,sizeof(maxHP));
	out.write((char*)&currentHP,sizeof(currentHP));
	out.write((char*)&level,sizeof(level));
	out.write((char*)&exp,sizeof(exp));
	out.write((char*)&attack,sizeof(attack));
	out.write((char*)&defense,sizeof(defense));
	out.write((char*)&currentPos,sizeof(currentPos));
	out.write((char*)&isAlive,sizeof(isAlive));
}