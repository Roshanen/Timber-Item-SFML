#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
class soundClass
{
public:
	Music chillmusic;
	SoundBuffer hitsoundf;
	Sound hitsound;
	SoundBuffer gomusoundf;
	Sound gomusound;
	SoundBuffer gethitsoundf;
	Sound gethitsound;
	SoundBuffer jumpsoundf;
	Sound jumpsound;
	SoundBuffer itemsoundf;
	Sound itemsound;
	SoundBuffer selectsoundf;
	Sound selectsound;
	SoundBuffer continuesoundf;
	Sound continuesound;
	SoundBuffer endsoundf;
	Sound endsound;
	SoundBuffer singletypesoundf;
	Sound singletypesound;
	SoundBuffer boomsoundf;
	Sound boomsound;

	int chillVolumn = 10;
	int soundVolumn = 20;

	void load_music();
	void volumn_music(bool);
	void volumn_sound(bool);
	void play_music();

	void hit_sound();
	void gomu_sound();
	void get_hit_sound();
	void jump_sound();
	void item_sound();
	void select_sound();
	void continue_sound();
	void end_sound();
	void single_type_sound();
	void boom_sound();
};

