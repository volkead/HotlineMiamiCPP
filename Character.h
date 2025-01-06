#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "Weapon.h"

using namespace std;
using namespace sf;

class Character : public Transformable
{
protected:
    // Sprites et position
    Sprite sprite;
    Sprite spriteFoots;
    Vector2f position;

    // États du personnage
    float speed;
    bool dead;
    bool hasWeapon = false;
    bool isAttacking = false;
    bool firstAttack;

    // Animation d'attaque
    const float attackCooldown = 0.2f;
    int attackAnimationFrame = 0;
    int totalAttackFrames = 8;

    // Cône d'attaque
    ConvexShape actionCone;
    float actionRange = 25.0f;
    float coneAngle = 45.0f;

    // Texture et frames
    Texture texture;
    IntRect frameSpr;
    IntRect frameSprFoots;

    // Timers d'animation
    Clock animationClock;
    Clock animationClock2;

    // Range d'animation
    int animationLineWalk = 0;
    int animationLineAttack = 320;

    // Initialisation du cône d'attaque
    void initializeAttackCone();

private:
    // Angles de direction
    float angleRad;
    float angleDeg;

public:
    // Directions et état du personnage
    Vector2f direction;
    bool isBlocked;
    Weapon* weaponToPick = nullptr;  // Pointeur vers une arme à ramasser
    Weapon* equippedWeapon = nullptr; // Arme équipée (copie ou initialisation vide)
    Character* enemyInRange = nullptr; // Ennemie dans la portée

    // Collider
    CircleShape collider;

    // Constructeur
    Character(const string& textureFile, Vector2f startPosition, float moveSpeed, bool deadState);

    // Fonctions de mouvement et d'attaque
    void lookAtTarget(Vector2f target);
    void Move(Time deltaTime);
    void Attack();
    void SecondAction();
    void Pickup(Weapon* weapon);
    void Drop();

    // Gestion de l'état de vie
    void KnockOut(Character* enemy);
    void Kill(Character* enemy);
    bool isDead();

    // Gestion des sprites et affichage
    Sprite getSprite();
    void Draw(RenderWindow& window, int layer);

    // Mise à jour du personnage
    virtual void Update();
};

#endif // CHARACTER_H
