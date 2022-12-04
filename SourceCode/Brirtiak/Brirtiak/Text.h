#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class textClass
{
public:
	Font font;
	Font arial;

	Text name;
	Text helper;

	Text gamename;
	Text pressAnyKey;
	Text scoreboard;
	Text setting;
	Text exit;

	Text headScore;
	Text user[5];
	Text userScore[5];

	Text headSetting;
	Text volumnScale;
	Text soundScale;

	Text pause;
	Text endThis;

	Text headEnd;
	Text endInput;
	Text enterToContinue;

	void load_font();
	void main_menu(int);
	void score_menu(String, int, int);
	void setting_menu(int, int, int);
	void pause_display(int, int, int);
	void end_display(String);
	void next_display(int, int, int, int, int);
};

