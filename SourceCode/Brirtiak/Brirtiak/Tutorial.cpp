#include "Tutorial.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void Tutorial::draw_tutorial() {
	tutorialTexture.loadFromFile("./Sprite/tutorial.png");
	tutorialSprite.setTexture(tutorialTexture);
	tutorialSprite.setScale(0.37,0.45);
	tutorialSprite.setPosition(-48, -32);
}