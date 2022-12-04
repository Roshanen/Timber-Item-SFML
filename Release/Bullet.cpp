#include "Bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;
void bulletClass::draw_bullet() {
	bulletTexture.loadFromFile("./Sprite/Ball.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setPosition(-100, -100);

	peaBulletTexture.loadFromFile("./Sprite/Peaball.png");
	peaBulletSprite.setTexture(peaBulletTexture);
	peaBulletSprite.setPosition(-100, -100);
}
void bulletClass::fire_bullet(int sety, int setx, int playery, int playerx) {
	bulletSprite.setColor(Color{ 255,255,255,255 });
	bulletSprite.setPosition(playerx * 32, playery * 32);
	direcx = setx;
	direcy = sety;
}
bool bulletClass::bullet_travel(RenderWindow* window, double deltaTime) {
	if (bulletSprite.getPosition().x > 0 && bulletSprite.getPosition().x < 340 && bulletSprite.getPosition().y > 0 && bulletSprite.getPosition().y < 340) {
		totalTime += deltaTime;
		if (totalTime >= switchTime) {
			bulletSprite.move(x + direcx * speed, y + direcy * speed);
			if (speed < 20) {
				speed += 1;
			}
			totalTime -= switchTime;
		}
		return 0;
	}
	else if (bulletSprite.getPosition().x <= 0 || bulletSprite.getPosition().x >= 340 || bulletSprite.getPosition().y <= 0 || bulletSprite.getPosition().y >= 340) {
		bulletSprite.setColor(Color::Transparent);
		speed = 5;
		return 1;
	}
}
void bulletClass::pea_spawn(int posy, int posx) {
	peaState = 1;
	peaBulletSprite.setPosition(posx * 32, posy * 32);
	Vector2f peaPos = peaBulletSprite.getPosition();
	peaDesx = peaPos.x;
	peaDesy = peaPos.y;
}
void bulletClass::pea_travel(RenderWindow* window, int playy, int playx, double deltaTime) {
	Vector2f peaPos = peaBulletSprite.getPosition();
	if ((playx * 32 != (int)peaPos.x) || (playy * 32 != (int)peaPos.y)) {
		peaTotalTime += deltaTime;
		if (peaTotalTime >= peaSwitchTime) {
			peaBulletSprite.move((playx * 32 - peaDesx) / 8, (playy * 32 - peaDesy) / 8);
			peaTotalTime -= peaSwitchTime;
		}
	}
	else {
		peaState = 0;
	}
}