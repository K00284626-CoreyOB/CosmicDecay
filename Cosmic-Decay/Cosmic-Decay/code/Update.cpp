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
		if (m_ShowReadyGraphic) {
			// Increment the timer
			m_ReadyTimer += dtAsSeconds;

			// Check if 3 seconds have passed
			if (m_ReadyTimer >= 3.0f) {
				m_ShowReadyGraphic = false; // Hide the "Ready" graphic after 3 seconds
			}
		}

		// Update Player
		m_PacMan.update(dtAsSeconds);
		Vector2f playerPosition(m_PacMan.getCenter());
		FloatRect pr = m_PacMan.getPosition();


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
		if  (detectCollisions(m_PacMan))
		{
			// New level required
			m_NewLevelRequired = true;

		}
		else
		{
			// Run Players collision detection
			detectCollisions(m_PacMan);
			detectCollisions(m_BlinkyGhost);
			detectCollisions(m_PinkyGhost);
     		detectCollisions(m_InkyGhost);
		}
//Dec 13th 2021 Check list of Dots to see if they intersect with Pacman
//if they intersect erase the dot from the list
		std::list<PlayableCharacter>::iterator it;

		for (it = m_DotsList.begin(); it != m_DotsList.end();) {
			if (m_PacMan.getPosition().intersects ((it)->getPosition()))
			{
				//Dec 14th 2021 calc distance d between the 2 points
				//if distance is less than 30 pixels remove the dot
				int x1 = m_PacMan.getPosition().left;
				int y1 = m_PacMan.getPosition().top;
				int x2 = (it)->getPosition().left;
				int y2 = (it)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared+ysquared);

				if (d < 30)
				{
					m_DotsList.erase(it++);
					score += (m_IsDoubleScoreActive) ? 2 : 1;
					cout << "Score: " << score << endl;

					m_DotsEatenCount++;

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

		for (it = m_KeyList.begin(); it != m_KeyList.end();) {
			if (m_PacMan.getPosition().intersects((it)->getPosition()))
			{
				//Dec 14th 2021 calc distance d between the 2 points
				//if distance is less than 30 pixels remove the dot
				int x1 = m_PacMan.getPosition().left;
				int y1 = m_PacMan.getPosition().top;
				int x2 = (it)->getPosition().left;
				int y2 = (it)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared + ysquared);

				if (d < 30)
				{
					m_KeyList.erase(it++);
					m_IsDoubleScoreActive = true;
					m_DoubleScoreTimer = 6.0f;
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
			}

			if (m_IsDoubleScoreActive) {
				m_DoubleScoreTimer -= dtAsSeconds;
				if (m_DoubleScoreTimer <= 0) {
					m_IsDoubleScoreActive = false;
				}
			}

		}

//Dec 9th 2021 Desmond's Death Detection code and animation
		if (m_PacMan.getPosition().intersects
		(m_BlinkyGhost.getPosition()) || m_PacMan.getPosition().intersects
		(m_PinkyGhost.getPosition()) || m_PacMan.getPosition().intersects
		(m_InkyGhost.getPosition()))
		{
			m_PacMan.setSpriteFromSheet(sf::IntRect{ 12,622,550,50 });
			m_PacMan.moveTextureRect();
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

		if (m_PacMan.getPosition().intersects(m_BlinkyGhost.getPosition()) ||
			m_PacMan.getPosition().intersects(m_PinkyGhost.getPosition()) ||
			m_PacMan.getPosition().intersects(m_InkyGhost.getPosition())) {

			m_PacMan.setSpriteFromSheet(sf::IntRect{ 12, 622, 550, 50 });
			m_PacMan.moveTextureRect();
			score--;

			// Decrease lives
			m_Lives--;
			cout << "Lives: " << m_Lives << endl;

			// Reset dots eaten count since Pacman lost a life
			m_DotsEatenCount = 0;

			// Check if all lives are lost
			if (m_Lives <= 0) {
				cout << "Game Over!" << endl;
				//state = State::MAIN_MENU; 
				m_ShowGameOver = true;
			}
		}

		if (m_DotsEatenCount >= 25) {
			m_Lives++;
			cout << "Extra Life Earned! Lives: " << m_Lives << endl;
			m_DotsEatenCount = 0; // Reset the counter after earning an extra life
		}

		//score text
		std::stringstream ss;
		ss << "Score: " << score;
		scoreText.setString(ss.str());

		// Create a string to show the number of lives
		std::stringstream livesStream;
		livesStream << "Lives: " << m_Lives;
		livesText.setString(livesStream.str());

	}// End if playing
		

}