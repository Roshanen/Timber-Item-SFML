#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class bulletClass
{
public:
	int x = 0;
	int y = 0;
	int direcx = 0;
	int direcy = 0;
	int peaDesx = 0;
	int peaDesy = 0;
	int peaState = 0;
	double speed = 5;
	double totalTime = 0;
	double switchTime = 0.05;
	double peaTotalTime = 0;
	double peaSwitchTime = 0.05;

	Texture bulletTexture;
	Sprite bulletSprite;
	Texture peaBulletTexture;
	Sprite peaBulletSprite;

	void draw_bullet();
	void fire_bullet(int, int, int, int);
	bool bullet_travel(RenderWindow*, double);
	void pea_spawn(int,int);
	void pea_travel(RenderWindow* , int,int,double);
};

