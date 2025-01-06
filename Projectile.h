#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Projectile {
public:
    Projectile(Vector2f startPosition, Vector2f direction, float speed);
    void update(Time deltaTime);
    void draw(RenderWindow& window);
    FloatRect getBounds() const;

private:
    CircleShape shape;   // Représente le projectile
    Vector2f velocity;   // Vitesse et direction
};
