#include "GameEngine.h"

GameEngine :: GameEngine() // the default ctor
{
	currentLevel = 0;
	monsterCounter = 0;
	monsters = NULL;
	one = new Hero(); // creates hero
	loadNext(); // loads map
}

GameEngine :: ~GameEngine() // the dtor
{
	clear(); 
}

void GameEngine :: loadNext() // the method that loads the next map
{
	currentLevel++;
	// first we generate a file name depending on the current level
	char* filename;
	char bfr[2];
	char* prefix = "Level";
	char* middle = itoa(currentLevel,bfr,10);
	char* extension = ".txt";
	int len = strlen(prefix)+strlen(extension)+strlen(middle);
	filename = new char [len+1];
	strcpy(filename,prefix);
	strcat(filename,middle);
	strcat(filename,extension);

	// then we try to load the map from the given name
	try
	{
		map.loadFrom(filename); 
	}
	catch (int param)
	{
		// if we cant, we show a error message and dont proceed to next map, nor lose all data
		currentLevel--;
		system("cls");
		cerr << "Error, cannot load next map!" << endl;
		system("pause");
		throw param;
	}
	spawnEnemies(); // we spawn enemies from the map info
	one->setPos(map.getEntry()); // set the players position according to the entry symbol
	map.setAtPos(one->getDisplaySymbol(), map.getEntry()); // we set the players symbol at that position
}
void GameEngine :: tryToMove(const Direction dir)
{
	// a new postion
	Position next=one->getPos();
	// depending on the input, next is calculateds
	switch(dir)
	{
	case UP:
		next.y--;
		break;
	case DOWN:
		next.y++;
		break;
	case LEFT: 
		next.x--;
		break;
	case RIGHT:
		next.x++;
		break;
	}

	// if its empty space its save to move there
	if (map.getAtPos(next) == ' ')
	{
		map.setAtPos(' ',one->getPos());
		one->setPos(next);
		map.setAtPos(one->getDisplaySymbol(),one->getPos());
	}

	// if its the exit of the map, we check if all monsters are killed
	// if not we display a message
	if (map.isExit(next))
	{
		bool flag = false;
		for (int i=0; i<monsterCounter; i++)
		{
			if (monsters[i]->getIsAlive())
			{
				system("cls");
				cout << "You have to kill all monsters before entering next level!" << endl;
				system("pause");
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			try
			{
				loadNext();
			}
			catch (int param) {}
		}
	}

	// if the next position is a monster symbol
	// we go into battle
	Enemy :: monsterType type = Enemy :: getEnemyType(map.getAtPos(next));
	if ( type != Enemy :: Unknown)
	{

		Enemy* two = findMonster(next); // finds exactly which monster is at the given position
		try
		{
			Battlefield.EnterBattle(*one,*two);
			map.setAtPos(' ',two->getPos());
			// if the player is winner he recieves a new item
			one->getEquipment()->addItemToBag((generateItem(*one))); 
			system("pause");
		}	
		catch (int param) {} // if hes not alive the game ends
	}
}

void GameEngine :: clearMonsters() // the function that clears the monster array
{
	if (currentLevel == 1)
		return;
	for (int i=0; i<monsterCounter; i++)
	{
		map.setAtPos(' ',monsters[i]->getPos()); // it places empty spaces where the monsters were
		delete monsters[i];
	}	
	delete monsters;
	monsters = NULL;
}
void GameEngine :: clear()
{
	clearMonsters();
	// + clears the hero data and sets the players position to empty space
	map.setAtPos(' ',one->getPos());
	delete one;
	one = NULL;
}
void GameEngine :: print()
{
	// print the map
	map.print();
	// print extra info about the players stats
	cout << endl
		<< "Map: " << currentLevel << endl;
	cout << "Health: " << one->getCurrentHp()  << '/' << one->getMaxHp() << '\t'
		<< "Attack: " << one->getAttack() << '\t' << "Defense: " << one->getDefense() << endl;
	cout << "Level: " << one->getLevel() << '\t' 
		<< "Experience: " << one->getExp() << '/' << one->getExpToLevelUp() << '\t' << endl;	 
}
void GameEngine :: spawnEnemies()
{
	// if there we monsters befpre , in case we load a next map, we clear the array
	clearMonsters();
	Position temp;
	monsterCounter = 0;

	// we count how many monsters are there on the map 
	// depending on the symbol on the map
	for (int i=0; i<map.getHeight(); i++)
	{
		for (int j=0; j<map.getWidth(); j++)
		{
			temp(j,i);
			if (Enemy :: getEnemyType(map.getAtPos(temp)) != Enemy :: Unknown)
			{
				monsterCounter++;
			}
		}
	}

	// we create a new array of monsters with known count
	monsters = new Enemy* [monsterCounter];
	monsterCounter = 0;
	for (int i=0; i<map.getHeight(); i++)
	{
		for (int j=0; j<map.getWidth(); j++)
		{
			temp(j,i);
			Enemy :: monsterType type = Enemy :: getEnemyType(map.getAtPos(temp));
			if ( type != Enemy :: Unknown)
			{
				monsters[monsterCounter] = Enemy :: create(type,currentLevel); // we create monster
				monsters[monsterCounter]->setPos(temp); // set its position
				map.setAtPos(monsters[monsterCounter]->getDisplaySymbol(),temp); // set its symbol
				monsterCounter++;	
			}
		}
	}

}
Enemy* GameEngine :: findMonster(Position pos)
{
	// search exactly which monster is at given position and return pointer to it
	for (int i=0; i<monsterCounter; i++)
	{
		if (monsters[i]->getPos() == pos)
		{
			return monsters[i];
		}
	}
	return NULL;
}
Item* GameEngine :: generateItem(Hero &one)
{
	// we generate new item after battle
	// stronger than the one we already have
	Item* item;
	srand(time(NULL));
	int result = rand()% 3;
	int attack = one.getEquipment()->getAllAttack();
	int defense = one.getEquipment()->getAllDefense();
	attack += rand() % 6+1;
	defense += (int)(rand() % 6)/2+1;

	switch(result)
	{
	case 0:
		item = new Sword(attack);
		cout << "You gained a new sword with bonus to attack +" << attack << endl;
		break;
	case 1:
		item = new Helmet(defense);
		cout << "You gained a new helmet with bonus to defense +" << defense << endl;
		break;
	case 2:
		item = new Armor(defense);
		cout << "You gained a new armor with bonus to defense +" << defense << endl;
		break;
	}
	return item;
}

void GameEngine :: showItems()
{
	// display what items the hero has equipped at a given moment
	int cnt = one->getEquipment()->getNumberOfSlots();
	bool flag = false;
	system("cls");
	cout << "Current Items: " << endl;
	for (int i=0; i<cnt; i++)
	{
		if (one->getEquipment()->getAt(i))
		{
			flag = true;
			one->getEquipment()->getAt(i)->print();
		}
	}
	if (!flag)
	{
		cout << "None" << endl;
	}
	system("pause");
}
void GameEngine :: run()
{
	// the main loop of the game
	// at the very begining we set the players symbol and position on the map
	one->setPos(map.getEntry());
	map.setAtPos(one->getDisplaySymbol(),one->getPos());

	// this loop continues until the player is dead
	while(one->getIsAlive())
	{
		print();
		input = tolower(getch());
		try
		{
			switch(input)
			{
			case 'a':
				tryToMove(LEFT);
				break;
			case 's':
				tryToMove(DOWN);
				break;
			case 'd':
				tryToMove(RIGHT);
				break;
			case 'w':
				tryToMove(UP);
				break;
			case 'i':
				showItems();
				break;
			case 'p':
				serialize("save.dat");
				break;
			case 'o':
				deserialize("save.dat");
				break;
			}
		}
		catch (int param) {}
		system("cls");
	}

}

void GameEngine :: serialize(const char* fileName)
{
	ofstream out(fileName,ios :: binary);
	if (!out)
	{
		system("cls");
		cerr << "Error while saving the game to save.dat !" << endl;
		system("pause");
		throw 5;
	}
	out.write((char*)&currentLevel,sizeof(currentLevel));
	one->serialize(out);
	int aliveMonsters = 0;
	for (int i=0; i<monsterCounter; i++)
	{
		if (monsters[i]->getIsAlive())
			aliveMonsters++;
	}
	out.write((char*)&aliveMonsters,sizeof(aliveMonsters));
	for (int i=0; i<monsterCounter; i++)
	{
		if (monsters[i]->getIsAlive())
			monsters[i]->serialize(out);
	}
	out.close();
	system("cls");
	cout << "Game saved in sav.dat" << endl;
	system("pause");
}

void GameEngine :: deserialize(const char* fileName)
{
	ifstream in(fileName,ios :: binary);
	if (!in)
	{
		system("cls");
		cerr << "Error, could not open sav.dat !" << endl;
		system("pause");
		throw 5;
	}
	in.read((char*)&currentLevel,sizeof(currentLevel));
	currentLevel--;
	loadNext();
	clear();
	one = new Hero(in);
	map.setAtPos(one->getDisplaySymbol(),one->getPos());
	in.read((char*)&monsterCounter,sizeof(monsterCounter));
	monsters = new Enemy* [monsterCounter];
	for (int i=0; i<monsterCounter; i++)
	{
		monsters[i] = new Enemy(in);
		map.setAtPos(monsters[i]->getDisplaySymbol(),monsters[i]->getPos());
	}
	in.close();
	system("cls");
	cout << "Game loaded from sav.dat" << endl;
	system("pause");

}
