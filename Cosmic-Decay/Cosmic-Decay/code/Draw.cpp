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

		//Dec 13th 2021 Draw fuses
		std::list<PlayableCharacter>::iterator it;

		for (it = m_FusesList.begin(); it != m_FusesList.end(); it++) {
			m_Window.draw((it)->getSprite());
		}

		std::list<PlayableCharacter>::iterator itH;

		for (itH = m_HealthPickupList.begin(); itH != m_HealthPickupList.end(); itH++) {
			m_Window.draw((itH)->getSprite());
		}

		std::list<PlayableCharacter>::iterator itA;

		for (itA = m_AmmoPickupList.begin(); itA != m_AmmoPickupList.end(); itA++) {
			m_Window.draw((itA)->getSprite());
		}
		m_Window.draw(spriteCrosshair);

		m_Window.draw(m_Player.getSpriteFromSheet());
		

		// Draw Enemy
		if (m_ZombieAlien1.isActive())
		{
			m_Window.draw(m_ZombieAlien1.getSprite());
		}
		if (m_ZombieAlien2.isActive())
		{
			m_Window.draw(m_ZombieAlien2.getSprite());
		}
		if (m_ZombieAlien3.isActive())
		{
			m_Window.draw(m_ZombieAlien3.getSprite());
		}

		
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				m_Window.draw(bullets[i].getShape());
			}
		}

		// Draw the HUD
	// Switch to m_HudView
		m_Window.setView(m_HudView);
		m_Window.draw(m_Hud.getLevel());
		m_Window.draw(m_Hud.getScore());
		m_Window.draw(m_Hud.getAmmo());
		m_Window.draw(m_Hud.getHealth());
		m_Window.draw(m_Hud.getFuse());
		m_Window.draw(m_Hud.getBackground());
		m_Window.draw(m_Hud.getBackground2());
		if (!m_Playing)
		{
			m_Window.draw(m_Hud.getMessage());
		}

		//m_Window.draw(scoreText);
	}
	if (state == State::MAIN_MENU)
	{
		m_Window.clear(Color::Black);


		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(spriteMainMenu);
		m_Window.draw(mainMenuText);

	}

	if (state == State::PAUSED)
	{
		m_Window.clear(Color::Black);


		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(spriteMainMenu);
		m_Window.draw(pauseMenuText);

	}
	
	// Show everything we have just drawn
	m_Window.display();
}