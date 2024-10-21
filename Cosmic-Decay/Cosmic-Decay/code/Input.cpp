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
			
		}
		if (state == State::PLAYING)
		{

			// Handle the player quitting

			if (event.key.code == (Keyboard::Space))
			{
				state = State::PAUSED;
			}

		}

			// Switch between Enemy and Player

		
	}	



	// Handle input specific to Player
	if (m_PacMan.handleInput())
	{
		// Play a jump sound
	}

	if (state == State::MAIN_MENU)
	{
	//	window.draw(spriteMainMenu);
	//	window.draw(levelUpText);
	}
}