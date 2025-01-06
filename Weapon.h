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
    bool isPickedUp = false; // Indique si l'arme est ramass�e

public:
    Sprite sprite;          // Sprite de l'arme
    String weaponName;      // Nom de l'arme
    bool isGun;             // Indique si c'est une arme � feu
    sf::Vector2f velocity;  // V�locit� de l'arme l�ch�e

    // Constructeurs
    Weapon(const string& textureFile, Vector2f startPosition, string na, bool gun);
    Weapon();

    // M�thode pour mettre � jour la v�locit� et la position de l'arme l�ch�e
    void Update(float deltaTime) {
        // R�duire progressivement la v�locit� de l'arme en vu du drop 

        velocity *= 0.95f; // Facteur de r�duction (� ajuster si n�cessaire)

        // Arr�ter le mouvement si la vitesse est inf�rieure � un seuil
        if (std::abs(velocity.x) < 0.1f && std::abs(velocity.y) < 0.1f) {
            velocity = sf::Vector2f(0.f, 0.f);
        }

        // Mise � jour de la position de l'arme
        setPosition(getPosition() + velocity * deltaTime);
    }

    // M�thodes de classe
    void HideIt();
    void Draw(RenderWindow& window);

    // M�thode virtuelle pure pour l'attaque
    virtual void Attack(Character* enemyToAttack) = 0;
};

#endif // WEAPON_H
