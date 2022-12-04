#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class bombClass
{
public:
	Texture bombTexture;
	Texture bombExplodeTexture;
	Sprite bombSprite;

	bool bombState = 0;
	bool boom = 0;
	int boomState = 0;
	int bombTimer = 0;
	int x = 0;
	int y = 0;
	char ch = 'B';

	void draw_bomb();
	void spawn_bomb();
	void turn_bomb();
	void explode();
	void animation(double);
private:
	double totalTime = 0;
	double switchTime = 0.3;
	double totalTimeE = 0;
	double switchTimeE = 0.3;
	int currentTexture = 0;
};

