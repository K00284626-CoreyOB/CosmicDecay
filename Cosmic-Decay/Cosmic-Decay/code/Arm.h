#pragma once
#include <SFML/Graphics.hpp>
#include "PlayableCharacter.h"
#include "Player.h"

using namespace sf;

class Arm : public PlayableCharacter
{
public:
    // Constructor specific to Player
    Arm();

    // Overridden input handler for Player
    
    // Overridden update method for Player
    //void update(float elapsedTime) override;

    //void virtual moveTextureRect(float timeElapsed);


    // Where is the player
    FloatRect getPosition();


private:
    
};