#include "Player.h"
#include "TextureHolder.h"
#include <iostream>

Player::Player()
{
    // Associate a texture with the sprite
    m_Sprite = sf::Sprite(TextureHolder::GetTexture(
        "graphics/playerSpriteSheet2.png"));
    m_Sprite.setTextureRect(sf::IntRect{ 50, 100, 50, 50 });
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

    //2019 up and down movement
    if (Keyboard::isKeyPressed(Keyboard::Up) || (joyOnePovY == 100))
    {
        m_UpPressed = true;

    }
    else
    {
        m_UpPressed = false;
    }


    if (Keyboard::isKeyPressed(Keyboard::Down) || (joyOnePovY == -100))
    {
        m_DownPressed = true;

    }
    else
    {
        m_DownPressed = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) || (joyOnePovX == -100))
    {
        m_LeftPressed = true;

    }
    else
    {
        m_LeftPressed = false;
    }


    if (Keyboard::isKeyPressed(Keyboard::Right) || (joyOnePovX == 100))
    {
        m_RightPressed = true;
    }
    else
    {
        m_RightPressed = false;
    }

    return m_JustJumped;
}

void Player::update(float elapsedTime)
{
    if (m_RightPressed) {
        m_Position.x += m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        moveTextureRect(elapsedTime);
    }
    else if (m_LeftPressed) {
        m_Position.x -= m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        moveTextureRect(elapsedTime);
    }
    else if (m_UpPressed) {
        m_Position.y -= m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        moveTextureRect(elapsedTime);
    }
    else if (m_DownPressed) {
        m_Position.y += m_Speed * elapsedTime;
        setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        moveTextureRect(elapsedTime);
    }

    // Update collision boxes
    sf::FloatRect r = getPosition();

    // Feet
    m_Feet.left = r.left + 3;
    m_Feet.top = r.top + r.height - 1;
    m_Feet.width = r.width - 6;
    m_Feet.height = 1;

    // Head
    m_Head.left = r.left + 3;
    m_Head.top = r.top - 1;
    m_Head.width = r.width - 6;
    m_Head.height = 1;

    // Right
    m_Right.left = r.left + r.width - 1;
    m_Right.top = r.top + r.height * .35;
    m_Right.width = 1;
    m_Right.height = r.height * .3;

    // Left
    m_Left.left = r.left + 1;
    m_Left.top = r.top + r.height * .35;
    m_Left.width = 1;
    m_Left.height = r.height * .3;

    // Move the sprite into position
    updateLeftRightHeadFeet();
    m_Sprite.setPosition(m_Position);
}

void Player::moveTextureRect(float timeElapsed)
{
    // if the animation counter is greater than the animation limit reset to 0
    if (ani_counter == animation_it_limit - 1)
    {
        ani_counter = 0;
    }

    if (horizontal) {
        // Move the texture rectangle horizontally
        m_Sprite.setTextureRect(sf::IntRect(
            sheetCoordinate.x + ani_counter * spriteSize.x,
            sheetCoordinate.y,
            spriteSize.x,
            spriteSize.y
        ));
    }
    else {
        // Move the texture rectangle vertically
        m_Sprite.setTextureRect(sf::IntRect(
            sheetCoordinate.x,
            sheetCoordinate.y + ani_counter * spriteSize.y,
            spriteSize.x,
            spriteSize.y
        ));
    }

    //increment animation counter to point to the next frame
    double timePerFrame;
    timePerFrame = 1.0 / 5.0;
    animationTimer = animationTimer + timeElapsed;
    if (animationTimer > timePerFrame)
    {
        ani_counter++;
        animationTimer = 0;
    }

    cout << "Animation Counter: " << ani_counter << std::endl;
    cout << "Current Texture Rect: " << m_Sprite.getTextureRect().left << ", " << m_Sprite.getTextureRect().top << std::endl;
}

FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
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
