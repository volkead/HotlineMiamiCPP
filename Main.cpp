#include <SFML/Audio.hpp> 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

#include <cmath>  // Pour atan2 et radian à degré
#include <iostream>

using namespace sf;
using namespace std;

Clock deltaClock;

// Fonction pour convertir des radians en degrés
float radToDeg(float radian) 
{
    return radian * 180.f / 3.14159f;
}

// Fonction pour normaliser un vecteur
Vector2f Normalize(Vector2f vecToNormalize) 
{
    Vector2f dir;
    float length = std::sqrt(vecToNormalize.x * vecToNormalize.x + vecToNormalize.y * vecToNormalize.y);
    if (length != 0) 
    {
        dir.x = vecToNormalize.x / length;
        dir.y = vecToNormalize.y / length;
        return dir;
    }
    return Vector2f(0, 0);
}

Vector2f Lerp(Vector2f a, Vector2f b, float s)
{
    // Interpolation linéaire sur les composants x et y du vecteur
    Vector2f result;
    result.x = a.x + s * (b.x - a.x);
    result.y = a.y + s * (b.y - a.y);
    return result;
}

int main()
{
    RenderWindow window(VideoMode(960, 540), "Hotline Miami", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    Clock animationTimer;
    animationTimer.restart();

    ////////// CAMERA //////////
    View gameView;
    const float zoom = 4;
    gameView.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));
    gameView.setSize(window.getSize().x / zoom, window.getSize().y / zoom);
    window.setView(gameView);

    // Load textures
    Texture texCursor, texMap;
    if (!texCursor.loadFromFile("Ressource/SpritesSheets/SS_Cursor.png") ||
        !texMap.loadFromFile("Ressource/SpritesSheets/Bg_Map2.png")) {
        return EXIT_FAILURE;
    }

    // Load map mask as Image
    Image texMapMask;
    if (!texMapMask.loadFromFile("Ressource/SpritesSheets/Bg_Map1_Mask.png")) {
        return EXIT_FAILURE;
    }

    // Initialize cursor sprite
    Sprite sprCursor(texCursor), sprMap(texMap);
    sprCursor.setOrigin(7.5, 7.5);
    IntRect frameSprCursor(0, 0, 15, 15);
    sprCursor.setTextureRect(frameSprCursor);

    // Initialize the player
    Player player("Ressource/SpritesSheets/SS_Player_Walk.png", { 450.f, 380.f }, 100, 200);

    // Game states
    Vector2i mousePosition;
    bool isBlocked = false;

    // Start the game loop
    while (window.isOpen())
    {
        //Time dt = deltaClock.restart();
        Time deltaTime = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                mousePosition = sf::Mouse::getPosition(window);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    player.attack();  // Lancer l'attaque du joueur
                }
            }

            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::S) player.direction.y = (event.type == sf::Event::KeyPressed) ? 1 : 0;
                if (event.key.code == sf::Keyboard::Z) player.direction.y = (event.type == sf::Event::KeyPressed) ? -1 : 0;
                if (event.key.code == sf::Keyboard::D) player.direction.x = (event.type == sf::Event::KeyPressed) ? 1 : 0;
                if (event.key.code == sf::Keyboard::Q) player.direction.x = (event.type == sf::Event::KeyPressed) ? -1 : 0;
            }
        }

        // Positionnement du curseur en fonction de la souris
        sprCursor.setPosition(gameView.getCenter().x + (mousePosition.x - (window.getSize().x) / 2.0) / zoom,
            gameView.getCenter().y + (mousePosition.y - (window.getSize().y) / 2.0) / zoom);

        // Calcul du vecteur direction de l'objet vers la souris
        sf::Vector2f direction = sprCursor.getPosition() - player.getPosition();
        sf::Vector2f dirNorm = Normalize(direction);

        // Calcul de l'angle en radians et conversion en degrés
        float angleRad = std::atan2(direction.y, direction.x);
        float angleDeg = radToDeg(angleRad);

        // Appliquer la rotation du joueur pour qu'il regarde la souris
        player.SetRotation(angleDeg);

        // Mettre à jour le joueur (mouvement, attaque, etc.)
        player.Move(deltaTime);

        // Détection de collision avec le masque de la carte
        int nextPixelColored = texMapMask.getPixel(player.getPosition().x + 10.f * dirNorm.x, player.getPosition().y + 10.f * dirNorm.y).toInteger();
        isBlocked = (nextPixelColored == 255);

        // Mouvement de la caméra en fonction de la position du joueur
        gameView.move(dirNorm.x * 3 - gameView.getCenter().x + player.getPosition().x, dirNorm.y * 3 - gameView.getCenter().y + player.getPosition().y);


        ///////////// ANIMATION CLOCK /////////////
        if (animationTimer.getElapsedTime().asMilliseconds() >= 100) {

            // Animation du curseur
            frameSprCursor.left = (frameSprCursor.left + 15) % 180;  // Boucle à travers les frames du curseur
            sprCursor.setTextureRect(frameSprCursor);
            animationTimer.restart();
        }

        // Effacement de l'écran
        window.clear();
        window.setView(gameView);

        // Dessin des sprites
        window.draw(sprMap);
        window.draw(player.getSprite());
        window.draw(sprCursor);

        // Mise à jour de la fenêtre
        window.display();
    }

    return EXIT_SUCCESS;
}
