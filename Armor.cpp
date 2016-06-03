#include "Armor.h"


Armor :: Armor() : Item(armor)
{
	defense = 0;
}
Armor :: Armor(const Armor &other) : Item(armor)
{
	this->defense = other.defense;
}
Armor :: Armor(int defense) : Item(armor)
{
	this->defense = defense;
}

Armor :: Armor(istream &in) : Item(armor) // method used for the deserialization of this item
{ 
	in.read((char*)&defense,sizeof(defense)); // reads the defense of the armor from a stream
}

 void Armor :: print() const
 {
	 cout << "Armor: Bonus to defense +" << defense << endl;
 }

void Armor :: serialize(ostream &out)
{
	Item :: serialize(out); // calling the method from the base abstract class 
	out.write((char*)&defense,sizeof(defense)); // then writing the defense of the armor in a stream
}