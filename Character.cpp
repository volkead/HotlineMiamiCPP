#include "Character.h"

using namespace std;
using namespace sf;

// Constructeur de la classe Character
Character::Character(const string& textureFile, Vector2f startPosition, float moveSpeed, bool deadState)
{
    // Charger la texture et configurer le sprite
    if (!texture.loadFromFile(textureFile))
    {
        throw runtime_error("Failed to load texture: " + textureFile);
    }

    sprite.setTexture(texture);
    sprite.setOrigin(32, 32);
    spriteFoots = sprite;

    // Initialiser les rectangles de texture
    frameSpr = { 0, 0, 64, 64 };
    frameSprFoots = { 192, 0, 64, 64 };

    sprite.setTextureRect(frameSpr);
    spriteFoots.setTextureRect(frameSprFoots);
    setPosition(startPosition);

    // Initialiser les positions du sprite et du collider
    sprite.setPosition(getPosition());
    spriteFoots.setPosition(getPosition());
    collider.setOrigin(8, 8);
    collider.setPosition(getPosition());

    // Initialiser les attributs de position et de vitesse
    position = startPosition;
    speed = moveSpeed;
    dead = deadState;

    collider.setRadius(8);
    animationClock.restart();
    initializeAttackCone();  // Initialiser le cône d'attaque

    cout << "Sprite generated, image : " + textureFile + " at " << getPosition().x << "," << getPosition().y << endl;
}

// Méthodes de mouvement et d'attaque
void Character::Move(Time deltaTime)
{
    Vector2f velocity = direction * speed * deltaTime.asSeconds();
    move(velocity);
}

void Character::Attack()
{
    if (animationClock2.getElapsedTime().asSeconds() > attackCooldown)
    {
        firstAttack = !firstAttack;
        isAttacking = true;
        attackAnimationFrame = 0;
        frameSpr.top = animationLineAttack;

        animationClock2.restart();

        if (enemyInRange && (equippedWeapon == nullptr))
        {
            KnockOut(enemyInRange);
        }
        else if (equippedWeapon != nullptr)
        {
            equippedWeapon->Attack(enemyInRange);
        }
    }
}

// Méthodes de gestion des cibles
void Character::lookAtTarget(Vector2f target)
{
    Vector2f direction = target - getPosition();
    float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2)); // Calculer la distance à la cible

    if (distance < 40) // Vérifie si la cible est assez proche pour attaquer
    {
        Attack();
    }

    // Tourner vers la cible
    float angleRad = atan2(direction.y, direction.x);
    float angleDeg = angleRad * 180.0f / 3.14159f;
    setRotation(angleDeg);
}

void Character::KnockOut(Character* enemyToKO)
{
    enemyToKO->dead = true;
    enemyToKO->frameSpr.top = 128;
    enemyToKO->frameSpr.left = (rand() * 64 + 1) % 192;
    enemyToKO->sprite.setTextureRect(enemyToKO->frameSpr);
}

// Méthodes d'action secondaire
void Character::SecondAction()
{
    if (hasWeapon)
    {
        Drop();
    }
    else
    {
        Pickup(weaponToPick);
    }
}

// Méthodes de gestion des armes
void Character::Pickup(Weapon* weapon)
{
    if (weapon == nullptr)
    {
        cout << "no weapon available";
        return; // Vérifie si l'arme existe
    }

    cout << "picked up : " << weapon->weaponName.toAnsiString() << endl;

    // Ajuster l'animation en fonction du type d'arme
    if (weapon->weaponName == "ak")
    {
        animationLineWalk = 384;
        animationLineAttack = 384 + 64;
        totalAttackFrames = 2;
    }
    else if (weapon->weaponName == "bat")
    {
        animationLineWalk = 512;
        animationLineAttack = 512 + 64;
        totalAttackFrames = 8;
    }

    hasWeapon = true;
    equippedWeapon = weapon;
    frameSpr.top = animationLineWalk;
    weaponToPick = nullptr;

    weapon->HideIt(); // Marque l'arme comme ramassée
}

void Character::Drop()
{
    hasWeapon = false;

    animationLineWalk = 0;
    animationLineAttack = 320;
    totalAttackFrames = 9;
    frameSpr.top = animationLineWalk;

    equippedWeapon->sprite.setPosition(sprite.getPosition());
    equippedWeapon = nullptr;
}

// Méthodes d'état
bool Character::isDead()
{
    return dead;
}

Sprite Character::getSprite()
{
    return sprite;
}

// Méthodes de mise à jour et de dessin
void Character::Update()
{
    sprite.setPosition(getPosition());
    spriteFoots.setPosition(getPosition());
    collider.setPosition(getPosition());

    actionCone.setPosition(getPosition());
    actionCone.setRotation(getRotation());

    sprite.setRotation(getRotation());

    angleRad = atan2(direction.y, direction.x);
    angleDeg = angleRad * 180.f / 3.14159f;

    spriteFoots.setRotation(angleDeg);

    // Mise à jour de l'animation
    if (animationClock.getElapsedTime().asMilliseconds() >= 50)
    {
        if (isAttacking)
        {
            if (attackAnimationFrame < totalAttackFrames)
            {
                frameSpr.left = (attackAnimationFrame * 64) % 512;
                attackAnimationFrame++;

                if (direction.x != 0 || direction.y != 0)
                {
                    frameSprFoots.left = (frameSprFoots.left + 64) % 1024;
                }
                else
                {
                    frameSprFoots.left = 0;
                    frameSprFoots.top = 192;  // État au repos
                }
            }
            else
            {
                attackAnimationFrame = 0;
                isAttacking = false;
                frameSpr.top = animationLineWalk;
            }
        }
        else
        {
            if (direction.x != 0 || direction.y != 0)
            {
                frameSpr.left = (frameSpr.left + 64) % 512;
                frameSprFoots.left = (frameSprFoots.left + 64) % 1024;
            }
            else
            {
                frameSprFoots.left = 0;
                frameSprFoots.top = 192;  // État au repos
            }
        }

        sprite.setTextureRect(frameSpr);
        spriteFoots.setTextureRect(frameSprFoots);
        animationClock.restart();
    }
}

void Character::Draw(RenderWindow& window, int layer)
{
    switch (layer)
    {
    case 1:
        window.draw(spriteFoots);
        break;
    case 2:
        window.draw(sprite);
        break;
    default:
        window.draw(spriteFoots);
        window.draw(sprite);
        break;
    }
}

void Character::initializeAttackCone()
{
    actionCone.setPointCount(3);
    actionCone.setPoint(0, Vector2f(0, 0));
    actionCone.setPoint(1, Vector2f(actionRange, actionRange / tan(coneAngle * 3.14159f / 180.0f)));
    actionCone.setPoint(2, Vector2f(actionRange, -actionRange / tan(coneAngle * 3.14159f / 180.0f)));

    actionCone.setFillColor(Color(255, 0, 0, 100));
}
