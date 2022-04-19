#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;

class UNIT
{
private: 
	   int damage;


public:
	int health;
	float currentFrame = 0;
	FloatRect rect;
	Sprite sprite;
	bool life;
	float dx, dy;

};

