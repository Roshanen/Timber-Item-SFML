#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class UI
{
public:
	Font font;

	Texture healthTexture;
	Sprite healthSprite;
	Text healthText;

	Texture scoreTexture;
	Sprite scoreSprite;
	Text scoreText;

	Texture jumpTexture;
	Sprite jumpSprite;
	Text jumpText;

	Texture bulwarkTexture;
	Sprite bulwarkSprite;
	Text bulwarkText;

	Texture bulletTexture;
	Sprite bulletSprite;
	Text bulletText;

	void draw_UI();
	void health_bar(int);
	void score_bar(int);
	void jump_bar(int, int);
	void bulwark_bar(int, int);
	void bullet_bar(int, int);
};

