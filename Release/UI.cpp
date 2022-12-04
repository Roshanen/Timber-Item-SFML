#include "UI.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void UI::draw_UI() {
	font.loadFromFile("./Font/04B_30__.TTF");

	healthTexture.loadFromFile("./Sprite/Life.png");
	healthSprite.setTexture(healthTexture);
	healthText.setFont(font);

	scoreTexture.loadFromFile("./Sprite/Score.png");
	scoreSprite.setTexture(scoreTexture);
	scoreText.setFont(font);

	jumpTexture.loadFromFile("./Sprite/Jump.png");
	jumpSprite.setTexture(jumpTexture);
	jumpText.setFont(font);

	bulwarkTexture.loadFromFile("./Sprite/Bulwark.png");
	bulwarkSprite.setTexture(bulwarkTexture);
	bulwarkText.setFont(font);

	bulletTexture.loadFromFile("./Sprite/Bulletbar.png");
	bulletSprite.setTexture(bulletTexture);
	bulletText.setFont(font);
}
void UI::health_bar(int hp) {
	String string_health = std::to_string(hp);
	healthSprite.setPosition(-0, -32);
	healthText.setString(string_health);
	healthText.setPosition(32 +2, -32 + 6);
	healthText.setCharacterSize(16);
}
void UI::score_bar(int score) {
	String string_score = std::to_string(score);
	scoreSprite.setPosition(64, -32);
	scoreText.setString(string_score);
	scoreText.setPosition(96 + 2, -32 + 6);
	scoreText.setCharacterSize(16);
}
void UI::jump_bar(int jump, int move) {
	String string_jump = std::to_string(jump);
	jumpSprite.setPosition(192, -32);
	jumpText.setString(string_jump);
	jumpText.setPosition(224 + 2, -32 + 6);
	jumpText.setCharacterSize(16);
	jumpText.setOutlineThickness(1);
	if (move != 1) {
		jumpSprite.setTextureRect(IntRect(0, 0, 64, 32));
		jumpText.setOutlineColor(Color(221, 150, 93));
	}
	else if (move == 1) {
		jumpSprite.setTextureRect(IntRect(64, 0, 64, 32));
		jumpText.setOutlineColor(Color(255, 196, 47));
	}
}
void UI::bulwark_bar(int cd, int move) {
	String string_cd = std::to_string(cd);
	bulwarkSprite.setPosition(256, -32);
	bulwarkText.setString(string_cd);
	bulwarkText.setPosition(288 + 2, -32 + 6);
	bulwarkText.setCharacterSize(16);
	bulwarkText.setOutlineThickness(1);
	if (move != 2) {
	bulwarkSprite.setTextureRect(IntRect(0, 0, 64, 32));
	bulwarkText.setOutlineColor(Color(221, 150, 93));
	}
	else if (move == 2) {
		bulwarkSprite.setTextureRect(IntRect(64, 0, 64, 32));
		bulwarkText.setOutlineColor(Color(255, 196, 47));
	}
}
void UI::bullet_bar(int available, int move) {
	String string_available = std::to_string(available);
	bulletSprite.setPosition(320,-32);
	bulletText.setString(string_available);
	bulletText.setPosition(352 + 2, -32 + 6);
	bulletText.setCharacterSize(16);
	bulletText.setOutlineThickness(1);
	if (move != 3) {
		bulletSprite.setTextureRect(IntRect(0, 0, 64, 32));
		bulletText.setOutlineColor(Color(221, 150, 93));
	}
	else if (move == 3) {
		bulletSprite.setTextureRect(IntRect(64, 0, 64, 32));
		bulletText.setOutlineColor(Color(255, 196, 47));
	}
}