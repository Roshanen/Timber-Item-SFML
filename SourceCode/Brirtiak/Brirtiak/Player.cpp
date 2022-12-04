#include "Player.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void playerClass::draw_player(sf::RenderWindow* window) {
	playerTexture.loadFromFile("./Sprite/SETplayer.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(currentTexture, 0, 32, 32));
	playerSprite.setPosition(32 * this->x, 32 * this->y);
}
bool playerClass::move_player(sf::RenderWindow* window, double deltaTime) {
	Vector2f playerPos = playerSprite.getPosition();

	if (this->x * 32 != playerPos.x || this->y * 32 != playerPos.y) {
		totalTimeMove += deltaTime;
		if (totalTimeMove >= switchTimeMove) {
			playerSprite.move(this->direction.x * 4, this->direction.y * 4);
			totalTimeMove -= switchTimeMove;
		}
		//printf("%f %f %d %d\n", (playerPos.x), (playerPos.y), x * 32, y * 32);
		return 0;
	}
	else {
		return 1;
	}
}

void playerClass::animation(RenderWindow* window, double deltaTime) {
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		currentTexture = (currentTexture + 32) % 256;
		playerSprite.setColor(Color(255, 255, 255, 255));
		playerSprite.setTextureRect(IntRect(currentTexture, 0, 32, 32));
		totalTime = 0;
	}
}
