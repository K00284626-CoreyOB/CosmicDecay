//Matthew O'Rourke Bourke

#include "stdafx.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

int score = 0;

void Engine::update(float dtAsSeconds)
{
	
	//start of a new game we will need a new level
	if (m_NewLevelRequired)
	{
		loadLevel();
	}

	if (state == State::PLAYING)
	{
		

		// Update Player
		player.update(dtAsSeconds);
		Vector2f playerPosition(player.getCenter());
		FloatRect pr = player.getPosition();




	}// End if playing
		

}