#include "Player.h"
#include "TextureHolder.h"
#include <cmath>
#include <iostream>

// Constructor
Player::Player()
    : m_Speed(START_SPEED),
    m_Health(static_cast<int>(START_HEALTH)),
    m_MaxHealth(static_cast<int>(START_HEALTH)),
    m_Position(0.f, 0.f),
    m_UpPressed(false),
    m_DownPressed(false),
    m_LeftPressed(false),
    m_RightPressed(false),
    m_Invulnerable(false),
    m_FireRateMultiplier(1.0f),
    m_InfiniteAmmo(false),
    m_EnemiesIgnore(false),
    m_CanAttack(true)
{
    // Load default texture (assuming Zach is default)
    m_Texture = TextureHolder::GetTexture("graphics/zachIdle.png");
    m_Sprite.setTexture(m_Texture);

    // Set origin to center for smooth rotation
    m_Sprite.setOrigin(m_Texture.getSize().x / 2.f, m_Texture.getSize().y / 2.f);
}

// Reset player stats
void Player::resetPlayerStats()
{
    m_Speed = START_SPEED;
    m_Health = static_cast<int>(START_HEALTH);
    m_MaxHealth = static_cast<int>(START_HEALTH);
    m_Invulnerable = false;
    m_FireRateMultiplier = 1.0f;
    m_InfiniteAmmo = false;
    m_EnemiesIgnore = false;
    m_CanAttack = true;

    // Switch back to default weapon if necessary
    switchToGun();
}

// Spawn the player
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
    m_Arena = arena;
    m_Resolution = resolution;
    m_TileSize = tileSize;

    // Place the player in the middle of the arena
    m_Position.x = arena.width / 2.f;
    m_Position.y = arena.height / 2.f;

    m_Sprite.setPosition(m_Position);
}

// Handle getting hit
bool Player::hit(Time timeHit)
{
    if (m_Invulnerable)
        return false;

    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
    {
        m_LastHit = timeHit;
        if (m_Health > 0)
        {
            m_Health -= 10;
            if (m_Health < 0)
                m_Health = 0;
            return true;
        }
    }
    return false;
}

// Get last hit time
Time Player::getLastHitTime()
{
    return m_LastHit;
}

// Get position
FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

// Get center
Vector2f Player::getCenter()
{
    return m_Position;
}

// Get rotation
float Player::getRotation()
{
    return m_Sprite.getRotation();
}

// Get sprite
Sprite Player::getSprite()
{
    return m_Sprite;
}

// Get health
int Player::getHealth()
{
    return m_Health;
}

// Movement functions
void Player::moveLeft() { m_LeftPressed = true; }
void Player::moveRight() { m_RightPressed = true; }
void Player::moveUp() { m_UpPressed = true; }
void Player::moveDown() { m_DownPressed = true; }

void Player::stopLeft() { m_LeftPressed = false; }
void Player::stopRight() { m_RightPressed = false; }
void Player::stopUp() { m_UpPressed = false; }
void Player::stopDown() { m_DownPressed = false; }

// Update player state
void Player::update(float elapsedTime, Vector2i mousePosition)
{
    // Handle movement
    if (m_UpPressed)
        m_Position.y -= m_Speed * elapsedTime;
    if (m_DownPressed)
        m_Position.y += m_Speed * elapsedTime;
    if (m_LeftPressed)
        m_Position.x -= m_Speed * elapsedTime;
    if (m_RightPressed)
        m_Position.x += m_Speed * elapsedTime;

    m_Sprite.setPosition(m_Position);

    // Keep player within arena
    if (m_Position.x > m_Arena.width - m_TileSize)
        m_Position.x = m_Arena.width - m_TileSize;
    if (m_Position.x < m_Arena.left + m_TileSize)
        m_Position.x = m_Arena.left + m_TileSize;
    if (m_Position.y > m_Arena.height - m_TileSize)
        m_Position.y = m_Arena.height - m_TileSize;
    if (m_Position.y < m_Arena.top + m_TileSize)
        m_Position.y = m_Arena.top + m_TileSize;

    m_Sprite.setPosition(m_Position);

    // Calculate rotation towards mouse
    float angle = (atan2(
        static_cast<float>(mousePosition.y) - (m_Resolution.y / 2.f),
        static_cast<float>(mousePosition.x) - (m_Resolution.x / 2.f)
    ) * 180.f) / 3.14159265358979323846f;

    m_Sprite.setRotation(angle);

    // Update ability
    updateAbility();
}

// Upgrades
void Player::upgradeSpeed()
{
    m_Speed += (START_SPEED * 0.2f); // 20% speed increase
}

void Player::upgradeHealth()
{
    m_MaxHealth += static_cast<int>(START_HEALTH * 0.2f); // 20% max health increase
}

void Player::increaseHealthLevel(int amount)
{
    m_Health += amount;
    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
}

// Ability management
void Player::setAbility(std::unique_ptr<Abilities> ability)
{
    m_Ability = std::move(ability);
}

void Player::useAbility()
{
    if (m_Ability)
        m_Ability->useAbility();
}

void Player::updateAbility()
{
    if (m_Ability)
        m_Ability->update();
}

// Ability-related setters
void Player::switchToMelee()
{
    // Change texture to melee (ensure "zachMelee.png" exists)
    m_Texture = TextureHolder::GetTexture("graphics/zachMelee.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(m_Texture.getSize().x / 2.f, m_Texture.getSize().y / 2.f);
}

void Player::switchToGun()
{
    // Change texture back to gun (ensure "zachIdle.png" exists)
    m_Texture = TextureHolder::GetTexture("graphics/zachIdle.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(m_Texture.getSize().x / 2.f, m_Texture.getSize().y / 2.f);
}

void Player::setInvulnerable(bool invuln)
{
    m_Invulnerable = invuln;
}

void Player::setFireRateMultiplier(float multiplier)
{
    m_FireRateMultiplier = multiplier;
    // Adjust fire rate accordingly in your shooting logic
}

void Player::setInfiniteAmmo(bool infinite)
{
    m_InfiniteAmmo = infinite;
    // Adjust ammo logic accordingly in your shooting system
}

void Player::setEnemiesIgnore(bool ignore)
{
    m_EnemiesIgnore = ignore;
    // Implement logic in enemy AI to respect this flag
}

void Player::setCanAttack(bool canAttack)
{
    m_CanAttack = canAttack;
    // Implement logic in shooting/attack system to respect this flag
}
