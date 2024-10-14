#include "Engine.h"

/* Author: Corey O'Brien  Version 1.0
Program Description: This class will be the Engine which will store most of the data needed.
Calls the run() method to initialise the game.*/

Engine::Engine()
{
	//Texture textureBackground = TextureHolder::GetTexture(
		//"textures/");

	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Thomas was late",
		Style::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	

	

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}
	

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/tempBackground.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);


	// Load the texture for the background vertex array
	//m_TextureTiles = TextureHolder::GetTexture(
	//	"graphics/tiles_sheet.png");
}

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		//update(dtAsSeconds);
		draw();
	}
}