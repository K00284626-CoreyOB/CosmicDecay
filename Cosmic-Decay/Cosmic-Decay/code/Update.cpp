//Matthew O'Rourke Bourke

#include "stdafx.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

int score = 0;

void Engine::update(float dtAsSeconds)
{
	
	//start of a new game we will need a new level
	if (m_NewLevelRequired)
	{
		loadLevel();
	}

	if (state == State::PLAYING)
	{
		// Update Player
		//player.update(dtAsSeconds);
		Vector2f playerPosition(player.getCenter());
		FloatRect pr = player.getPosition();


		// May 4 moving to top left coords not centre coords
		/*enemy.GhostChaseMoveTo(dtAsSeconds, pr, enemy.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		enemy.updateSprite(1);

		enemy.GhostChaseMoveTo(dtAsSeconds, pr, enemy.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		enemy.updateSprite(2);

		enemy.GhostChaseMoveTo(dtAsSeconds, pr, enemy.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		enemy.updateSprite(3);*/

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when Enemy is touching the home tile
		/*if (detectCollisions(enemy))
		{
			//proceed to new level
			m_NewLevelRequired = true;

		}
		else
		{
			//calling collision method for player and npcs
			detectCollisions(player);
			detectCollisions(enemy);
		}*/

		//Checking for collectible collision
		//std::list<PlayableCharacter>::iterator it;

		/*for (it = m_DotsList.begin(); it != m_DotsList.end();) {
			if (player.getPosition().intersects ((it)->getPosition()))
			{
				//Dec 14th 2021 calc distance d between the 2 points
				//if distance is less than 30 pixels remove the dot
				int x1 = player.getPosition().left;
				int y1 = player.getPosition().top;
				int x2 = (it)->getPosition().left;
				int y2 = (it)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared+ysquared);

				if (d < 30)
				{
					m_DotsList.erase(it++);
					cout << "Score: " << score << endl;
				}
				else
				{
					++it;
				}
			}
			else
			{
				++it;
			}*/

		}

//Dec 9th 2021 Desmond's Death Detection code and animation
		if (player.getPosition().intersects
		(enemy.getPosition()) || player.getPosition().intersects
		(enemy.getPosition()) || player.getPosition().intersects
		(enemy.getPosition()))
		{
			//player.setSpriteFromSheet(sf::IntRect{ 12,622,550,50 });
			//player.moveTextureRect();
			score--;
			cout << "Score: " << score << endl;
		}
		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Enemy and Player run out of time?
		if (m_TimeRemaining <= 0)
		{
			//m_NewLevelRequired = true;
		}

		if (player.getPosition().intersects(enemy.getPosition()) ||
			player.getPosition().intersects(enemy.getPosition()) ||
			player.getPosition().intersects(enemy.getPosition())) {

			//player.setSpriteFromSheet(sf::IntRect{ 12, 622, 550, 50 });
			//player.moveTextureRect();
			score--;

			// Decrease lives
			//m_Lives--;
			//cout << "Lives: " << m_Lives << endl;

			//reset score
			score = 0;

			// Check if all lives are lost
			//if (m_Lives <= 0) {
				//cout << "Game Over!" << endl;
				//state = State::MAIN_MENU; 
				//mainMenu = true;
			//}
		}

		//score text
		//std::stringstream ss;
		//ss << "Score: " << score;
		//scoreText.setString(ss.str());
	//}// End if playing
		

}