#include "stdafx.h"
#include "Engine.h"

void Engine::input()
{
	bool exit_loop = false;
	Event event;

	while (m_Window.pollEvent(event))
	{
		if (state == State::MAIN_MENU) 
		{
			// Handle the player levelling up
			if (event.key.code == Keyboard::Num1)
			{
				// Increase fire rate
				m_LM.setCurrentLevel(0);
				m_NewLevelRequired = true;
				state = State::PLAYING;

				//wave = 0;
				score = 0;

				// Prepare the gun and ammo for next game
				currentBullet = 0;
				bulletsSpare = 24;
				bulletsInClip = 6;
				clipSize = 6;
				fireRate = 1;

				// Reset the player's stats
				//player.resetPlayerStats();
			
			}

			if (event.key.code == Keyboard::Num2)
			{
				
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				state = State::GAME_OVER;
			}
		}
		if (state == State::PAUSED)
		{

			if (event.key.code == Keyboard::R)
			{

				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::M)
			{
				state = State::MAIN_MENU;
				exit_loop = true;

				
			}

		}
		if (state == State::GAME_OVER)
		{
			m_Window.close();
		}

		if (state == State::PLAYING)
		{
			bool joyMenuPressed = sf::Joystick::isButtonPressed(0, 7);

			// Handle the player quitting

				if (event.key.code==(Keyboard::Escape) || joyMenuPressed)
				{
					state = State::MAIN_MENU;
				}
		

			// Handle the player quitting

			if (event.key.code == (Keyboard::Space))
			{
				state = State::PAUSED;
			}

		
			// Reloading
			if (event.key.code == Keyboard::R)
			{
				if (bulletsSpare >= clipSize)
				{
					// Plenty of bullets. Reload.
					bulletsInClip = clipSize;
					bulletsSpare -= clipSize;
					//reload.play();
				}
				else if (bulletsSpare > 0)
				{
					// Only few bullets left
					bulletsInClip = bulletsSpare;
					bulletsSpare = 0;
					//reload.play();
				}
				else
				{
					// More here soon?!
					//reloadFailed.play();
				}
			}

			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (m_GameTimeTotal.asMilliseconds()
					- m_LastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
				{

					// Pass the centre of the player and the centre of the crosshair
					// to the shoot function
					bullets[currentBullet].shoot(
						m_Player.getCenter().x, m_Player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					m_LastPressed = m_GameTimeTotal;
					//shoot.play();
					bulletsInClip--;
				}

			}// End fire a bullet
		}



			// Switch between Enemy and Player

		
	}	



	// Handle input specific to Player
	if (m_Player.handleInput())
	{
		// Play a jump sound
	}

	if (state == State::MAIN_MENU)
	{
	//	window.draw(spriteMainMenu);
	//	window.draw(levelUpText);
	}
}