#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
using namespace std;

class Level
{
	unsigned short height; // height of the map
	unsigned short width; // width of the map

	// the symbol that shows where should the hero be placed when the map is loaded
	static const char entrySymbol = '*'; 

	// the symbol that shows where the here should go to load the next map
	static const char exitSymbol = '%';

	// the position of the entry symbol
	Position entry;

	// level is a two-dimensional array of chars
	char** level;

	// a function that allocates a map by height and width parameters
	char** allocate(const unsigned short h, const unsigned short w);

	// a function that clears the memory taken by the allocated map 
	void free();

	// a fuction that is used in the loadFrom method for loading a map from text file
	// by reading the file line be line, allocating memory for the map and copying
	// the text from the file into the map array
	void loadFile(istream &in);
public:
	// the constructor of the class
	Level();

	// the destructor of the class
	~Level();

	// print is a method that prints the map on the screen
	void print() const;

	// a method that loads a map by its file name
	void loadFrom(const char* filename);
	
	// a method that sets a symbol at a  given position on the map
	void setAtPos(const char object, const Position pos);
	
	// a method that gets a symbol at a given position on the map
	char getAtPos(const Position pos) const { return level[pos.y][pos.x]; }

	// a method that checks if the exit symbol is placed at the given position
	bool isExit(const Position pos) const;

	// a method that gets the position of the entry symbol
	Position getEntry() const { return entry;} 

	unsigned short getHeight() const { return height; }
	unsigned short getWidth() const { return width; }

};