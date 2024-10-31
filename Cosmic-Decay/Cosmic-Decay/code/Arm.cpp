#include "Arm.h"
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



FloatRect Arm::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


/*
void Arm::update(float elapsedTime, Vector2i mousePosition)
{
	// Set the Arm's position relative to the player's position
	FloatRect playerPos = m_Player.getPosition();
	m_Position.x = playerPos.left;  // Adjust this if necessary for your positioning
	m_Position.y = playerPos.top;

	// Update the sprite position
	m_Sprite.setPosition(m_Position);

	
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2) * 180) / 3.141;
	m_Sprite.setRotation(angle);

	m_Sprite.setPosition(m_Position);
}
*/