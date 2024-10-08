//Zach Ahearn
//Creating The Enemy Hordes

//#include "ZombieArena.h"
//#include "Zombie.h"

/*
Zombie* createHorde(int numZombies, IntRect arena, int wave)
{
	Zombie* zombies = new Zombie[numZombies];

	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numZombies; i++)
	{

		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;

		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;

		case 2:
			// top
			x = (rand() % maxX) + minX;
			y = minY;
			break;

		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		
		// Bloater, crawler or runner
		srand((int)time(0) * i * 2);

		//When the round is 7, only the zombie type 'boss' will be added to the array
		int type;
		if (wave == 7)
		{
			type = 3;
		}
		else
		{
			type = (rand() % 3);
		}
		// Spawn the new zombie into the array
		zombies[i].spawn(x, y, type, i);

	}
	return zombies;
}

*/