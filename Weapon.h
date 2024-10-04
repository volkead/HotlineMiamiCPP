#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;
class Weapon
{
	Texture texWeapon;
	Sprite sprWeapon;
	bool isPickedUp = false;
	bool isAttacking = false;

public:
	Weapon(Texture tex);

};

