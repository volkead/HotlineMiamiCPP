#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player(const std::string& textureFile, sf::Vector2f startPosition, int startHealth, float moveSpeed)
    //: Character(textureFile, startPosition, startHealth, moveSpeed), isAttacking(false), attackCooldown(0.5f) 
{
    // Load texture and set up sprite
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load texture: " + textureFile);
    }

    sprite.setOrigin(32, 32);
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
    frameSpr = { 0,0,64,64 };

    speed = moveSpeed;
    sprite.setTextureRect(frameSpr);
    cout << "Sprite generated, image : " + textureFile + " at " << startPosition.x << "," << startPosition.y;
}



void Player::attack() {
    if (attackClock.getElapsedTime().asSeconds() > attackCooldown)
    {
        isAttacking = true;
        attackClock.restart();
        // Logique d'attaque du joueur
    }
}

