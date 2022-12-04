#include "Board.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void boardClass::draw_table()
{
	this->boardTexture.loadFromFile("./Sprite/board.png");
	this->boardSprite.setTexture(boardTexture);
	this->boardSprite.setPosition(0, 0);	//80 60

	this->lavaTexture.loadFromFile("./Sprite/lava.png");

	for (int i = 0; i < 10; i++) {
		this->lavaSprite[i].setTexture(lavaTexture);
		this->lavaSprite[i].setPosition(32 * lava[i].x, 32 * lava[i].y);
	}
};