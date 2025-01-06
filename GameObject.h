#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class GameObject
{
protected:
    Sprite _sprite;       // Sprite du GameObject
    Texture _texture;     // Texture du GameObject
    string _id;           // Identifiant du GameObject

public:
    // Constructeur
    GameObject(const string& textureFile, const string& id)
        : _id(id)
    {
        InitTexture(textureFile); // Initialiser la texture lors de la création de l'objet
    }

    // Initialiser la texture à partir d'un fichier
    void InitTexture(const string& textureFile) {
        if (!_texture.loadFromFile(textureFile)) {
            throw runtime_error("Failed to load texture: " + textureFile);
        }
        _sprite.setTexture(_texture);
    }

    // Obtenir le sprite
    Sprite GetSprite() const {
        return _sprite;
    }

    // Méthode de mise à jour (vide par défaut, à redéfinir dans les sous-classes)
    virtual void Update() {
        // Logique de mise à jour par défaut
    }

    // Opérateur d'égalité
    bool operator==(const GameObject& other) const {
        return _id == other._id; // Compare les identifiants
    }
};

#endif // GAMEOBJECT_H
