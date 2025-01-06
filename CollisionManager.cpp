#include "CollisionManager.h"
#include <algorithm> // pour std::remove

CollisionManager::CollisionManager() {
    weapons.clear();
    enemies.clear();
}

// Ajoute une arme à la liste
void CollisionManager::addWeapon(Weapon* weapon) {
    if (weapon != nullptr) {
        weapons.push_back(weapon);
    }
}

// Ajoute un ennemi à la liste
void CollisionManager::addEnemy(Character* enemy) {
    if (enemy != nullptr) {
        enemies.push_back(enemy);
    }
}

// Vérifie les collisions entre le joueur et les armes
Weapon* CollisionManager::checkWeaponCollisions(const Character& player) const {
    for (Weapon* weapon : weapons) {
        if (weapon && player.collider.getGlobalBounds().intersects(weapon->sprite.getGlobalBounds())) {
            return weapon; // Retourne un pointeur vers l'arme en collision
        }
    }
    return nullptr;
}

// Vérifie les collisions entre le joueur et les ennemis
Character* CollisionManager::checkEnemyCollisions(const Character& player) const {
    for (Character* enemy : enemies) {
        if (enemy && player.collider.getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds()) && !enemy->isDead()) {
            return enemy; // Retourne un pointeur vers l'ennemi en collision
        }
    }
    return nullptr;
}

// Supprime une arme de la liste
void CollisionManager::removeWeapon(Weapon* weapon) {
    weapons.erase(std::remove(weapons.begin(), weapons.end(), weapon), weapons.end());
}

// Supprime un ennemi de la liste
void CollisionManager::removeEnemy(Character* enemy) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}
