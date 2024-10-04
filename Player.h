#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character 
{
private:
    bool isAttacking = false;
    float attackCooldown;
    sf::Clock attackClock;

public:
    Player(const std::string& textureFile, sf::Vector2f startPosition, int startHealth, float moveSpeed);

    void attack() override; // Surcharge de la méthode d'attaque
};

#endif // PLAYER_H
