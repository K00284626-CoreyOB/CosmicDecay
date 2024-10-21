#include "Player.h"
#include "TextureHolder.h"
#include <iostream>

Player::Player()
{
    // Associate a texture with the sprite
    m_Sprite = sf::Sprite(TextureHolder::GetTexture(
        "graphics/pacman-spritesheet-resized-810-730.png"));
    m_Sprite.setTextureRect(sf::IntRect{ 12, 62, 50, 50 });
}

bool Player::handleInput()
{
    m_JustJumped = false;

    // Joystick input variables
    float joyOnePovY = 0;
    float joyOnePovX = 0;
    bool joyOneConnected = sf::Joystick::isConnected(0);
    if (joyOneConnected) {
        joyOnePovY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
        joyOnePovX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
    }

    // Keyboard and joystick input handling
    m_UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (joyOnePovY == 100);
    m_DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (joyOnePovY == -100);
    m_LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (joyOnePovX == -100);
    m_RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (joyOnePovX == 100);

    return m_JustJumped;
}

void Player::update(float elapsedTime)
{
    if (m_RightPressed) {
        m_Position.x += m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(12, 62, 150, 50));
    }
    else if (m_LeftPressed) {
        m_Position.x -= m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(12, 12, 150, 50));
    }
    else if (m_UpPressed) {
        m_Position.y -= m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(12, 112, 150, 50));
    }
    else if (m_DownPressed) {
        m_Position.y += m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(12, 162, 150, 50));
    }

    // Update collision boxes
    sf::FloatRect r = getPosition();
    m_Feet = { r.left + 3, r.top + r.height - 1, r.width - 6, 1 };
    m_Head = { r.left + 3, r.top - 1, r.width - 6, 1 };
    m_Right = { r.left + r.width - 1, r.top + r.height * .35, 1, r.height * .3 };
    m_Left = { r.left + 1, r.top + r.height * .35, 1, r.height * .3 };

    // Move the sprite into position
    updateLeftRightHeadFeet();
    m_Sprite.setPosition(m_Position);
}

// Ability methods
void Player::switchToMelee() {
    // Logic to switch to melee weapon
    std::cout << "Switched to melee weapon.\n";
}

void Player::switchToGun() {
    // Logic to switch to gun weapon
    std::cout << "Switched to gun weapon.\n";
}

void Player::increaseHealthLevel(int amount) {
    // Logic to increase health level
    std::cout << "Health increased by " << amount << ".\n";
}

void Player::setHealth(float health) {
    // Logic to set health
    std::cout << "Health set to " << health << ".\n";
}

float Player::getMaxHealth() const {
    return m_MaxHealth;
}

void Player::setInvulnerable(bool state) {
    m_Invulnerable = state;
    std::cout << "Invulnerability set to " << (state ? "true" : "false") << ".\n";
}

void Player::setEnemiesIgnore(bool state) {
    m_EnemiesIgnore = state;
    std::cout << "Enemies ignore set to " << (state ? "true" : "false") << ".\n";
}

void Player::setCanAttack(bool state) {
    m_CanAttack = state;
    std::cout << "Can attack set to " << (state ? "true" : "false") << ".\n";
}

void Player::setFireRateMultiplier(float multiplier) {
    m_FireRateMultiplier = multiplier;
    std::cout << "Fire rate multiplier set to " << multiplier << ".\n";
}

void Player::setInfiniteAmmo(bool state) {
    m_InfiniteAmmo = state;
    std::cout << "Infinite ammo set to " << (state ? "true" : "false") << ".\n";
}