#pragma once
#include "GameCharacter.h"
//Szymon

class Enemy : public Character
{
public:
    //Overrides the GameCharacters update function
    void update() override;
};