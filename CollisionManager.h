#pragma once

#include "Weapon.h"
#include "Character.h"
#include <vector>

using namespace sf;
using namespace std;

class CollisionManager {
public:
    CollisionManager();

    // Stockage de pointeurs pour éviter la copie
    vector<Weapon*> weapons; // Liste des armes
    vector<Character*> enemies; // Liste des ennemis

    // Ajoute une arme au registre
    void addWeapon(Weapon* weapon);

    // Ajoute un ennemi au registre
    void addEnemy(Character* enemy);

    // Vérifie les collisions avec les armes et retourne l'arme en collision ou nullptr
    Weapon* checkWeaponCollisions(const Character& player) const;

    // Vérifie les collisions avec les ennemis et retourne l'ennemi en collision ou nullptr
    Character* checkEnemyCollisions(const Character& player) const;

    // Supprime une arme du registre
    void removeWeapon(Weapon* weapon);

    // Supprime un ennemi du registre
    void removeEnemy(Character* enemy);
};
