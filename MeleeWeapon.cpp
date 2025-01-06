#include "MeleeWeapon.h"
#include "Character.h"
#include <iostream>

MeleeWeapon::MeleeWeapon(const string& textureFile, Vector2f startPosition, string na)
    : Weapon(textureFile, startPosition, na, false) {}

void MeleeWeapon::Attack(Character* enemyToAttack) {
    if (enemyToAttack != nullptr) {
        // Logique d'attaque pour une arme blanche
        std::cout << "Attaque corps à corps sur l'ennemi avec l'arme " << weaponName.toAnsiString() << std::endl;

        // Code pour appliquer les dégâts ou autres effets à enemyToAttack
        enemyToAttack->KnockOut(enemyToAttack);
    }
}
