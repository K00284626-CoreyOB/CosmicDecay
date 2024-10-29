#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Arm
{
private:

	// Where is the Arm
	Vector2f m_Position;

	// Of course we will need a sprite
	Sprite m_Sprite;

	// And a texture
	// !!Watch this space!!
	Texture m_Texture;

	// What is the screen resolution
	Vector2f m_Resolution;

	// What size is the current arena
	IntRect m_Arena;

	// How big is each tile of the arena
	int m_TileSize;

	

	// All our public functions will come next
public:

	Arm();

	// Call this at the end of every game
	
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	
	// Where is the Arm
	FloatRect getPosition();

	// Where is the center of the Arm
	Vector2f getCenter();

	// Which angle is the Arm facing
	float getRotation();

	// Send a copy of the sprite to main
	Sprite getSprite();


	// We will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	


};



#pragma once
