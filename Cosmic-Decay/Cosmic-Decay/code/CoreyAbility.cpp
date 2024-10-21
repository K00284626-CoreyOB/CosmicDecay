#include "CoreyAbility.h"
#include "Player.h"
#include <iostream>

CoreyAbility::CoreyAbility(Player& player)
    : Abilities(player), invulnerable(false)
{
}

void CoreyAbility::useAbility()
{
    if (!m_Active)
    {
        std::cout << "Corey uses Mask ability!\n";
        m_Active = true;
        invulnerable = true;

        // Grant invulnerability
        m_Player.setInvulnerable(true);

        // Start the ability timer
        m_Clock.restart();
    }
}

void CoreyAbility::update()
{
    if (m_Active && m_Clock.getElapsedTime().asSeconds() >= 10.0f)
    {
        std::cout << "Corey's Mask ability ended.\n";
        m_Active = false;
        invulnerable = false;

        // Remove invulnerability
        m_Player.setInvulnerable(false);
    }
}