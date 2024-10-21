#pragma once
#include "PlayableCharacter.h"
#include <SFML/Graphics.hpp>

class Player : public PlayableCharacter
{
public:
    // Constructor specific to Player
    Player();

    // Overridden input handler for Player
    bool virtual handleInput();

    // Overridden update method for Player
    void virtual update(float elapsedTime);

    // Health management functions
    void setHealth(float health) { m_CurrentHealth = health; }
    void increaseHealthLevel(int amount) { m_CurrentHealth += amount; }
    float getMaxHealth() const { return m_MaxHealth; }
    float getCurrentHealth() const { return m_CurrentHealth; }

    // Ability management
    void switchToMelee();
    void switchToGun();
    void setInvulnerable(bool state) { m_IsInvulnerable = state; }

private:
    // Health attributes
    float m_MaxHealth;            // Maximum health
    float m_CurrentHealth;        // Current health

    // State attributes
    bool m_InMeleeMode;          // Track if player is in melee mode
    bool m_IsInvulnerable;        // Track if player is invulnerable

    // Movement attributes
    sf::Vector2f m_Position;      // Current position
    float m_Speed;                // Movement speed

    // Collision rectangles
    sf::FloatRect m_Feet;         // Feet bounding box
    sf::FloatRect m_Head;         // Head bounding box
    sf::FloatRect m_Right;        // Right bounding box
    sf::FloatRect m_Left;         // Left bounding box
};