#pragma once
#include "Abilities.h"

class CoreyAbility : public Abilities
{
public:
    CoreyAbility(Player& player);
    virtual void useAbility() override;
    virtual void update() override;

private:
    bool invulnerable;
};