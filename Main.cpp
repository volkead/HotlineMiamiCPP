#include <SFML/Audio.hpp> 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Weapon.h"
#include "MeleeWeapon.h"
#include "FirearmWeapon.h"
#include "CollisionManager.h"
#include "Character.h"
#include "Map.h"

#include "GameObject.h"

#include <cmath>  // Pour atan2 et radian à degré
#include <iostream>

// Constantes de configuration
const float ZOOM_LEVEL = 4.4f;
const float SMOOTH_SPEED = 5.f;
const float PLAYER_MOVE_OFFSET = -20.f;
const float AIM_OFFSET = 10.f;

// Utilisation des espaces de noms SFML
using namespace sf;
using namespace std;

// Fonction pour convertir des radians en degrés
float radToDeg(float radian)
{
    return radian * 180.f / 3.14159f;
}

// Fonction pour normaliser un vecteur
Vector2f Normalize(Vector2f vec)
{
    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
    return (length != 0) ? vec / length : Vector2f(0.f, 0.f);
}

// Fonction de Lerp pour interpolation linéaire
Vector2f Lerp(Vector2f a, Vector2f b, float s)
{
    return a + s * (b - a);
}

int main()
{
    // Initialisation de la fenêtre et configuration de la vue de la caméra
    RenderWindow window(VideoMode(960, 540), "Hotline Miami", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    View gameView;
    gameView.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f));
    gameView.setSize(window.getSize().x / ZOOM_LEVEL, window.getSize().y / ZOOM_LEVEL);
    window.setView(gameView);

    Map map_NoTalk("Ressource/Maps/L_No_Talk.png", "Ressource/Maps/L_No_Talk_Walls.png", "Ressource/Maps/L_No_Talk_Props.png", "Ressource/Maps/L_No_Talk_Mask.png");
    Map map_Intro("Ressource/Maps/L_Intro.png", "Ressource/Maps/L_Intro_Walls.png", "Ressource/Maps/L_Intro_Props.png", "Ressource/Maps/L_Intro_Mask.png");


    Map currentMap = map_Intro;

    // Chargement des textures
    Texture texCursor, texVHS, texAura;
    if (!texCursor.loadFromFile("Ressource/SpritesSheets/SS_Cursor.png") ||
        !texVHS.loadFromFile("Ressource/SpritesSheets/VHS.png") ||
        !texAura.loadFromFile("Ressource/SpritesSheets/Character_Aura.png"))
    {
        return EXIT_FAILURE;
    }

    Image texMapMask;
    if (!texMapMask.loadFromFile("Ressource/Maps/L_No_Talk_Mask.png"))
    {
        return EXIT_FAILURE;
    }

    RectangleShape background({ 2048,2048 });
    background.setOrigin(1024, 1024);
    Color color(0, 0, 0);
    background.setFillColor(color);
    background.setPosition(gameView.getCenter());

    // Initialisation des sprites
    Sprite sprCursor(texCursor), sprVHS(texVHS), sprAura(texAura);
    sprCursor.setOrigin(7.5, 7.5);
    sprAura.setOrigin(128, 128);
    sprVHS.setOrigin(1024, 1024);
    sprVHS.setPosition(gameView.getCenter());

    background.setPosition(gameView.getCenter());
    IntRect frameSprCursor(0, 0, 15, 15);
    sprCursor.setTextureRect(frameSprCursor);

    // Création du joueur et des armes
    Character player("Ressource/SpritesSheets/SS_Player_Walk.png", { 50.f, 50.f }, 150, false);
    
    CollisionManager collision;



    // Déclarations pour les boucles de temps et les états de jeu
    Clock deltaClock, animationTimer, cameraSmoothClock, baseClock;
    animationTimer.restart();
    baseClock.restart();
    Vector2i mousePosition;

    //currentClock.restart();

    // Boucle de jeu principale
    while (window.isOpen())
    {
        Time deltaTime = deltaClock.restart();

        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved)
            {
                mousePosition = sf::Mouse::getPosition(window);
            }

            // Gestion des clics de souris et des touches du clavier
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    player.Attack();
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    player.SecondAction();
                }
            }

            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
            {
                bool keyPressed = (event.type == sf::Event::KeyPressed);
                if (event.key.code == sf::Keyboard::S)
                {
                    player.direction.y = keyPressed ? 1 : 0;
                }
                if (event.key.code == sf::Keyboard::Z)
                {
                    player.direction.y = keyPressed ? -1 : 0;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    player.direction.x = keyPressed ? 1 : 0;
                }
                if (event.key.code == sf::Keyboard::Q)
                {
                    player.direction.x = keyPressed ? -1 : 0;
                }
            }
        }

        // Mise à jour du joueur et gestion des collisions
        int nextPixelColored = currentMap.GetMask().getPixel(player.getPosition().x + 10.f * Normalize(player.direction).x, player.getPosition().y + 10.f * Normalize(player.direction).y).toInteger();
        player.isBlocked = (nextPixelColored == 255);

        if (nextPixelColored == -16776961)
        {
            //Load nextLevel, à l'avenir faire une fonction Load(Map mapToLoad) et ajouter les information de création de character dans la classe Map plutôt que dans le main.

            //nettoyage entités présentes
            for (size_t i = 0; i < collision.weapons.size(); i++) {
                delete collision.weapons.at(i);
            }

            for (size_t i = 0; i < collision.enemies.size(); i++) {
                delete collision.enemies.at(i);
            }

            currentMap = map_NoTalk;
            Character* enemy1 = new Character("Ressource/SpritesSheets/SS_Enemy_Walk.png", { 390.f, 300.f }, 200, false);
            Character* enemy2 = new Character("Ressource/SpritesSheets/SS_Enemy_Walk.png", { 150.f, 250.f }, 200, false);
            Character* enemy3 = new Character("Ressource/SpritesSheets/SS_Enemy_Walk.png", { 250.f, 220.f }, 200, false);
            Character* enemy4 = new Character("Ressource/SpritesSheets/SS_Enemy_Walk.png", { 50.f, 110 }, 200, false);
            Character* enemy5 = new Character("Ressource/SpritesSheets/SS_Enemy_Walk.png", { 130.f, 360 }, 200, false);
            Character* enemy6 = new Character("Ressource/SpritesSheets/SS_Enemy_Walk.png", { 450.f, 150.f }, 200, false);


            Weapon* weapon1 = new FirearmWeapon("Ressource/HotlineMiamiSpritesSheets/Sprites/Items/Weapons/sprWeapons_0.png", { 500.f, 380.f }, "ak");
            Weapon* weapon2 = new MeleeWeapon("Ressource/HotlineMiamiSpritesSheets/Sprites/Items/Weapons/sprWeapons_4.png", { 450.f, 160.f }, "bat");
            Weapon* weapon3 = new MeleeWeapon("Ressource/HotlineMiamiSpritesSheets/Sprites/Items/Weapons/sprWeapons_4.png", { 170.f, 290.f }, "bat");


            collision.addWeapon(weapon1);
            collision.addWeapon(weapon2);
            collision.addWeapon(weapon3);
            collision.addEnemy(enemy1);
            collision.addEnemy(enemy2);
            collision.addEnemy(enemy3);
            collision.addEnemy(enemy4);
            collision.addEnemy(enemy5);
            collision.addEnemy(enemy6);
        }


        Character* collidedEnemy = collision.checkEnemyCollisions(player);
        if (collidedEnemy)
        {
            player.enemyInRange = collidedEnemy;
        }
        else
        {
            player.enemyInRange = nullptr;
        }

        Weapon* collidedWeapon = collision.checkWeaponCollisions(player);

        if (collidedWeapon)
        {
            player.weaponToPick = collidedWeapon;
        }
        else
        {
            player.weaponToPick = nullptr;
        }
        player.Update();
        sprAura.setPosition(player.getPosition());

        if (!player.isBlocked)
        {
            player.Move(deltaTime);

        }

        for (size_t i = 0; i < collision.enemies.size(); i++)
        {
            if (!collision.enemies.at(i)->isDead())
            {
                collision.enemies.at(i)->Update();
                collision.enemies.at(i)->lookAtTarget(player.getPosition());
            }

        }

        // Positionnement du curseur
        sprCursor.setPosition(gameView.getCenter() + (sf::Vector2f(mousePosition) - sf::Vector2f(window.getSize()) / 2.f) / ZOOM_LEVEL);
        //sprCursor.setPosition(player.getPosition().x + (mousePosition.x - (window.getSize().x) / 2) / ZOOM_LEVEL, player.getPosition().y + (mousePosition.y - (window.getSize().y) / 2) / ZOOM_LEVEL);

        // Direction et rotation du joueur vers la position du curseur
        Vector2f aimDirection = Normalize(sprCursor.getPosition() - player.getPosition());
        player.setRotation(radToDeg(atan2(aimDirection.y, aimDirection.x)));

        // Gestion du déplacement et du lissage de la caméra
        Vector2f camTarget = player.getPosition() + player.direction * PLAYER_MOVE_OFFSET + aimDirection * AIM_OFFSET;
        gameView.setCenter(Lerp(gameView.getCenter(), camTarget, SMOOTH_SPEED * cameraSmoothClock.restart().asSeconds()));

        // Animation du curseur
        if (animationTimer.getElapsedTime().asMilliseconds() >= 100)
        {
            frameSprCursor.left = (frameSprCursor.left + 15) % 180;
            sprCursor.setTextureRect(frameSprCursor);
            animationTimer.restart();
        }

        sprVHS.move(0.f, sin(baseClock.getElapsedTime().asSeconds() * 2) * deltaTime.asSeconds() * 2);
        color.b = (sin((2 * 3.14f / 30) * baseClock.getElapsedTime().asSeconds()) + 1) * 127.5 / 2;
        color.g = (sin((2 * 3.14f / 15) * baseClock.getElapsedTime().asSeconds()) + 1) * 127.5 / 2;
        color.r = 127.5 / 2;
        //color.g = 128;
        //color.g = sin(baseClock.getElapsedTime().asSeconds()/ 1 + 1) * 127, 5;
        background.setFillColor(color);

        // Rendu
        window.clear();
        window.setView(gameView);

        window.draw(background);

        currentMap.Draw(window, 0);

        //dessiner weapons
        for (size_t i = 0; i < collision.weapons.size(); i++) {
            collision.weapons.at(i)->Draw(window);
        }

        //dessiner enemy
        for (size_t i = 0; i < collision.enemies.size(); i++) {
            collision.enemies.at(i)->Draw(window, 0);
        }


        //draw player
        player.Draw(window, 1);
        window.draw(sprAura);

        currentMap.Draw(window, 1);
        player.Draw(window, 2);


        currentMap.Draw(window, 2);


        window.draw(sprCursor);
        window.draw(sprVHS);

        window.display();
    }
    for (size_t i = 0; i < collision.weapons.size(); i++) {
        delete collision.weapons.at(i);
    }

    for (size_t i = 0; i < collision.enemies.size(); i++) {
        delete collision.enemies.at(i);
    }

    return EXIT_SUCCESS;
}