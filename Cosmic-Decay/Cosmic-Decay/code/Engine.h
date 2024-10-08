#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Arena.h"
#include "TextureHolder.h"
#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"


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
	View mainView;

	// Here is our clock for timing everything
	Clock clock;

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

public:
	Engine();

	void run();
};