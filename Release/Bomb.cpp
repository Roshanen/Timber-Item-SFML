#include "Bomb.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void bombClass::draw_bomb() {
	bombTexture.loadFromFile("./Sprite/Bomb.png");
	bombExplodeTexture.loadFromFile("./Sprite/BombExplode.png");
	bombSprite.setTexture(bombTexture);
	this->bombSprite.setTextureRect(IntRect(currentTexture, 0, 32, 32));
}
void bombClass::spawn_bomb() {
	bombState = 1;
	bombTimer = 2;
	bombSprite.setTexture(bombTexture);
	bombSprite.setColor(Color(255, 255, 255, 255));
	bombSprite.setPosition(this->x * 32, this->y * 32);
}
void bombClass::turn_bomb() {
	if (bombState == 1) {
		bombSprite.setPosition(this->x * 32, this->y * 32);
		bombTimer--;
		if (bombTimer <= 0) {
			boom = 1;
			explode();
		}
	}
}
void bombClass::explode() {
	bombSprite.setTexture(bombExplodeTexture);
	currentTexture = 0;
	while (currentTexture < 128) {
		this->currentTexture = (currentTexture + 32);
		this->bombSprite.setTextureRect(IntRect(currentTexture, 0, 32, 32));
	}
	bombState = 0;
}
void bombClass::animation(double deltaTime) {
	bombSprite.setPosition(this->x * 32, this->y * 32);
	this->totalTime += deltaTime;
	if (totalTime >= switchTime) {
		this->currentTexture = (currentTexture + 32) % 256;
		this->bombSprite.setTextureRect(IntRect(currentTexture, 0, 32, 32));
		this->totalTime = 0;
	}
}