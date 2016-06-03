#pragma once
#include "Entity.h"
#include <iostream>
#include <time.h>
using namespace std;

/// Arena is a class thats used by the Game Engine
/// Its used to make battles between the player and the monsters
/// Its turn based
/// it has no members
class Arena
{
	// Battler is the type of the participants in the battles
	enum Battler 
	{
		Player,
		Monster
	};

	// method that prints text as the player goes into battle
	void printIntro(Battler first); 

	// method that prints the stats of the player and the monster
	void printStats(const Entity hero, const Entity monster);

	// this method chooses who will attack first the player or the monster, randomly
	Battler whoIsFirst();
	
	// this method prints who's turn is to attack next
	void toAttack(Battler who);

	// this method prints the log that is left after every turn of the battle
	// ( who attacked who with how many damage);
	void battleLog(Battler who, int damage);

	// this method is the actual attack. It calculates how many damage do both the player and monster take
	int attack(Entity &attacker, Entity &defender);
public:

	// this is the method that is used by the game Engine,
	// it takes the hero and the monster as parameters
	// the player and the monster take turns until one of the is dead
	void EnterBattle(Entity &hero, Entity &monster);
};