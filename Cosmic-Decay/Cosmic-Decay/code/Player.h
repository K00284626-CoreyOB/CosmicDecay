
#pragma once
#include "PlayableCharacter.h"


class Player : public PlayableCharacter
{

public:
	// A constructor specific to Player
	Player();

	// The overriden input handler for Player
	bool virtual handleInput();
	void virtual update(float elapsedTime);
};

#pragma once
