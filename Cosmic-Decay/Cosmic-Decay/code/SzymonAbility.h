#pragma once
#include "Abilities.h"

class SzymonAbility : public Abilities
{
public:
    SzymonAbility(Player& player);
    virtual void useAbility() override;
    virtual void update() override;

private:
    bool increasedFireRate;
    bool infiniteAmmo;
};