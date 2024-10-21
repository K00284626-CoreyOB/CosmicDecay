#pragma once
#include "Abilities.h"
#include <SFML/Graphics.hpp>

class ZachAbility : public Abilities
{
public:
    ZachAbility(Player& player);
    virtual void useAbility() override;
    virtual void update() override;

private:
    bool meleeMode;
    float originalHealth;
};