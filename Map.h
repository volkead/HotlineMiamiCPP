#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Map
{
private:
    Texture _bgTexture; // Texture pour l'arrière-plan
    Texture _wallsTexture; // Texture pour les murs
    Texture _propsTexture; // Texture pour les murs

    Image _mask;        // Image du masque



public:
    Map(const string& bgTextureFile, const string& wallsTextureFile, const string& propsTextureFile, const string& maskFile);

    Sprite _background; // Sprite pour l'arrière-plan
    Sprite _walls;      // Sprite pour les murs
    Sprite _props;
    
    void InitTextures();
    void Draw(RenderWindow& window, int layer);
    const Image& GetMask() const;
};

#endif // MAP_H
