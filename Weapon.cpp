#include "Weapon.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath>

Weapon::Weapon(Texture tex)
{
	texWeapon = tex;
	if (!texWeapon.loadFromFile("Ressource/SpritesSheets/SS_Player_Walk.png"))
	{
		Window win;
	}
	sprWeapon.setTexture(texWeapon);

}
