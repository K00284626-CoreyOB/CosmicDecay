#pragma once
#include "Abilities.h"

class MatthewAbility : public Abilities
{
public:
    MatthewAbility(Player& player);
    virtual void useAbility() override;
    virtual void update() override;

private:
    bool enemiesIgnore;
    bool canAttack;
};