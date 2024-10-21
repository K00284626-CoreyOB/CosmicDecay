#include "stdafx.h"
#include "Engine.h"

void Engine::draw()
{

	if (state == State::PLAYING)
	{
		// Rub out the last frame
		m_Window.clear(Color::White);


		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(m_BackgroundSprite);
		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the 

		m_Window.draw(m_VALevel, &m_TextureTiles);

		//Dec 13th 2021 Draw Dots
		std::list<PlayableCharacter>::iterator it;

		for (it = m_DotsList.begin(); it != m_DotsList.end(); it++) {
			m_Window.draw((it)->getSprite());
		}
		// Draw player
		m_Window.draw(m_PacMan.getSpriteFromSheet());

		// Draw Enemy
		m_Window.draw(m_BlinkyGhost.getSprite());
		m_Window.draw(m_PinkyGhost.getSprite());
		m_Window.draw(m_InkyGhost.getSprite());

		
		




		// Draw the HUD
		// Switch to m_HudView
		m_Window.setView(m_HudView);

		m_Window.draw(scoreText);
	}
	if (state == State::MAIN_MENU)
	{
		m_Window.clear(Color::Black);


		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(spriteMainMenu);
		m_Window.draw(mainMenuText);
		// Switch to m_MainView
//		m_Window.setView(m_MainView);
		m_Window.setView(m_HudView);

	}

	if (state == State::PAUSED)
	{
		m_Window.clear(Color::Black);


		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(spriteMainMenu);
		m_Window.draw(pauseMenuText);
		// Switch to m_MainView
//		m_Window.setView(m_MainView);
		m_Window.setView(m_HudView);

	}
	
	// Show everything we have just drawn
	m_Window.display();
}