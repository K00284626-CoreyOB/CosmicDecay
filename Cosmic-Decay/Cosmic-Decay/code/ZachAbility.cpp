#include "ZachAbility.h"
#include "Player.h"
#include <iostream>

ZachAbility::ZachAbility(Player& player)
    : Abilities(player), meleeMode(false), originalHealth(0.0f)
{
}

void ZachAbility::useAbility()
{
    if (!m_Active)
    {
        std::cout << "Zach uses CatZach ability!\n";
        m_Active = true;
        meleeMode = true;

        // Replace gun with melee
        m_Player.switchToMelee();

        // Increase health by 1.5x
        originalHealth = m_Player.getMaxHealth();
        m_Player.increaseHealthLevel(static_cast<int>(originalHealth * 0.5f));

        // Start the ability timer
        m_Clock.restart();
    }
}

void ZachAbility::update()
{
    if (m_Active && m_Clock.getElapsedTime().asSeconds() >= 10.0f)
    {
        std::cout << "Zach's CatZach ability ended.\n";
        m_Active = false;
        meleeMode = false;

        // Switch back to gun
        m_Player.switchToGun();

        
        // m_Player.setHealth(originalHealth);
    }
}