#include "Helmet.h"

Helmet :: Helmet() : Item(helmet)
{
	defense = 0;
}

Helmet :: Helmet(const Helmet &other) : Item(helmet)
{
	this->defense = other.defense;
}

Helmet :: Helmet(int defense) : Item(helmet)
{
	this->defense = defense;
}

Helmet :: Helmet(istream &in) : Item(helmet) // method used for the deserialization of this item
{
	in.read((char*)&defense,sizeof(defense)); // reads the defense of the armor from a stream
}
 void Helmet :: print() const
 {
	 cout << "Helmet: Bonus to defense +" << defense << endl;
 }

 void Helmet :: serialize(ostream &out)
{
	Item :: serialize(out); // calling the method from the base abstract class
	out.write((char*)&defense,sizeof(defense)); // then writing the defense of the armor in a stream
}

