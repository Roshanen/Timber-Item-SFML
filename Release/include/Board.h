#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class boardClass {
public:
	Texture boardTexture;
	Sprite boardSprite;
	Texture lavaTexture;
	Sprite lavaSprite[10];
	struct lava{
		int x = 0;
		int y = 0;
		char ch = 'L';
	} lava[10];

	void draw_table();
};

