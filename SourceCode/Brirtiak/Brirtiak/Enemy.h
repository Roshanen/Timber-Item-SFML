#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class enemyClass
{
public:
	Vector2i direction;

	bool state = 0;

	int hp = 0;
	int init_hp = 1;
	int move = 1;
	int attack = 1;
	int x = 0;
	int y = 0;
	int atk_ranged = 1;
	int cooldown = 0;
	char ch = 'E';

	int type = 0; //0mush 1ranged 2bomb 3brute 4reaper

	Texture enemyTexture[5];

	Sprite enemySprite;

	Font font;
	Text hpText;

	void init_enemy(double);
	void draw_enemy(RenderWindow*);
	bool move_enemy(RenderWindow*, double);
	void animation(RenderWindow*, double);

private:
	int currentTexture = 0;
	double totalTime = 0;
	double totalTimeMove = 0;
	double switchTime = 0.3;
	double switchTimeMove = 0.01;
};

