#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class itemClass
{
public:
	bool state = 1;
	int x = 0;
	int y = 0;
	char ch = 'I';
	int choice = 0;
	int choice2 = 0;
	int choice3 = 0;
	char wchoice[50]{};
	char wchoice2[50]{};
	char wchoice3[50]{};
	int currentSelect = 0;

	Texture itemTexture;
	Sprite itemSprite;
	Texture plateTexture;
	Sprite plateSprite;

	Font font;

	Text header;
	Text item0;
	Text item1;
	Text item2;

	void draw_item();
	void plate_display(int,char*,char*,char*);
};
