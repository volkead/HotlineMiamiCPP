#include "MeleeWeapon.h"
#include "Character.h"
#include <iostream>

MeleeWeapon::MeleeWeapon(const string& textureFile, Vector2f startPosition, string na)
    : Weapon(textureFile, startPosition, na, false) {}

void MeleeWeapon::Attack(Character* enemyToAttack) {
    if (enemyToAttack != nullptr) {
        // Logique d'attaque pour une arme blanche
        std::cout << "Attaque corps � corps sur l'ennemi avec l'arme " << weaponName.toAnsiString() << std::endl;

        // Code pour appliquer les d�g�ts ou autres effets � enemyToAttack
        enemyToAttack->KnockOut(enemyToAttack);
    }
}
