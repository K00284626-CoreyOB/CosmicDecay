#include "Arm.h"
#include "Player.h"
#include "Engine.h"
#include "TextureHolder.h"

Arm::Arm()
{

	// Associate a texture with the sprite
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/playerSpriteSheet2.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 0, 50, 50, 50 });

	m_Sprite.setOrigin(15, 77);
}


void Arm::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the Arm in the middle of the arena
	m_Position.x = m_Player;
	m_Position.y = arena.height / 2;

	// Copy the details of the arena to the Arm's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

}



FloatRect Arm::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Arm::getCenter()
{
	return m_Position;
}

float Arm::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Arm::getSprite()
{
	return m_Sprite;
}


void Arm::update(float elapsedTime, Vector2i mousePosition)
{

	

	m_Sprite.setPosition(m_Position);



	// Keep the Arm in the arena
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	// Calculate the angle the Arm is facing
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);
}