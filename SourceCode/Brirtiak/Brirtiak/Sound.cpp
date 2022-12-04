#include "Sound.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
void soundClass::load_music() {
	chillmusic.openFromFile("Sound/Town.flac");
	chillmusic.setLoop(true);

	hitsoundf.loadFromFile("Sound/Hit.wav");
	hitsound.setBuffer(hitsoundf);
	gomusoundf.loadFromFile("Sound/Gomu2.wav");
	gomusound.setBuffer(gomusoundf);
	gethitsoundf.loadFromFile("Sound/Gethit.wav");
	gethitsound.setBuffer(gethitsoundf);
	jumpsoundf.loadFromFile("Sound/Jump2.wav");
	jumpsound.setBuffer(jumpsoundf);
	itemsoundf.loadFromFile("Sound/Noice.wav");
	itemsound.setBuffer(itemsoundf);
	selectsoundf.loadFromFile("Sound/Select.wav");
	selectsound.setBuffer(selectsoundf);
	continuesoundf.loadFromFile("Sound/Continue.wav");
	continuesound.setBuffer(continuesoundf);
	endsoundf.loadFromFile("Sound/failed.ogg");
	endsound.setBuffer(endsoundf);
	singletypesoundf.loadFromFile("Sound/Singletype.wav");
	singletypesound.setBuffer(singletypesoundf);
	boomsoundf.loadFromFile("Sound/Boom.wav");
	boomsound.setBuffer(boomsoundf);
}
void soundClass::volumn_music(bool operate) {
	if (operate == 0 && chillVolumn < 100) {
		this->chillVolumn += 5;
	}
	else if (operate == 1 && chillVolumn > 0) {
		this->chillVolumn -= 5;
	}
	chillmusic.setVolume(chillVolumn);
}
void soundClass::volumn_sound(bool operate) {
	if (operate == 0 && soundVolumn < 100) {
		this->soundVolumn += 5;
	}
	else if (operate == 1 && soundVolumn > 0) {
		this->soundVolumn -= 5;
	}
}
void soundClass::play_music() {
	chillmusic.play();
	chillmusic.setVolume(chillVolumn);
}
void soundClass::hit_sound() {
	hitsound.setVolume(soundVolumn);
	hitsound.setPlayingOffset(seconds(0.2f));
	hitsound.play();
}
void soundClass::gomu_sound() {
	gomusound.setVolume(soundVolumn);
	gomusound.setPlayingOffset(seconds(0.5f));
	gomusound.play();

}
void soundClass::get_hit_sound() {
	gethitsound.setVolume(soundVolumn);
	gethitsound.setPlayingOffset(seconds(0.3f));
	gethitsound.play();
}
void soundClass::jump_sound()
{
	jumpsound.setVolume(soundVolumn);
	jumpsound.play();
}
void soundClass::item_sound() {
	itemsound.setVolume(soundVolumn);
	itemsound.play();
}
void soundClass::select_sound() {
	selectsound.setVolume(soundVolumn);
	selectsound.setPlayingOffset(seconds(0.15f));
	selectsound.play();
}
void soundClass::continue_sound() {
	continuesound.setVolume(soundVolumn);
	continuesound.setPlayingOffset(seconds(0.3f));
	continuesound.play();
}
void soundClass::end_sound() {
	endsound.setVolume(soundVolumn);
	endsound.play();
}
void soundClass::single_type_sound() {
	singletypesound.setVolume(soundVolumn);
	singletypesound.play();
}
void soundClass::boom_sound() {
	boomsound.setVolume(soundVolumn);
	boomsound.play();
}