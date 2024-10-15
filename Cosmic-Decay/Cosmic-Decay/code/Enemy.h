#pragma once
//Szymon
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	// How fast is each enemy type?
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;
	const float BOSS_SPEED = 40;

	// How tough is each enemy type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;
	const float BOSS_HEALTH = 60;

	// Make each enemy vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// Where is this enemy?
	Vector2f m_Position;

	// A sprite for the enemy
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

	// Public prototypes go here	
public:

	// Handle when a bullet hits a enemy
	bool hit();

	// Find out if the enemy is alive
	bool isAlive();

	// Spawn a new enemy
	void spawn(float startX, float startY, int type, int seed);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the enemy each frame
	void update(float elapsedTime, Vector2f playerLocation);

	void setScale(float scaleX, float scaleY);

	void setSpeed(float speed);

	Vector2f getPositionVector();

};


