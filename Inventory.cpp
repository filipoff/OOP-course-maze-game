#include "Inventory.h"
const int maxNumberOfItems = 3;

Inventory :: Inventory() // default ctor
{
	bag = NULL;
	numberOfSlots = 0;
}

void Inventory :: copyFrom(const Inventory &other) // help function for the cpy ctor
{
	this->numberOfSlots = other.numberOfSlots;
	bag = new Item* [numberOfSlots];

	for (int i=0; i<numberOfSlots; i++)
	{
		if (other.bag[i])
			bag[i] = other.bag[i]->clone();
		else 
			bag[i] = other.bag[i] = NULL;
	}
}

Inventory :: Inventory(int numberOfSlots) // the ctor that takes number of slots as parameter
{
	this->numberOfSlots = numberOfSlots;
	bag = new Item* [numberOfSlots];
	for (int i=0; i<numberOfSlots; i++)
		bag[i] = NULL;
}

Inventory :: Inventory(const Inventory &other)  // cpy ctor
{
	copyFrom(other);
}

Inventory :: Inventory(istream &in) // ctor used for deserialization of the inventory
{
	numberOfSlots = maxNumberOfItems;
	bag = new Item* [numberOfSlots];
	for (int i=0; i<numberOfSlots; i++)
	{
		bag[i] = NULL;
	}
	int usedSlots = 0;
	in.read((char*)&usedSlots,sizeof(usedSlots));
	for (int i=0; i<usedSlots; i++)
	{
		bag[i] = bag[i]->deserialize(in); // calls deserialization method of all items
	}
}

Inventory& Inventory :: operator=(const Inventory &other) // assignment operator
{
	if (&other == this)
	{
		return *this;
	}
	clear();
	copyFrom(other);
	return *this;
}

Inventory :: ~Inventory() // the dtor
{
	clear();
}
void Inventory :: addItemToBag(Item* item) // method that adds items to the inventory
{
	int i;
	for (i=0; i<numberOfSlots; i++) 
	{
		if (!bag[i])
		{
			bag[i] = item; //adds an item to a free slot
			break;
		}
		if (bag[i]->getItemType() == item->getItemType()) // or if an item of this type already exists
			// we overwrite it
		{
			delete bag[i];
			bag[i] = item;
			break;
		}
	}
	if ( i >= numberOfSlots) // if the item's type that we try to add is non of the ones we can put in
		// the inventory we delete it
	{
		delete item;
	}
}

int Inventory :: getAllAttack() const
{
	int attack = 0;
	for (int i=0; i<numberOfSlots; i++)
	{
		if (!bag[i])
			continue;
		attack += bag[i]->getAttack();
	}
	return attack; // gets the sum of attack of all items
}

int Inventory :: getAllDefense() const
{
	int defense = 0;
	for (int i=0; i<numberOfSlots; i++)
	{
		if (!bag[i])
			continue;
		defense += bag[i]->getDefense();
	}
	return defense; // gets the sum of defense of all items
}

const Item* Inventory :: getAt(int index) const
{
	return bag[index]; // returns an item at a given position in the array of pointers to items
}
void Inventory :: clear() // function for clearing the inventory
{
	for (int i=0; i<numberOfSlots; i++)
	{
		delete bag[i];
	}
	delete bag;
	bag = NULL;
}

void Inventory :: serialize(ostream &out) // the method that serializes the inventory
{
	// first we count the slots that actually have item in them
	int usedSlots = 0;
	for (int i=0; i<numberOfSlots; i++)
	{
		if (bag[i])
			usedSlots++;
	}
	// we write that counter
	out.write((char*)&usedSlots,sizeof(usedSlots));
	for (int i=0; i<numberOfSlots; i++)
	{
		if(bag[i]) // we call the serialize method of all items, checking if the slot is empty
			bag[i]->serialize(out);
	}
}