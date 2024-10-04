#include "Character.h"


//Character::Character(const std::string& textureFile, sf::Vector2f startPosition, int startHealth, float moveSpeed)
//    : position(startPosition), health(startHealth), speed(moveSpeed)
//{
//    //// Load texture and set up sprite
//    //if (!texture.loadFromFile(textureFile)) {
//    //    throw std::runtime_error("Failed to load texture: " + textureFile);
//    //}
//    //sprite.setTexture(texture);
//    //sprite.setPosition(startPosition);
//    //frameSpr = { 0,0,64,64 };
//
//    //sprite.setTextureRect(frameSpr);
//    //cout << "Sprite generated, image : " + textureFile + " at " << startPosition.x << "," << startPosition.y;
//}

void Character::Move(Time deltaTime) {
    Vector2f velocity = direction * speed * deltaTime.asSeconds();
    sprite.move(velocity);
}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Character::isDead()  {
    return health <= 0;
}

void Character::setPosition(sf::Vector2f newPosition) {
    position = newPosition;
    sprite.setPosition(position);
}

sf::Vector2f Character::getPosition()  {
    return sprite.getPosition();
}

void Character::SetRotation(float angle)
{
    sprite.setRotation(angle);
}

sf::Sprite Character::getSprite()  {
    return sprite;
}

//void Character::update(float deltaTime) {
//    Move(deltaTime);
//}