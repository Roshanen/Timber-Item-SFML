#include "Enemy.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void enemyClass::init_enemy(double setRandom) {
	enemyTexture[0].loadFromFile("./Sprite/SETenemy0.png");
	enemyTexture[1].loadFromFile("./Sprite/SETenemy1.png");
	enemyTexture[2].loadFromFile("./Sprite/SETenemy2.png");
	enemyTexture[3].loadFromFile("./Sprite/SETenemy3.png");
	enemyTexture[4].loadFromFile("./Sprite/SETenemy4.png");
	for (int i = 0; i < 5; i++) {
		if (this->type == i) {
			enemySprite.setTexture(enemyTexture[i]);
			break;
		}
	}
	this->enemySprite.setTextureRect(IntRect(currentTexture, 0, 32, 32));

	this->totalTime = setRandom;
}
void enemyClass::draw_enemy(RenderWindow* window) {
	this->enemySprite.setPosition(32 * x, 32 * y);

	String hpString = std::to_string(hp);
	font.loadFromFile("./Font/arial.ttf");
	this->hpText.setFont(font);
	this->hpText.setCharacterSize(5);
	this->hpText.setPosition(4 + 32 * x, 10 + 32 * y);
	this->hpText.setString(hpString);
}
bool enemyClass::move_enemy(RenderWindow* window, double deltaTime) {
	Vector2f enemyPos = enemySprite.getPosition();
	if (this->state == 0) {
		return 1;
	}
	if ((this->x * 32 != enemyPos.x) || (this->y * 32 != enemyPos.y)) {
		totalTimeMove += deltaTime;
		if (totalTimeMove >= switchTimeMove) {
			this->enemySprite.move(this->direction.x * 4, this->direction.y * 4);
			this->hpText.move(this->direction.x * 4, this->direction.y * 4);

			String hpString = std::to_string(hp);
			hpText.setString(hpString);
			hpText.setCharacterSize(5);
			totalTimeMove -= switchTimeMove;
		}
		return 0;
	}
	else {
		return 1;
	}

}
void enemyClass::animation(RenderWindow*, double deltaTime) {
	this->totalTime += deltaTime;
	if (totalTime >= switchTime) {
		this->currentTexture = (currentTexture + 32) % 256;
		this->enemySprite.setColor(Color(255, 255, 255, 255));
		this->enemySprite.setTextureRect(IntRect(currentTexture, 0, 32, 32));
		this->totalTime = 0;
	}
}