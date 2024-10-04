#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Audio.hpp> 
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>;
using namespace std;
using namespace sf;


class Character {
protected:
    sf::Event event;

    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;
    int health;
    sf::Texture texture;

    sf::IntRect frameSpr;

public:

    sf::Vector2f direction;

    //Character(const std::string& textureFile, sf::Vector2f startPosition, int startHealth, float moveSpeed);
    //virtual ~Character() = default;

    virtual void Move(Time deltaTime);
    virtual void attack() = 0;
    void takeDamage(int amount);
    bool isDead() ;

    void setPosition(sf::Vector2f newPosition);
    sf::Vector2f getPosition() ;

    sf::Sprite getSprite() ;

    void SetRotation(float angle);
    

    //void update(float deltaTime);
};

#endif // CHARACTER_H
