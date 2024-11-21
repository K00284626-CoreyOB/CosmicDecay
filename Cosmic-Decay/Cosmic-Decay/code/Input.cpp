#include "stdafx.h"
#include "Engine.h"
#include "PlayableCharacter.h"

void Engine::input()
{
	

	bool exit_loop = false;
	Event event;
	Event event2;

	while (m_Window.pollEvent(event))
	{
		if (state == State::MAIN_MENU) 
		{
			if (event.key.code == Keyboard::Num1)
			{
				event.key.code = Keyboard::Num0;
				state = State::CHAR_SELECT;
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

		if (state == State::CHAR_SELECT)
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Num1) //Choose Zach
				{
					m_Type = 1;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::Num2) //Choose Szymon
				{
					m_Type = 2;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::Num3) //Choose Matthew
				{
					m_Type = 3;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::Num4) //Choose Corey
				{
					m_Type = 4;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::Num5) //Return to menu
				{
					event.key.code = Keyboard::Num0;
					state = State::MAIN_MENU;
				}

				if (event.key.code == Keyboard::S)
				{
					state = State::SHOP;
				}
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

		//Shop system WIP************
		if (state == State::SHOP)
		{
			if (event.key.code == Keyboard::Num1 && score >= 10)
			{
				//Increase the fire rate by 1
				fireRate++;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2 && score >= 20)
			{
				//double the clip size
				clipSize += clipSize;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3 && score >= 15)
			{
				// Increase speed
				m_Player.increaseSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				// Increase speed
				m_Player.increaseSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				//exit shop
				state = State::PLAYING;
			}
		}// End levelling up

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
				//updating reload - changed so it reloads only the ammo that is needed, fixed issue where it reloaded double clip size
				int bulletsNeeded = clipSize - bulletsInClip;

				if (bulletsSpare >= bulletsNeeded) {
					bulletsInClip += bulletsNeeded;
					bulletsSpare -= bulletsNeeded;
				}
				else if (bulletsSpare > 0) {
					bulletsInClip += bulletsSpare;
					bulletsSpare = 0;
				}

				reloadSound.play();
				//display ammo count to hud
				std::stringstream ss;
				ss << "Ammo: " << bulletsInClip << "/" << bulletsSpare;
				m_Hud.setAmmo(ss.str());
				
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
					shootSound.play();
					bulletsInClip--;

					//update ammo count on screen
					std::stringstream ss;
					ss << "Ammo: " << bulletsInClip << "/" << bulletsSpare;
					m_Hud.setAmmo(ss.str());
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

}

void Engine::startPlaying()
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