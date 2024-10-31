#include "stdafx.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

int score = 0;

void Engine::update(float dtAsSeconds)
{
	if (m_Character1)
	{
		m_MainView.setCenter(m_Player.getCenter());
	}
	
	
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
		m_BlinkyGhost.updateSprite(1, dtAsSeconds);

		m_PinkyGhost.GhostChaseMoveTo(dtAsSeconds, pr, m_PinkyGhost.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		m_PinkyGhost.updateSprite(2, dtAsSeconds);

		m_InkyGhost.GhostChaseMoveTo(dtAsSeconds, pr, m_InkyGhost.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		m_InkyGhost.updateSprite(3, dtAsSeconds);
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

		if (m_Invincible)
		{
			m_InvincibleTime -= dtAsSeconds;
			if (m_InvincibleTime <= 0)
			{
				m_Invincible = false;
				m_InvincibleTime = INVINCIBILITY_DURATION;
			}
		}

		//Check list of fuses to see if they intersect with Pacman
		//if they intersect erase the fuse from the list
		std::list<PlayableCharacter>::iterator it;

		std::list<PlayableCharacter>::iterator itH;

		std::list<PlayableCharacter>::iterator itA;
		
		for (it = m_FusesList.begin(); it != m_FusesList.end();) {
			if (m_Player.getPosition().intersects ((it)->getPosition()))
			{
				
				//calculate distance d between the 2 points
				//if distance is less than 30 pixels remove the fuse
				int x1 = m_Player.getPosition().left;
				int y1 = m_Player.getPosition().top;
				int x2 = (it)->getPosition().left;
				int y2 = (it)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared+ysquared);

				if (d < 30)
				{
					m_FusesList.erase(it++);
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

		for (itH = m_HealthPickupList.begin(); itH != m_HealthPickupList.end();) {
			if (m_Player.getPosition().intersects((itH)->getPosition()))
			{

				//calculate distance d between the 2 points
				//if distance is less than 30 pixels remove the fuse
				int x1 = m_Player.getPosition().left;
				int y1 = m_Player.getPosition().top;
				int x2 = (itH)->getPosition().left;
				int y2 = (itH)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared + ysquared);

				if (d < 30)
				{
					m_HealthPickupList.erase(itH++);
					//ADD A LINE TO TO REGAIN HEALTH**************************************************
				}
				else
				{
					++itH;
				}
			}
			else
			{
				++itH;
			}

		}

		for (itA = m_AmmoPickupList.begin(); itA != m_AmmoPickupList.end();) {
			if (!m_Invincible && m_Player.getPosition().intersects((itA)->getPosition()))
			{

				//calculate distance d between the 2 points
				//if distance is less than 30 pixels remove the fuse
				int x1 = m_Player.getPosition().left;
				int y1 = m_Player.getPosition().top;
				int x2 = (itA)->getPosition().left;
				int y2 = (itA)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared + ysquared);

				

				if (d < 30)
				{
					m_AmmoPickupList.erase(itA++);
					//ADD A LINE A TO ADD AMMO TO STOCKPILE******** - Done
					bulletsSpare = bulletsSpare + 16;
					//debug
					cout << bulletsSpare << endl;
					m_Invincible = true;
					m_InvincibleTime = INVINCIBILITY_DURATION;
				}
				else
				{
					++itA;
				}
			}
			else
			{
				++itA;
			}

		}
        //Dec 9th 2021 Desmond's Death Detection code and animation
		if (m_Player.getPosition().intersects
		(m_BlinkyGhost.getPosition()) || m_Player.getPosition().intersects
		(m_PinkyGhost.getPosition()) || m_Player.getPosition().intersects
		(m_InkyGhost.getPosition()))
		{
			m_Player.setSpriteFromSheet(sf::IntRect{ 12,622,550,50 });
			m_Player.moveTextureRect(dtAsSeconds);
			//score--;
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		}

		//BULLET COLLISION WIP**************** - Matthew
		for (int i = 0; i <= 100; i++) 
		{
			if (bullets[i].isInFlight()) 
			{
				bullets[i].update(dtAsSeconds);
				if (bullets[i].getPosition().intersects(m_BlinkyGhost.getPosition())) 
				{
					bullets[i].stop();
					score++;
					std::stringstream ss;
					ss << "Score = " << score;
					scoreText.setString(ss.str());
				}
				else if (bullets[i].getPosition().intersects(m_PinkyGhost.getPosition())) 
				{
					bullets[i].stop();
					score++;
					std::stringstream ss;
					ss << "Score = " << score;
					scoreText.setString(ss.str());
				}
				else if (bullets[i].getPosition().intersects(m_InkyGhost.getPosition())) 
				{
					bullets[i].stop();
					score++;
					std::stringstream ss;
					ss << "Score = " << score;
					scoreText.setString(ss.str());
				}
			}
		}

	}// End if playing
		

}