#include "Weapon.h"
#include "Character.h"

// Constructeur avec paramètres
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

// Constructeur par défaut
Weapon::Weapon()
    : weaponName("null") {}

// Méthode pour dessiner l'arme
void Weapon::Draw(RenderWindow& window) {
    window.draw(sprite);
}

// Méthode pour cacher l'arme
void Weapon::HideIt() {
    // Déplace l'arme en dehors de la vue pour la cacher
    sprite.setPosition(1000, 1000);
}
