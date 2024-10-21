#pragma once
#include <SFML/Graphics.hpp>
#include <memory> 
#include "Abilities.h"

using namespace sf;

class Player
{
private:
    const float START_SPEED = 200.0f;
    const float START_HEALTH = 100.0f;

    // Player attributes
    Vector2f m_Position;
    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_Resolution;
    IntRect m_Arena;
    int m_TileSize;

    // Movement flags
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;

    // Health
    int m_Health;
    int m_MaxHealth;

    // Last hit time
    Time m_LastHit;

    // Speed
    float m_Speed;

    // Ability system
    std::unique_ptr<Abilities> m_Ability;

    // Ability-related states
    bool m_Invulnerable;
    float m_FireRateMultiplier;
    bool m_InfiniteAmmo;
    bool m_EnemiesIgnore;
    bool m_CanAttack;

public:
    Player();

    // Reset player stats
    void resetPlayerStats();

    // Spawn the player
    void spawn(IntRect arena, Vector2f resolution, int tileSize);

    // Handle getting hit
    bool hit(Time timeHit);

    // Get last hit time
    Time getLastHitTime();

    // Getters
    FloatRect getPosition();
    Vector2f getCenter();
    float getRotation();
    Sprite getSprite();
    int getHealth();
    int getMaxHealth() const { return m_MaxHealth; }

    // Movement
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    // Update
    void update(float elapsedTime, Vector2i mousePosition);

    // Upgrades
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);

    // Ability management
    void setAbility(std::unique_ptr<Abilities> ability);
    void useAbility();
    void updateAbility();

    // Ability-related setters
    void switchToMelee();
    void switchToGun();
    void setInvulnerable(bool invuln);
    void setFireRateMultiplier(float multiplier);
    void setInfiniteAmmo(bool infinite);
    void setEnemiesIgnore(bool ignore);
    void setCanAttack(bool canAttack);

    // Additional getters as needed
    float getSpeed() const { return m_Speed; }
    bool canAttackState() const { return m_CanAttack; }

    // Get maximum health
    int getMaxHealthValue() const { return m_MaxHealth; }
};