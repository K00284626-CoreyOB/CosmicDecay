#include "Hud.h"

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Position the text
	FloatRect textRect = m_StartText.getLocalBounds();

	m_StartText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	m_StartText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	//Ammo
	m_AmmoText.setFont(m_Font);
	m_AmmoText.setCharacterSize(90);
	m_AmmoText.setFillColor(Color::Black);
	m_AmmoText.setPosition(resolution.x - 550, 100);
	m_AmmoText.setString("Ammo: 6/24");

	//Health
	m_HealthText.setFont(m_Font);
	m_HealthText.setCharacterSize(90);
	m_HealthText.setFillColor(Color::Black);
	m_HealthText.setPosition(resolution.x - 550, 0);
	m_HealthText.setString("Health: 100");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(90);
	m_LevelText.setFillColor(Color::Black);
	m_LevelText.setPosition(resolution.x - 2530, 0);
	m_LevelText.setString("1");

	//Score
	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(90);
	m_ScoreText.setFillColor(Color::Black);
	m_ScoreText.setPosition(resolution.x - 2530, 100);
	m_ScoreText.setString("Score: -");
}

Text Hud::getMessage()
{
	return m_StartText;
}

Text Hud::getLevel()
{
	return m_LevelText;
}

Text Hud::getAmmo()
{
	return m_AmmoText;
}

Text Hud::getHealth()
{
	return m_HealthText;
}

Text Hud::getScore()
{
	return m_ScoreText;
}

void Hud::setLevel(String text)
{
	m_LevelText.setString(text);
}

void Hud::setAmmo(String text)
{
	m_AmmoText.setString(text);
}

void Hud::setHealth(String text)
{
	m_HealthText.setString(text);
}

void Hud::setScore(String text)
{
	m_ScoreText.setString(text);
}

void Hud::setStart(String text)
{
	m_StartText.setString(text);
}