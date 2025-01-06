#include "Projectile.h"

Projectile::Projectile(Vector2f startPosition, Vector2f direction, float speed) {
    shape.setRadius(5.0f);  // Taille du projectile
    shape.setFillColor(Color::Red);
    shape.setPosition(startPosition);
    velocity = direction * speed;
}

void Projectile::update(Time deltaTime) {
    shape.move(velocity * deltaTime.asSeconds());
}

void Projectile::draw(RenderWindow& window) {
    window.draw(shape);
}

FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
}
