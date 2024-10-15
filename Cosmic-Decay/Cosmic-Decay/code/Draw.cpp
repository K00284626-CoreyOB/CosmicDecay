#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	//if (!m_SplitScreen)
	//{
		// Switch to background view
	m_Window.setView(m_BGMainView);
	// Draw the background
	m_Window.draw(m_BackgroundSprite);

	// Switch to m_MainView
	m_Window.setView(m_MainView);

	m_Window.draw(player.getSprite());


	// Show everything we have just drawn
	m_Window.display();
}