#pragma once
#include "PlayableCharacter.h"
#include <SFML/Graphics.hpp>

class Player : public PlayableCharacter
{
public:
    // Constructor specific to Player
    Player();

    // Overridden input handler for Player
    bool handleInput() override;

    // Overridden update method for Player
    void update(float elapsedTime) override;

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

    
    //had to move to public
   
    

private:
    // Member variables
    float m_Speed = 200.0f;  // Speed of the player
    float m_JumpDuration = 0.25f;  // Duration of jump
    bool m_JustJumped = false; // Track jump state

    // Input state
    bool m_UpPressed = false;
    bool m_DownPressed = false;
    bool m_LeftPressed = false;
    bool m_RightPressed = false;

    // Health and abilities
    float m_MaxHealth = 100.0f;
    bool m_Invulnerable = false; // Track invulnerability state
    bool m_EnemiesIgnore = false; // Track if enemies ignore player
    bool m_CanAttack = true; // Track if player can attack
    float m_FireRateMultiplier = 1.0f; // Track fire rate multiplier
    bool m_InfiniteAmmo = false; // Track if player has infinite ammo

   
    //
    
    
};