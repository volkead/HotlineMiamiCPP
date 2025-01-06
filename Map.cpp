#include "Map.h"

// Constructeur
Map::Map(const string& bgTextureFile, const string& wallsTextureFile, const string& propsTextureFile, const string& maskFile)
{
    // Chargement des textures
    if (!_bgTexture.loadFromFile(bgTextureFile))
    {
        throw runtime_error("Could not load background texture from " + bgTextureFile);
    }
    if (!_wallsTexture.loadFromFile(wallsTextureFile))
    {
        throw runtime_error("Could not load walls texture from " + wallsTextureFile);
    }
    if (!_mask.loadFromFile(maskFile))
    {
        throw runtime_error("Could not load mask image from " + maskFile);
    }
    if (!_propsTexture.loadFromFile(propsTextureFile))
    {
        throw runtime_error("Could not load mask image from " + propsTextureFile);
    }

    // Initialisation des sprites
    _background.setTexture(_bgTexture);
    _walls.setTexture(_wallsTexture);
    _props.setTexture(_propsTexture);
}

// Méthode pour dessiner la carte
void Map::Draw(RenderWindow& window, int layer)
{
    switch (layer)
    {case 0:
        window.draw(_background);
        break;
    case 1:
        window.draw(_props);
        break;
    case 2:
        window.draw(_walls);
        break;
    default:
        window.draw(_background);
        window.draw(_props);
        window.draw(_walls);

        break;
    }
}

// Accesseur pour le masque
const Image& Map::GetMask() const
{
    return _mask;
}
