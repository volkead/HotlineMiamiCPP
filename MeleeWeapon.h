#pragma once
#include "Weapon.h"

class MeleeWeapon : public Weapon {
public:
    // Constructeur
    MeleeWeapon(const string& textureFile, Vector2f startPosition, string na);

    // Méthode d'attaque qui prend un pointeur vers un Character
    void Attack(Character* enemyToAttack) override;
};
