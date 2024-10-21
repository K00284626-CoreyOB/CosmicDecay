#include "stdafx.h"
#include "Enemy.h"
#include "TextureHolder.h"

Enemy::Enemy()
{
	// Associate a texture with the sprite, this will be changed later
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/e1.png"));

	m_JumpDuration = .45;
}
void Enemy::setSprite(int e_type)
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/pacman-spritesheet-resized-810-730.png"));
	// Associate a texture with the sprite
	if (e_type == 1)
	{
		//Blinky Red
		m_Sprite.setTextureRect(sf::IntRect{ 12,212,50,50 });
	}
	else if (e_type == 2)
	{
		//Pinky Pink
		m_Sprite.setTextureRect(sf::IntRect{ 12,262,50,50 });
	}
	else if (e_type == 3)
	{
		//inky Cyan
		m_Sprite.setTextureRect(sf::IntRect{ 12,312,50,50 });
	}
	else if (e_type == 4)
	{
		//Clyde Orange
		m_Sprite.setTextureRect(sf::IntRect{ 12,362,50,50 });
	}

	m_JumpDuration = .45;
}

void Enemy::updateSprite(int e_type)
{
	int offset=0;
	//up
	if (direction == sf::Vector2f(1, 0))
	{
		offset = 0;
	}

	//down
	if (direction == sf::Vector2f(-1, 0))
	{
		offset = 100;
	}

	//left
	if (direction == sf::Vector2f(0, 1))
	{
		offset = 200;
	}

	//right
	if (direction == sf::Vector2f(0, -1))
	{
		offset = 300;
	}

	if (e_type == 1)
	{

		setSpriteFromSheet(sf::IntRect{ 12+offset,212,100,50 });
		moveTextureRect();
	}
	else if (e_type == 2)
	{
		setSpriteFromSheet(sf::IntRect{ 12 + offset,262,100,50 });
		moveTextureRect();
	}
	else if (e_type == 3)
	{

		setSpriteFromSheet(sf::IntRect{ 12 + offset,312,100,50 });
		moveTextureRect();
	}
	else
	{
		setSpriteFromSheet(sf::IntRect{ 12 + offset,312,100,50 });
		moveTextureRect();
	}



	m_Sprite.setPosition(m_Position);
}


// A virtual function
bool Enemy::handleInput()
{
	
	m_JustJumped = false;

	return m_JustJumped;

}