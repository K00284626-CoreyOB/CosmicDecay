#pragma once
#include "PlayableCharacter.h"
#include "Bullet.h"
#include "Arm.h"
#include <SFML/Graphics.hpp>

class Player : public PlayableCharacter {
public:
    // Constructor specific to Player
    Player();

    // Overridden input handler for Player
    bool handleInput() override;

    // Overridden update method for Player
    void update(float elapsedTime) override;

    void moveTextureRect(float timeElapsed) override;

    // Draw method for the player and arm
    void draw(sf::RenderWindow& window);

    Arm& getArm();  // Return a reference to Arm

    // Where is the player
    FloatRect getPosition();

    // Ability methods
    void switchToMelee();
    void switchToGun();
    void increaseHealthLevel(int amount);
    void setHealth(float health);
    float getMaxHealth() const;
    void setInvulnerable(bool state);
    void setEnemiesIgnore(bool state);
    void setCanAttack(bool state);
    void setFireRateMultiplier(float multiplier);
    void setInfiniteAmmo(bool state);

    // Method to rotate the arm towards the mouse position
    void rotateArm(sf::RenderWindow& window);

    //for shop
    void increaseHealth();
    void increaseSpeed();

private:
    // Arm instance
    Arm m_Arm;

    // Member variables
    float m_Speed = 200.0f;
    float m_JumpDuration = 0.25f;
    bool m_JustJumped = false;

    // Input state
    bool m_UpPressed = false;
    bool m_DownPressed = false;
    bool m_LeftPressed = false;
    bool m_RightPressed = false;

    // Health and abilities
    float m_MaxHealth = 100.0f;
    bool m_Invulnerable = false;
    bool m_EnemiesIgnore = false;
    bool m_CanAttack = true;
    float m_FireRateMultiplier = 1.0f;
    bool m_InfiniteAmmo = false;
};