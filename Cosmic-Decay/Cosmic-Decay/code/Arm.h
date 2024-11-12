#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Arm {
public:
    // Constructor
    Arm();

    // Get the global bounds of the arm
    FloatRect getPosition();

    // Set the position of the arm (based on player position)
    void setPosition(Vector2f position);

    // Method to set the rotation of the arm
    void setRotation(float angle);

    // Method to get the sprite of the arm
    sf::Sprite& getSprite();

    // Rotate the arm towards the mouse position
    void rotateTowardsMouse(Vector2f playerPosition, RenderWindow& window);

    // Draw the arm
    void draw(RenderWindow& window);

private:
    Sprite m_Sprite; // Arm sprite
};