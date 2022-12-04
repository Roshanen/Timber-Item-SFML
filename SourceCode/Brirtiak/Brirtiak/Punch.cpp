#include "Punch.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void punchClass::draw_punch() {
	punchTexture.loadFromFile("./Sprite/Gomu.png");
	punchSprite.setTexture(punchTexture);
	punchSprite.setOrigin(48, 16);
	punchSprite.setColor(Color::Transparent);
}
void punchClass::punch_animation(int posy, int posx, int k, int h) {

	alphaColor = 255;
	punchSprite.setColor(Color(255, 255, 255, alphaColor));
	punchSprite.setRotation((h * 90) + (k * 90 + 90) * k);
	punchSprite.setPosition((posx + h) * 32 +16, (posy + k) * 32 +16);
	punchState = 1;
}
void punchClass::punch_update(double deltaTime) {
	if (punchState == 1) {
		punchTime += deltaTime;
		if (punchTime >= punchFadeInterval) {
			alphaColor -= 100;
			punchSprite.setColor(Color(255, 255, 255, alphaColor));
			if (alphaColor <= 0) {
				punchSprite.setColor(Color::Transparent);
				punchState = 0;
			}
			punchTime -= punchFadeInterval;
		}
	}
}
