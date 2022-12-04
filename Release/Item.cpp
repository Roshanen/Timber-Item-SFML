#include "Item.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void itemClass::draw_item() {
	itemTexture.loadFromFile("./Sprite/tribute.png");
	itemSprite.setTexture(itemTexture);
	itemSprite.setPosition(32 * x, 32 * y);

	plateTexture.loadFromFile("./Sprite/Itemplate.png");
	plateSprite.setTexture(plateTexture);
	plateSprite.setPosition(64,80);

	font.loadFromFile("./Font/arial.TTF");
	header.setFont(font);
	header.setString("Choose Item");
	header.setCharacterSize(20);
	header.setPosition(120, 112);
	header.setOutlineColor(Color::Black);
	header.setOutlineThickness(1);
	item0.setFont(font);
	item0.setCharacterSize(16);
	item0.setPosition(80,176+6);
	item1.setFont(font);
	item1.setCharacterSize(16);
	item1.setPosition(80, 208+6);
	item2.setFont(font);
	item2.setCharacterSize(16);
	item2.setPosition(80, 240+6);
}
void itemClass::plate_display(int playerselect,char* word0,char* word1,char* word2) {
	String word00 = word0;
	String word01 = word1;
	String word02 = word2;
	item0.setString("1 : " + word00);
	item0.setOutlineThickness(1);
	if (currentSelect == 0) {
		item0.setOutlineColor(Color::Yellow);
	}
	else {
		item0.setOutlineColor(Color::Black);
	}
	item1.setString("2 : " + word01);
	item1.setOutlineThickness(1);
	if (currentSelect == 1) {
		item1.setOutlineColor(Color::Yellow);
	}
	else {
		item1.setOutlineColor(Color::Black);
	}
	item2.setString("3 : " + word02);
	item2.setOutlineThickness(1);
	if (currentSelect == 2) {
		item2.setOutlineColor(Color::Yellow);
	}
	else {
		item2.setOutlineColor(Color::Black);
	}
	if (playerselect == 4) {
		plateSprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		plateSprite.setColor(Color(0, 0, 0, 0));
	}
}