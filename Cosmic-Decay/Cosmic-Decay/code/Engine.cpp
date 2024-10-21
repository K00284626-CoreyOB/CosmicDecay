#include "stdafx.h"
#include "Engine.h"
using namespace sf;




Engine::Engine()
{
	scoreFont.loadFromFile("fonts/KOMIKAP_.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::Magenta);
	scoreText.setPosition(1120, 20);
	score = 0;

	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	state = State::MAIN_MENU;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Maze follow",
		Style::Fullscreen);
//	m_Window.setFramerateLimit(30);
	//sf::Window::setFramerateLimit(unsigned int 	limit)


	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_MainView.setCenter(resolution.x / 2, resolution.y / 2);

	// Two lines below used to create zoomed our screenshots for the book
	//m_BGMainView.zoom(2.5);
	m_MainView.zoom(1.5);
	m_HudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));




	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");


	textureMainMenu = TextureHolder::GetTexture("graphics/background-menu.png");
	spriteMainMenu.setTexture(textureMainMenu);
	spriteMainMenu.setPosition(0, 0);


	font.loadFromFile("fonts/KOMIKAP_.ttf");


	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(80);
	mainMenuText.setFillColor(Color::White);
	mainMenuText.setPosition(150, 250);
	std::stringstream mainMenuStream;
	mainMenuStream <<
		"Run Away !" <<
		"\n1 - Play Game" <<
		"\n2 - High Scores " <<
		"\n3- Exit";

	mainMenuText.setString(mainMenuStream.str());
	// pause menu options
	pauseMenuText.setFont(font);
	pauseMenuText.setCharacterSize(80);
	pauseMenuText.setFillColor(Color::White);
	pauseMenuText.setPosition(150, 250);
	std::stringstream pauseMenuStream;
	pauseMenuStream <<
		"Game Paused "<<
		"\nR - Resume" <<
		"\nM - Exit to Menu";

	pauseMenuText.setString(pauseMenuStream.str());

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
		update(dtAsSeconds);
		draw();
	}
}