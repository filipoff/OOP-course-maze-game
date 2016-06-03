#pragma once
#include "Utils.h"
#include "Hero.h"
#include "Enemy.h"
#include "Level.h"
#include "Arena.h"
#include "Item.h"
#include "Sword.h"
#include "Helmet.h"
#include "Armor.h"
#include <conio.h>
#include <fstream>
#include <time.h>


// the game engine is the class that makes all the actions

enum Direction // an enum that is used for the input directions of the player
{
	UP = 'w',
	DOWN = 's',
	LEFT = 'a',
	RIGHT = 'd'
};

class GameEngine
{

	Level map; // the game has a map
	Hero* one; // a hero that the player controls
	Enemy** monsters; // array of pointers to monsters - all monster info is stored here
	Arena Battlefield; // this is the battlefield that when the player encounters a monster, battl happens
	char input; // the input char that game recieves from the player in order to play the game
	int currentLevel; // the currently loaded map
	int monsterCounter; // the monster's total count on a given map


	// this method checks if the player's next move is
	// free to step, has a monster that will go into battle with,
	// if its the trigger for loading the next map
	void tryToMove(const Direction dir);

	// this method loads the next map
	void loadNext();

	// this method prints all the info in the console
	void print();

	// this method spawns enemies from the spawn points placed in the map file
	// the monsters stats depend on the current map the the player is at
	void spawnEnemies();

	// a method that clears the monster array
	void clearMonsters();

	// this method clears all data used by the class, its used in the dtor
	void clear();

	// this method shows a screen that all items that the player has are visible
	void showItems();

	// this method genetarates an item that the player gets if he wins a battler
	Item* generateItem(Hero &one);

	// this function finds with monster from the monster array is located at a given position
	Enemy* findMonster(Position pos);

	// this method is used when the player wants to save the game at a given point to a file
	void serialize(const char* fileName);

	// this method is used to restore a game that the player has played before
	void deserialize(const char* fileName);

	// method that introduces the player to the game
	void printIntro();
public:
	GameEngine(); // the default ctor
	~GameEngine(); // the dtor

	// this is the method that controls the whole structure of the gameplay
	void run();
};