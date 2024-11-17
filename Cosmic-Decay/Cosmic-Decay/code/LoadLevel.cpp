#include "stdafx.h"
#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];

	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	for (int i = 0; i < m_LM.getLevelSpawningPointsSize().y; ++i)
	{
		delete[] m_ArraySpawningPointsLevel[i];

	}
	delete[] m_ArraySpawningPointsLevel;

	// load spawning points data
	m_ArraySpawningPointsLevel = m_LM.nextLevelSpawningPoints();
	for (int x = 0; x < m_LM.getLevelSpawningPointsSize().x; x++)
	{
		for (int y = 0; y < m_LM.getLevelSpawningPointsSize().y; y++)
		{


			// check to see if its a fuse (type 6)
			int artefact = m_ArraySpawningPointsLevel[y][x];
			if (artefact == 6)
			{
				//create a fuse object , this calls the fuses constructor
				Fuses t_Fuse;
				int locx = (x * 50) + 11;
				int locy = (y * 50) + 11;

				//set the fuse location
				t_Fuse.spawn(Vector2f(locx,locy), GRAVITY, 4);

				//add to the list
				m_FusesList.push_back(t_Fuse);
			}

			if (artefact == 9)
			{
				//create a health object , this calls the health constructor
				HealthPickup t_Health;
				int locx = (x * 50) + 11;
				int locy = (y * 50) + 11;

				//set the health location
				t_Health.spawn(Vector2f(locx, locy), GRAVITY, 4);

				//add to the list
				m_HealthPickupList.push_back(t_Health);
			}

			if (artefact == 8)
			{
				//create a ammo object , this calls the ammo constructor
				AmmoPickup t_Ammo;
				int locx = (x * 50) + 11;
				int locy = (y * 50) + 11;

				//set the ammo location
				t_Ammo.spawn(Vector2f(locx, locy), GRAVITY, 4);

				//add to the list
				m_AmmoPickupList.push_back(t_Ammo);
			}

		}
	}

	// How long is this new time limit
	m_TimeRemaining = m_LM.getTimeLimit();

	// Spawn Enemy and Player
	m_ZombieAlien1.setSprite(1);
	m_ZombieAlien2.setSprite(2);
	m_ZombieAlien3.setSprite(3);
	
	m_Player.setName("Player");
	m_Player.spawn(Vector2f(1500, 700), GRAVITY, 0);
	m_ZombieAlien1.spawn(Vector2f(850, 100), GRAVITY, 1);
	m_ZombieAlien2.spawn(Vector2f(600, 100), GRAVITY, 2);
	m_ZombieAlien3.spawn(Vector2f(400, 100), GRAVITY, 3);
	float speed_Val = m_Player.getSpeed();
	m_ZombieAlien1.setSpeed(speed_Val * 0.5);
	m_ZombieAlien2.setSpeed(speed_Val * 0.4);
	m_ZombieAlien3.setSpeed(speed_Val * 0.3);
	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}