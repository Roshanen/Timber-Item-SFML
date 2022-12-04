#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class playerClass
{
public:
	Vector2i direction;

	int hp_init = 10;
	int hp = 0;

	int attack = 1;

	int moveType = 0; //0Move 1Jump 2Bulwark 3Fire 4Item

	int jump_init = 2;
	int jump_available = 2;

	int bulwark_cooldown_init = 3;
	int bulwark_cooldown = 0;

	int bullet_init = 1;
	int bullet_available = 1;

	bool enrage = 0;
	int cone_atk = 0;

	int x = 6;
	int y = 8;

	char ch = 'P';

	Texture playerTexture;
	Sprite playerSprite;

	void draw_player(RenderWindow*);
	bool move_player(RenderWindow*, double);
	void animation(RenderWindow*, double);

private:
	int currentTexture = 0;
	double totalTime = 0;
	double totalTimeMove = 0;
	double switchTime = 0.3;
	double switchTimeMove = 0.01;
};

