#include "Weapon.h"
#include "Character.h"

// Constructeur avec param�tres
Weapon::Weapon(const string& textureFile, Vector2f startPosition, string na, bool gun)
    : weaponName(na), isGun(gun) {

    // Chargement de la texture et configuration du sprite
    if (!texture.loadFromFile(textureFile)) {
        throw runtime_error("Failed to load texture: " + textureFile);
    }

    sprite.setTexture(texture);
    sprite.setOrigin(30, 30);

    frameSpr = { 0, 0, 60, 60 };
    sprite.setTextureRect(frameSpr);

    setPosition(startPosition);
    sprite.setPosition(getPosition());
}

// Constructeur par d�faut
Weapon::Weapon()
    : weaponName("null") {}

// M�thode pour dessiner l'arme
void Weapon::Draw(RenderWindow& window) {
    window.draw(sprite);
}

// M�thode pour cacher l'arme
void Weapon::HideIt() {
    // D�place l'arme en dehors de la vue pour la cacher
    sprite.setPosition(1000, 1000);
}
