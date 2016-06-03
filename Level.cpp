#include "Level.h"

// this method allocates an empty map using height and width
char** Level :: allocate(const unsigned short h, const unsigned short w)
{
	height = h;
	width = w;
	char** temp = new char* [height];
	for (int i=0; i<height; i++)
	{
		temp[i] = new char [width+1];
	}
	return temp;
}
Level :: Level() // the default ctor
{
	level = NULL;
	height = 0;
	width = 0;
	entry(0,0);
}

void Level :: loadFrom(const char* filename) // a method that loads a map given a file name
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		throw 2; // throws exception if the file couldnt be opened, game engine takes care of the exception
	loadFile(file);
	file.close();
}
Level :: ~Level() // the dtor
{
	free();
}
void Level :: print() const // the method that prints the map in the console
{
	for(int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
			cout << level[i][j];
		cout << endl;
	}
}
void Level :: loadFile(istream &in) // the method that reads the data from the map file
{
	free();
	char *buffer;
	int h,w;
	in >> h >> w;
	in.ignore();
	height = h;
	width = w;
	level = new char* [height];
	for (int i=0; i<height; i++)
	{
		level[i] = new char [width+1];
	}
	for (int i=0; i<height; i++)
	{
		in.getline(level[i],width+1);
		for (int j=0; j < width; j++)
		{
			if ( level[i][j] == entrySymbol) // when we find the entry symbol of the hero
			{
				entry(j,i);
				 level[i][j] = ' '; // we replace it with a empty space 
			}
		}
	}
}


void Level :: setAtPos(const char object, const Position pos)
{
	level[pos.y][pos.x] = object;
}


bool Level :: isExit(const Position pos) const
{
	if ( level[pos.y][pos.x] == exitSymbol )
		return true;
	else return false;
}

void Level :: free()
{

	for (int i=0; i<height; i++)
		delete [] level[i];
	delete level;
	level = NULL;
	width = 0;
	height = 0;
	entry(0,0);

}
