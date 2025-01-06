#pragma once
#include "Weapon.h"
#include "Projectile.h"
#include <vector>

class FirearmWeapon : public Weapon {
public:
    FirearmWeapon(const string& textureFile, Vector2f startPosition, string na);
    
    void Attack(Character* enemyToAttack) override;
    void updateProjectiles(Time deltaTime);
    void drawProjectiles(RenderWindow& window);

private:
    std::vector<Projectile> projectiles;  // Liste des projectiles
    float projectileSpeed = 300.0f;        // Vitesse des projectiles
};
