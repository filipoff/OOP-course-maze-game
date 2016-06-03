#include "Arena.h"

void Arena :: printIntro(Battler first)
{
	system("cls");
	cout << "Entering Battle..." << endl;
	system("pause");
	system("cls");
	if (first == Player)
		cout << "You ";
	else cout << "The monster ";
	cout << "will attack first" << endl;
	system("pause");
	system("cls");
}

void Arena :: printStats(const Entity hero, const Entity monster)
{
	cout << "Your stats: " << endl;
	cout << "Health : " << hero.getCurrentHp() << '/' << hero.getMaxHp() << endl;
	cout << "Attack : " << hero.getAttack() << endl;
	cout << "Defense : " << hero.getDefense() << endl;
	cout << endl;
	cout << "Monster's stats: " << endl;
	cout << "Health : " << monster.getCurrentHp() << '/' << monster.getMaxHp() << endl;
	cout << "Attack : " << monster.getAttack() << endl;
	cout << "Defense : " << monster.getDefense() << endl;
	cout << endl;

}

Arena :: Battler Arena :: whoIsFirst()
{
	srand(time(NULL));
	int res = rand()% 2; // chooses the first attacker at random
	return (Battler)res;
}

int Arena :: attack(Entity &attacker, Entity &defender)
{
	int damageTaken = attacker.getAttack() - defender.getDefense();
	defender.setCurrentHP(defender.getCurrentHp() - damageTaken);
	return damageTaken < 0 ? 0 : damageTaken;
	// TODO : random element to attack
	// needs better formula
}

void Arena :: toAttack(Battler who) // announces who's turn is it
{
	if ( who == Player)
		cout << "Your turn to attack the monster." << endl;
	else cout << "Monster's turn to attack you." << endl;
	cout << endl;
}

void Arena :: battleLog(Battler who, int damage) // announces the damage taken by the player and monster
{
	if (who == Player)
	{
		cout << "You inflicted " << damage << " to the Monster" << endl; 
	}
	else
	{
		cout << "The Monster inflicted " << damage << " to You" << endl; 
	}
	cout << endl;
}


void Arena :: EnterBattle(Entity &hero, Entity &monster)
{
	Arena :: Battler first; 
	first = whoIsFirst(); // decides who will attack first
	printIntro(first); // prints the intro the the battle
	int damage = 0;

	// loop until either the player's HP or monster's HP hits 0
	while (hero.getCurrentHp() > 0 && monster.getCurrentHp() > 0) 
	{
		printStats(hero,monster);
		if( first == Player ) 
		{
			damage = attack(hero, monster);
			battleLog(first,damage);
			first = Monster;
			toAttack(first);
		}
		else 
		{
			damage = attack(monster, hero);
			battleLog(first,damage);
			first = Player;
			toAttack(first);
		}

		// announces that the game is over and the game engine stops the game
		if (hero.getCurrentHp() <= 0) 
		{
			system("cls");
			cout << "You are dead!" << endl;
			cout << "GAME OVER" << endl;
			system("pause");
			hero.setIsAlive(false);
			throw 2;
		}
		system("pause");
		system("cls");
	}

	// announces that the player has won the battle
	cout << "You won the battle!" << endl;
	system("pause");

	// the player recieves experience from the monster
	// and if the player has enough XP, he levels up
	hero.setExp(hero.getExp() + monster.getExp());
	if (hero.getExp() >= hero.getExpToLevelUp()) //TODO exptolevelup
	{
		hero.levelUp();
	}
	// after every battle the player regains hes HP points back
	hero.setCurrentHP(hero.getMaxHp());
	// sets the battled monster as dead 
	monster.setIsAlive(false);
}
