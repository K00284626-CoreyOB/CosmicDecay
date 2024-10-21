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
		
		
		m_Player.update(dtAsSeconds);
		Vector2f playerPosition(m_Player.getCenter());
		FloatRect pr = m_Player.getPosition();


// May 4 moving to top left coords not centre coords
		m_BlinkyGhost.GhostChaseMoveTo(dtAsSeconds, pr, m_BlinkyGhost.getSpeed(), m_ArrayLevel,m_LM.getLevelSize().y, m_LM.getLevelSize().x );
		m_BlinkyGhost.updateSprite(1);

		m_PinkyGhost.GhostChaseMoveTo(dtAsSeconds, pr, m_PinkyGhost.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		m_PinkyGhost.updateSprite(2);

		m_InkyGhost.GhostChaseMoveTo(dtAsSeconds, pr, m_InkyGhost.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		m_InkyGhost.updateSprite(3);
		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when Enemy is touching the home tile
		if  (detectCollisions(m_Player))
		{
			// New level required
			m_NewLevelRequired = true;

		}
		else
		{
			// Run Players collision detection
			detectCollisions(m_Player);
			detectCollisions(m_BlinkyGhost);
			detectCollisions(m_PinkyGhost);
     		detectCollisions(m_InkyGhost);
		}
//Dec 13th 2021 Check list of Dots to see if they intersect with Pacman
//if they intersect erase the dot from the list
		std::list<PlayableCharacter>::iterator it;
		
		for (it = m_DotsList.begin(); it != m_DotsList.end();) {
			if (m_Player.getPosition().intersects ((it)->getPosition()))
			{
				
				//Dec 14th 2021 calc distance d between the 2 points
				//if distance is less than 30 pixels remove the dot
				int x1 = m_Player.getPosition().left;
				int y1 = m_Player.getPosition().top;
				int x2 = (it)->getPosition().left;
				int y2 = (it)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared+ysquared);

				if (d < 30)
				{
					m_DotsList.erase(it++);
					score++;
					cout << score << endl;
					std::stringstream ss;
					ss << "Score = " << score;
					scoreText.setString(ss.str());
				}
				else
				{
					++it;
				}
			}
			else
			{
				++it;
			}

		}


//Dec 9th 2021 Desmond's Death Detection code and animation
		if (m_Player.getPosition().intersects
		(m_BlinkyGhost.getPosition()) || m_Player.getPosition().intersects
		(m_PinkyGhost.getPosition()) || m_Player.getPosition().intersects
		(m_InkyGhost.getPosition()))
		{
			m_Player.setSpriteFromSheet(sf::IntRect{ 12,622,550,50 });
			m_Player.moveTextureRect();
			score--;
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		}
		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Enemy and Player run out of time?
		if (m_TimeRemaining <= 0)
		{
			//m_NewLevelRequired = true;
		}

	}// End if playing
		

}