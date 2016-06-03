#include "Item.h"
#include "Armor.h"
#include "Helmet.h"
#include "Sword.h"

void Item :: serialize(ostream &out)
{
		out.write((char*)&type,sizeof(type));
}

Item* Item ::deserialize(istream &in)
{
	Item* res = NULL;
	ItemType type;
	in.read((char*)&type,sizeof(type));
	switch(type)
	{
	case sword:
		res = new Sword(in);
		break;
	case helmet:
		res = new Helmet(in);
		break;
	case armor:
		res = new Armor(in);
		break;
	}
	return res;

}