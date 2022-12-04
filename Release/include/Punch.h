#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class punchClass
{
public:
	bool punchState = 0;
	int alphaColor = 255;

	Texture punchTexture;
	Sprite punchSprite;

	void draw_punch();
	void punch_animation(int, int, int ,int);
	void punch_update(double);

private:
	double punchTime = 0;
	double punchFadeInterval = 0.3;
};

