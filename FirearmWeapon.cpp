#include "FirearmWeapon.h"
#include "Character.h"
#include <iostream>

FirearmWeapon::FirearmWeapon(const string& textureFile, Vector2f startPosition, string na)
    : Weapon(textureFile, startPosition, na, true) {}

void FirearmWeapon::Attack(Character* enemyToAttack) {
    if (enemyToAttack) {
        // Crée un projectile partant de la position actuelle de l'arme, en direction de l'ennemi
        //Vector2f direction = enemyToAttack->getSprite().getPosition() - sprite.getPosition();
        //float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        //direction /= length;  // Normalise la direction

        //// Ajoute le projectile à la liste
        //projectiles.emplace_back(sprite.getPosition(), direction, projectileSpeed);

        //std::cout << "Tir d'un projectile vers l'ennemi." << std::endl;
    }
}

void FirearmWeapon::updateProjectiles(Time deltaTime) {
    for (auto& projectile : projectiles) {
        projectile.update(deltaTime);
    }

    // Vérifiez ici les collisions avec les ennemis
    // Supprimez les projectiles qui sortent de l'écran si nécessaire
}

void FirearmWeapon::drawProjectiles(RenderWindow& window) {
    for (auto& projectile : projectiles) {
        projectile.draw(window);
    }
}
