#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 500;

	int m_Type;

public:
	Player();

	void spawn();

matthew
};