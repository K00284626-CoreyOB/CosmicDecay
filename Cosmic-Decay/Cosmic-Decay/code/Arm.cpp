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

