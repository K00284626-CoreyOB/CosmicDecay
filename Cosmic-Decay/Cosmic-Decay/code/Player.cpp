#include "stdafx.h"
#include "Player.h"
#include "TextureHolder.h"
#include <iostream>

Player::Player()

{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/pacman-spritesheet-resized-810-730.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 12,62,50,50 });
	ani_counter = 1;

	m_JumpDuration = .25;


}

bool Player::handleInput()
{
	m_JustJumped = false;
	
	float joyOnePovY = 0;
	float joyOnePovX = 0;
	bool joyOneConnected = sf::Joystick::isConnected(0);
	if (joyOneConnected) {
		joyOnePovY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
		joyOnePovX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
	}



	//2019 up and down movement
	if (Keyboard::isKeyPressed(Keyboard::Up) || (joyOnePovY == 100))
	{
		m_UpPressed = true;

	}
	else
	{
		m_UpPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::Down) || (joyOnePovY==-100))
	{
		m_DownPressed = true;

	}
	else
	{
		m_DownPressed = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) || (joyOnePovX == -100))
	{
		m_LeftPressed = true;

	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::Right) || (joyOnePovX == 100))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}
void Player::update(float elapsedTime)
{
	timeElapsed = elapsedTime;

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
		direction = sf::Vector2f(0, -1);
		//2nd row of sprite sheet 3 characters 150 pixels by 50 pixels
		setSpriteFromSheet(sf::IntRect(12, 62, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();

	}
	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
		direction = sf::Vector2f(0, 1);
		//1st row of sprite sheet 3 characters
		setSpriteFromSheet(sf::IntRect(12, 12, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();

	}

	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
		direction = sf::Vector2f(1, 0);
		//3rd row of sprite sheet 3 characters
		setSpriteFromSheet(sf::IntRect(12, 112, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();


	}

	if (m_DownPressed)
	{

		m_Position.y += m_Speed * elapsedTime;
		direction = sf::Vector2f(-1, 0);
		//4th row of sprite sheet 3 characters
		setSpriteFromSheet(sf::IntRect(12, 162, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();

	}







	// Update the rect for all body parts
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left + 3;
	m_Head.top = r.top-1;
	m_Head.width = r.width - 6;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 1;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left+1;
	m_Left.top = r.top + r.height * .35;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

	// Move the sprite into position
	updateLeftRightHeadFeet();
	m_Sprite.setPosition(m_Position);

}