#include "stdafx.h"
#include "Engine.h"
using namespace sf;




Engine::Engine()
{
	//Sounds
	shootBuffer.loadFromFile("sound/shoot.MP3");
	shootSound.setBuffer(shootBuffer);

	reloadBuffer.loadFromFile("sound/reload.WAV");
	reloadSound.setBuffer(reloadBuffer);

	reachedGoalBuffer.loadFromFile("sound/reachgoal.WAV");
	reachedGoalSound.setBuffer(reachedGoalBuffer);

	pickupBuffer.loadFromFile("sound/pickup.WAV");
	pickupSound.setBuffer(pickupBuffer);

	playerHurtBuffer.loadFromFile("sound/playerHurt.WAV");
	playerHurtSound.setBuffer(playerHurtBuffer);

	enemyHurtBuffer.loadFromFile("sound/enemyHurt.WAV");
	enemyHurtSound.setBuffer(enemyHurtBuffer);

	scoreFont.loadFromFile("fonts/KOMIKAP_.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::Magenta);
	scoreText.setPosition(1500, 20);
	score = 0;

	shopText.setFont(scoreFont);
	shopText.setCharacterSize(40);
	shopText.setFillColor(Color::White);
	shopText.setPosition(150, 250);
	std::stringstream shopStream;
	shopStream <<
		"1- Increased rate of fire (10 points)" <<
		"\n2- Double clip size (20 points)" <<
		"\n3- Increased sprint speed (15 points)"<<
		"\n4- Exit";
	shopText.setString(shopStream.str());

	m_InvincibleTime = 0;

	// Ammo
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::Magenta);
	ammoText.setPosition(200, 20);

	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	state = State::MAIN_MENU;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Cosmic Decay",
		Style::Fullscreen);
//	m_Window.setFramerateLimit(30);
	//sf::Window::setFramerateLimit(unsigned int 	limit)


	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_MainView.setCenter(resolution.x / 2, resolution.y / 2);

	// Two lines below used to create zoomed our screenshots for the book
	//m_BGMainView.zoom(2.5);
	m_MainView.zoom(0.8);
	m_HudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));

	// 100 bullets should do
	currentBullet = 0;
	bulletsSpare = 24;
	bulletsInClip = 6;
	clipSize = 6;
	fireRate = 1;

	

	// Hide the mouse pointer and replace it with crosshair
	m_Window.setMouseCursorVisible(false);
	textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);


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

	std::string currentLevelFile = m_levelManager.getLevelToLoad();

	cout << currentLevelFile << endl;

	
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");
	
	


	textureMainMenu = TextureHolder::GetTexture("graphics/cosmicDecayPoster.png");
	spriteMainMenu.setTexture(textureMainMenu);
	spriteMainMenu.setPosition(0, 0);
	spriteMainMenu.setScale(0.4, 0.75);


	font.loadFromFile("fonts/KOMIKAP_.ttf");


	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(80);
	mainMenuText.setFillColor(Color::White);
	mainMenuText.setPosition(150, 50);
	std::stringstream mainMenuStream;
	mainMenuStream <<
		"\n1 - Play Game" <<
		"\n2 - High Scores " <<
		"\n3 - Exit";

	mainMenuText.setString(mainMenuStream.str());

	//character selection screen
	charSelectText.setFont(font);
	charSelectText.setCharacterSize(80);
	charSelectText.setFillColor(Color::White);
	charSelectText.setPosition(150, 50);
	std::stringstream charSelectStream;
	charSelectStream <<
		"\n1 - Zach" <<
		"\n2 - Szymon" <<
		"\n3 - Matthew" <<
		"\n4 - Corey" <<
		"\n5 - Return to Menu";

	charSelectText.setString(charSelectStream.str());

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

		if (state == State::PLAYING)
		{
			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = m_Window.mapPixelToCoords(
				Mouse::getPosition(), m_MainView);

			// Set the crosshair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);
		}

		input();
		update(dtAsSeconds);
		draw();
	}
}