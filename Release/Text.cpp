#include "Text.h"
#include <SFML/Graphics.hpp>
using namespace sf;

void textClass::load_font() {
	font.loadFromFile("./Font/04B_30__.TTF");
	arial.loadFromFile("./Font/arial.ttf");

	name.setFont(arial);
	name.setString("65010100_KACHEN");
	name.setPosition(-32,-32);
	name.setFillColor(Color::White);
	name.setCharacterSize(10);
	name.setOutlineColor(Color::White);
	name.setOutlineThickness(0.5);

	helper.setFont(arial);
	helper.setString("W,A,S,D : MOVE | F : JUMP | Q : FIST | E : FIRE");
	helper.setPosition(-32, 400);
	helper.setFillColor(Color::White);
	helper.setCharacterSize(10);
	helper.setOutlineColor(Color::White);
	helper.setOutlineThickness(0.5);

	gamename.setFont(font);
	pressAnyKey.setFont(font);
	scoreboard.setFont(font);
	setting.setFont(font);
	exit.setFont(font);

	headScore.setFont(font);
	for (int i = 0; i < 5; i++) {
		user[i].setFont(font);
		userScore[i].setFont(font);
	}

	headSetting.setFont(font);
	volumnScale.setFont(font);
	soundScale.setFont(font);

	pause.setFont(font);
	endThis.setFont(font);

	headEnd.setFont(font);
	endInput.setFont(arial);
	enterToContinue.setFont(arial);

}
void textClass::main_menu(int i) {
	gamename.setString("TIMBER \nITEM");
	gamename.setCharacterSize(32);
	gamename.setOutlineThickness(1);
	gamename.setOutlineColor(Color::White);
	gamename.setLetterSpacing(2);
	gamename.setFillColor(Color(50, 205, 50));
	gamename.setPosition(32, 64);
	gamename.setStyle(Text::Bold);

	pressAnyKey.setString("START");
	pressAnyKey.setCharacterSize(16);
	pressAnyKey.setFillColor(Color::White);
	pressAnyKey.setPosition(32, 192);
	if (i == 0) {
		pressAnyKey.setOutlineThickness(1);
		pressAnyKey.setOutlineColor(Color::Red);
	}
	else {
		pressAnyKey.setOutlineThickness(0);
	}
	scoreboard.setString("SCOREBOARD");
	scoreboard.setCharacterSize(16);
	scoreboard.setFillColor(Color::White);
	scoreboard.setPosition(32, 225);
	if (i == 1) {
		scoreboard.setOutlineThickness(1);
		scoreboard.setOutlineColor(Color::Red);
	}
	else {
		scoreboard.setOutlineThickness(0);
	}
	setting.setString("SETTING");
	setting.setCharacterSize(16);
	setting.setFillColor(Color::White);
	setting.setPosition(32, 257);
	if (i == 2) {
		setting.setOutlineThickness(1);
		setting.setOutlineColor(Color::Red);
	}
	else {
		setting.setOutlineThickness(0);
	}
	exit.setString("EXIT");
	exit.setCharacterSize(16);
	exit.setFillColor(Color::White);
	exit.setPosition(32, 289);
	if (i == 3) {
		exit.setOutlineThickness(1);
		exit.setOutlineColor(Color::Red);
	}
	else {
		exit.setOutlineThickness(0);
	}
}
void textClass::score_menu(String name, int score, int i) {
	String string_score = std::to_string(score);
	headScore.setString("SCOREBOARD");
	headScore.setCharacterSize(32);
	headScore.setFillColor(Color::White);
	headScore.setPosition(32, 32);

	user[i].setString(name);
	user[i].setCharacterSize(16);
	user[i].setFillColor(Color::White);
	user[i].setPosition(128, 96 + 32 * i);

	userScore[i].setString(string_score);
	userScore[i].setCharacterSize(16);
	userScore[i].setFillColor(Color::White);
	userScore[i].setPosition(32, 96 + 32 * i);
}
void textClass::setting_menu(int volumnmusic, int volumnsound, int i) {
	String string_volumnmusic = std::to_string(volumnmusic);
	String string_volumnsound = std::to_string(volumnsound);
	headSetting.setString("SETTING");
	headSetting.setCharacterSize(32);
	headSetting.setFillColor(Color::White);
	headSetting.setPosition(96, 32);
	headSetting.setOutlineColor(Color::Black);
	headSetting.setOutlineThickness(1);

	volumnScale.setString("Music " + string_volumnmusic);
	volumnScale.setCharacterSize(24);
	volumnScale.setFillColor(Color::White);
	volumnScale.setPosition(32, 96);
	volumnScale.setOutlineThickness(1);
	if (i == 0) {
		volumnScale.setOutlineColor(Color::Green);
	}
	else {
		volumnScale.setOutlineColor(Color::Black);
	}

	soundScale.setString("Sound " + string_volumnsound);
	soundScale.setCharacterSize(24);
	soundScale.setFillColor(Color::White);
	soundScale.setPosition(32, 128);
	soundScale.setOutlineThickness(1);
	if (i == 1) {
		soundScale.setOutlineColor(Color::Green);
	}
	else {
		soundScale.setOutlineColor(Color::Black);
	}
}
void textClass::pause_display(int height, int width, int i) {
	pause.setString("Pause");
	pause.setCharacterSize(48);
	pause.setOutlineColor(Color::Black);
	pause.setOutlineThickness(2);
	pause.setFillColor(Color::White);
	pause.setPosition(height / 9, width / 9 - 64);

	endThis.setString("END THIS GAME");
	endThis.setCharacterSize(16);
	endThis.setColor(Color::White);
	endThis.setPosition(32, 160);
	if (i == 4) {
		endThis.setOutlineThickness(1);
		endThis.setOutlineColor(Color(20, 210, 50));
	}
	else {
		endThis.setOutlineThickness(0);
	}

	pressAnyKey.setString("RESUME");
	pressAnyKey.setCharacterSize(16);
	pressAnyKey.setFillColor(Color::White);
	pressAnyKey.setPosition(32, 192);
	if (i == 0) {
		pressAnyKey.setOutlineThickness(1);
		pressAnyKey.setOutlineColor(Color(20, 210, 50));
	}
	else {
		pressAnyKey.setOutlineThickness(0);
	}

	scoreboard.setString("SCOREBOARD");
	scoreboard.setCharacterSize(16);
	scoreboard.setFillColor(Color::White);
	scoreboard.setPosition(32, 225);
	if (i == 1) {
		scoreboard.setOutlineThickness(1);
		scoreboard.setOutlineColor(Color(20, 210, 50));
	}
	else {
		scoreboard.setOutlineThickness(0);
	}

	setting.setString("SETTING");
	setting.setCharacterSize(16);
	setting.setFillColor(Color::White);
	setting.setPosition(32, 257);
	if (i == 2) {
		setting.setOutlineThickness(1);
		setting.setOutlineColor(Color(20, 210, 50));
	}
	else {
		setting.setOutlineThickness(0);
	}

	exit.setString("MAIN MANU");
	exit.setCharacterSize(16);
	exit.setFillColor(Color::White);
	exit.setPosition(32, 289);
	if (i == 3) {
		exit.setOutlineThickness(1);
		exit.setOutlineColor(Color(20, 210, 50));
	}
	else {
		exit.setOutlineThickness(0);
	}
}

void textClass::next_display(int height, int width, int i, int hp, int score) {
	String string_score = std::to_string(score);
	if (hp > 0) {
		pause.setString("YOU WON STAGE\nSCORE " + string_score);
	}
	else {
		pause.setString("YOU DIED\nSCORE " + string_score);
	}
	pause.setCharacterSize(24);
	pause.setOutlineColor(Color::Black);
	pause.setOutlineThickness(2);
	pause.setFillColor(Color::Yellow);
	pause.setPosition(height / 9 - 64, width / 9 - 64);

	pressAnyKey.setString("CONTINUE");
	pressAnyKey.setCharacterSize(16);
	pressAnyKey.setFillColor(Color::White);
	pressAnyKey.setPosition(32, 192);
	if (i == 0) {
		pressAnyKey.setOutlineThickness(1);
		pressAnyKey.setOutlineColor(Color(255, 100, 0));
	}
	else {
		pressAnyKey.setOutlineThickness(0);
	}

	scoreboard.setString("SCOREBOARD");
	scoreboard.setCharacterSize(16);
	scoreboard.setFillColor(Color::White);
	scoreboard.setPosition(32, 225);
	if (i == 1) {
		scoreboard.setOutlineThickness(1);
		scoreboard.setOutlineColor(Color(255, 100, 0));
	}
	else {
		scoreboard.setOutlineThickness(0);
	}

	setting.setString("SETTING");
	setting.setCharacterSize(16);
	setting.setFillColor(Color::White);
	setting.setPosition(32, 257);
	if (i == 2) {
		setting.setOutlineThickness(1);
		setting.setOutlineColor(Color(255, 100, 0));
	}
	else {
		setting.setOutlineThickness(0);
	}

	exit.setString("MAIN MANU");
	exit.setCharacterSize(16);
	exit.setFillColor(Color::White);
	exit.setPosition(32, 289);
	if (i == 3) {
		exit.setOutlineThickness(1);
		exit.setOutlineColor(Color(255, 100, 0));
	}
	else {
		exit.setOutlineThickness(0);
	}
}

void textClass::end_display(String playerInput) {
	headEnd.setString("GAME END\nENTER YOUR NAME");
	headEnd.setCharacterSize(16);
	headEnd.setFillColor(Color::White);
	headEnd.setPosition(12, 0);

	endInput.setString(playerInput);
	endInput.setCharacterSize(16);
	endInput.setFillColor(Color::Yellow);
	endInput.setPosition(12, 72);

	enterToContinue.setString("Press Enter to continue");
	enterToContinue.setCharacterSize(16);
	enterToContinue.setPosition(12, 108);
}