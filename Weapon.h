#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Character;

class Weapon : public Transformable {
protected:
    Texture texture;       // Texture de l'arme
    IntRect frameSpr;      // Cadre de la sprite
    bool isPickedUp = false; // Indique si l'arme est ramassée

public:
    Sprite sprite;          // Sprite de l'arme
    String weaponName;      // Nom de l'arme
    bool isGun;             // Indique si c'est une arme à feu
    sf::Vector2f velocity;  // Vélocité de l'arme lâchée

    // Constructeurs
    Weapon(const string& textureFile, Vector2f startPosition, string na, bool gun);
    Weapon();

    // Méthode pour mettre à jour la vélocité et la position de l'arme lâchée
    void Update(float deltaTime) {
        // Réduire progressivement la vélocité de l'arme en vu du drop 

        velocity *= 0.95f; // Facteur de réduction (à ajuster si nécessaire)

        // Arrêter le mouvement si la vitesse est inférieure à un seuil
        if (std::abs(velocity.x) < 0.1f && std::abs(velocity.y) < 0.1f) {
            velocity = sf::Vector2f(0.f, 0.f);
        }

        // Mise à jour de la position de l'arme
        setPosition(getPosition() + velocity * deltaTime);
    }

    // Méthodes de classe
    void HideIt();
    void Draw(RenderWindow& window);

    // Méthode virtuelle pure pour l'attaque
    virtual void Attack(Character* enemyToAttack) = 0;
};

#endif // WEAPON_H
