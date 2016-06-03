#include "Sword.h"

Sword :: Sword() : Item(sword)
{
	attack = 0;
}

Sword :: Sword(const Sword &other) : Item(sword)
{
	this->attack = other.attack;
}

Sword :: Sword(int attack) : Item(sword)
{
	this->attack = attack;
}

Sword :: Sword(istream &in) : Item(sword)  // method used for the deserialization of this item
{
	in.read((char*)&attack,sizeof(attack));  // reads the attack of the sword from a stream
}

 void Sword :: print() const
 {
	 cout << "Sword: Bonus to attack +" << attack << endl;
 }

 void Sword :: serialize(ostream &out)
{
	Item :: serialize(out); // calling the method from the base abstract class 
	out.write((char*)&attack,sizeof(attack)); // then writing the attack of the sword in a stream
}