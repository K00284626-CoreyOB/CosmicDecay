#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "LevelManager.h"
#include "TextureHolder.h"
#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"
#include <list>

//using namespace sf;

class Engine
{
private:
	//The texture holder
	TextureHolder Th;

	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

	// Start with the GAME_OVER state
	State state = State::GAME_OVER;

	// Get the screen resolution and create an SFML window
	Vector2f resolution;

	// Create a an SFML View for the main action
	View m_MainView;
	View m_BGMainView;

	// Here is our clock for timing everything
	Clock clock;
	Time m_GameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// Create the background
	VertexArray background;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;

	// The Hud
	//Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	// A regular RenderWindow
	RenderWindow m_Window;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

	//create background function
	int loadBackground(VertexArray& rVA, IntRect arena);


	//Matthew changes ----
	void loadLevel();
	
	int** m_ArrayLevel = NULL;
	int** m_ArraySpawningPointsLevel = NULL;

	bool m_Playing = false;

	LevelManager m_LM;

	const int GRAVITY = 0;

	VertexArray m_VALevel;

	bool m_NewLevelRequired = true;

	//std::list<PlayableCharacter> m_DotsList;

	//std::list<PlayableCharacter> m_KeyList;

	float m_TimeRemaining = 5;
	Time m_GameTimeTotal;

	//Enemy* createHorde(int numEnemies, IntRect arena, int wave);

public:
	Engine();

	void run();
};