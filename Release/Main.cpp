#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Player.h"
#include "Board.h"
#include "Enemy.h"
#include "Item.h" 
#include "Text.h"
#include "Sound.h"
#include "Bullet.h"
#include "Punch.h"
#include "Bomb.h"
#include "UI.h"
#include "Tutorial.h"

#define window_height 960 
#define window_width 1280
#define board_size 12

using namespace sf;

RenderWindow window(VideoMode(window_width, window_height), "Game", Style::Titlebar | Style::Close);

playerClass player;
enemyClass enemy[10];
itemClass item;
textClass text;
boardClass board;
soundClass sound;
bulletClass bullet[10];
punchClass punch;
bombClass bomb[10];
UI ui;
Tutorial tutorial;

char name[20];
bool movable = 1;
int menuSelect = 0; //0start 1score 2setting 3exit
int settingSelect = 0; //0music 1sound
int pauseSelect = 0; //0resume 1score 2setting 3backtomenu
int nextSelect = 0; //0next 1score 2setting 3backtomenu
int state = 8; //0menu 1score 2setting 3intial 4game 5pause 6end 7next 8tutorial
int lastState = 5;
int enemy_horde = 4;
int current_enemy = 0;
int stage = 0;
int turn = 0;
int score = 0;
int kill = 0;
int jewel = 0;
float timer = 0;
char table[board_size][board_size] = { 0 };

struct tokenStruct
{
	int x = 0;
	int y = 0;
	int currentbullet = 0;
	int bulwarkused = 0;
	bool item = 0;
	int hpSum = 0;
} token;

struct scoreStruct
{
	char name[20] = "-";
	int score;
} score_list[5];

void pre_check();
bool all_enemy()
{
	for (int i = 0; i < enemy_horde; i++)
	{
		if (enemy[i].state == 1)
			return 1;
	}
	return 0;
}
void init_state()
{
	if (player.hp <= 0)
	{
		player.hp = 10;
		player.hp_init = 10;

		player.attack = 1;

		player.moveType = 0;

		player.jump_init = 2;
		player.jump_available = 2;

		player.bulwark_cooldown_init = 3;
		player.bulwark_cooldown = 0;

		player.bullet_init = 1;
		player.bullet_available = player.bullet_init;

		player.enrage = 0;
		player.cone_atk = 0;

		player.x = 6;
		player.y = 8;

		stage = 0;
		turn = 0;
		kill = 0;
		jewel = 0;
	}
	else
	{
		stage++;
		turn = 0;
		if (enemy_horde <= 10) {
			enemy_horde = stage / 5 + 4;
		}
		player.moveType = 0;
		player.jump_available = player.jump_init;
		player.bulwark_cooldown = 0;
		player.bullet_available = player.bullet_init;

		player.y = 8;
		player.x = 6;
	}
}
void init_table()
{
	table[player.y][player.x] = player.ch;
	item.y = board_size / 2;
	item.x = rand() % board_size;
	item.state = 1;
	table[item.y][item.x] = item.ch;
	for (int i = 0; i < 10; i++)
	{
		if (i < enemy_horde) {
			enemy[i].init_hp = 1 + (stage / 10);
			enemy[i].enemySprite.setColor(Color(255, 255, 255, 255));
			enemy[i].cooldown = 0;
			enemy[i].type = rand() % 5;
			if (enemy[i].type == 2) {
				enemy[i].atk_ranged = 6;
			}
			else if (enemy[i].type == 1) {
				enemy[i].atk_ranged = 3;
			}
			else {
				enemy[i].atk_ranged = 1;
			}
			if (enemy[i].type == 3) {
				enemy[i].hp = enemy[i].init_hp * 2;
				enemy[i].attack = 1 + (stage / 10);
			}
			else {
				enemy[i].hp = enemy[i].init_hp;
				enemy[i].attack = 1;
			}
			enemy[i].y = rand() % (board_size / 2 - 2);
			enemy[i].x = rand() % (board_size);
			while (table[enemy[i].y][enemy[i].x] != 0)
			{
				enemy[i].y = rand() % (board_size / 2 - 1);
				enemy[i].x = rand() % (board_size);
			}
			enemy[i].state = 1;
			table[enemy[i].y][enemy[i].x] = enemy->ch; // enemy
		}

		board.lava[i].y = rand() % board_size;
		board.lava[i].x = rand() % board_size;
		while (table[board.lava[i].y][board.lava[i].x] != 0)
		{
			board.lava[i].y = rand() % board_size;
			board.lava[i].x = rand() % board_size;
		}
		table[board.lava[i].y][board.lava[i].x] = board.lava->ch; // lava
	}
}
void print_table()
{
	printf("     LAGOONA MATATA\n");
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			printf((table[i][j] == 0) ? "  |" : " %c|", table[i][j]);
			if (i == board_size - 1 && j == board_size - 1)
			{
				printf(" %d %d", player.hp, player.enrage);
				for (int k = 0; k < enemy_horde; k++)
					printf(" %d", enemy[k].hp);
				printf(" %d", score);
			}
		}
		printf("\n");
	}
}
void set_table()
{
	table[player.y][player.x] = player.ch;
	if (item.state == 1)
		table[item.y][item.x] = item.ch;
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i].state == 1) {
			table[enemy[i].y][enemy[i].x] = enemy->ch;
		}
		if (bomb[i].bombState == 1) {
			table[bomb[i].y][bomb[i].x] = bomb->ch;
		}
		table[board.lava[i].y][board.lava[i].x] = board.lava->ch;
	}
}
void clear_table()
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
			table[i][j] = 0;
	}
}
void damage_player(int enemy_attack)
{
	player.hp -= enemy_attack;
	sound.get_hit_sound();
	player.playerSprite.setColor(Color(255, 0, 0));
}
void damage(int y, int x)
{
	for (int i = 0; i < enemy_horde; i++)
	{
		if (enemy[i].state == 0)
			continue;
		if (enemy[i].y == y && enemy[i].x == x)
		{
			if (player.enrage == 1)
			{
				enemy[i].hp -= player.attack;
				player.enrage = 0;
			}
			enemy[i].hp -= player.attack;
			sound.hit_sound();
			enemy[i].enemySprite.setColor(Color(255, 0, 0, 255));
			if (enemy[i].hp <= 0)
			{
				enemy[i].state = 0;
				kill++;
				break;
			}
		}
	}
}
void bomb_spawn(int i) {
	if (table[player.y - 1][player.x] == 0 && (abs(enemy[i].y - player.y) + abs(enemy[i].x - player.x)) <= enemy[i].atk_ranged) {
		table[player.y - 1][player.x] = 'B';
		bomb[i].y = player.y - 1;
		bomb[i].x = player.x;
	}
	else if (table[player.y + 1][player.x] == 0 && (abs(enemy[i].y - player.y) + abs(enemy[i].x - player.x)) <= enemy[i].atk_ranged) {
		table[player.y + 1][player.x] = 'B';
		bomb[i].y = player.y + 1;
		bomb[i].x = player.x;
	}
	else if (table[player.y][player.x + 1] == 0 && (abs(enemy[i].y - player.y) + abs(enemy[i].x - player.x)) <= enemy[i].atk_ranged) {
		table[player.y][player.x + 1] = 'B';
		bomb[i].y = player.y;
		bomb[i].x = player.x + 1;
	}
	else if (table[player.y][player.x - 1] == 0 && (abs(enemy[i].y - player.y) + abs(enemy[i].x - player.x)) <= enemy[i].atk_ranged) {
		table[player.y][player.x - 1] = 'B';
		bomb[i].y = player.y;
		bomb[i].x = player.x - 1;
	}
	bomb[i].spawn_bomb();
}
void loop_bomb() {
	for (int i = 0; i < 10; i++) {
		bomb[i].turn_bomb();
		if (bomb[i].boom == 1) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					if (table[bomb[i].y - 1 + j][bomb[i].x - 1 + k] == player.ch) {
						damage_player(1);
					}
					if (table[bomb[i].y - 1 + j][bomb[i].x - 1 + k] == enemy->ch) {
						damage(bomb[i].y - 1 + j, bomb[i].x - 1 + k);
					}
				}
			}
			sound.boom_sound();
			bomb[i].boom = 0;
		}
	}
}
void item_choose(int choose, int active, char* word)
{
	switch (choose)
	{
	case 0:
		strcpy(word, "Fully Heal");
		if (active == 1)
		{
			player.hp = player.hp_init;
		}
		break;
	case 1:
		strcpy(word, "-2 Hp & +1 Atk");
		if (active == 1)
		{
			player.hp -= 2;
			player.attack++;
		}
		break;
	case 2:
		strcpy(word, "-1 Hp & -1 Cd Bulwark");
		if (active == 1)
		{
			player.hp--;
			player.bulwark_cooldown_init--;
		}
		break;
	case 3:
		strcpy(word, "+1 Max Life");
		if (active == 1)
		{
			player.hp_init++;
		}
		break;
	case 4:
		strcpy(word, "-2 Hp & +1 Max Jump");
		if (active == 1)
		{
			player.hp -= 2;
			player.jump_available++;
			player.jump_init++;
		}
		break;
	case 5:
		strcpy(word, "Sweep Next Atk");
		if (active == 1)
		{
			player.hp -= 3;
			player.cone_atk = 1;
		}
		break;
	case 6:
		strcpy(word, "Pendant(+score)");
		if (active == 1)
		{
			jewel++;
		}
		break;
	case 7:
		strcpy(word, "Jewel(+score)");
		if (active == 1)
		{
			jewel++;
		}
		break;
	case 8:
		strcpy(word, "Enrage next atk");
		if (active == 1)
		{
			player.enrage = 1;
		}
		break;
	case 9:
		strcpy(word, "Mushroom?");
		if (active == 1)
		{
			player.hp += (rand() % 2 == 0) ? 1 : -1;
		}
		break;
	}
	if (active) {
		sound.item_sound();
	}
}
void item_active()
{
	item.state = 0;
	player.moveType = 4;

	item.choice2 = (rand() % 9) + 1;
	item.choice3 = (rand() % 9) + 1;
	while (item.choice2 == item.choice3)
		item.choice3 = (rand() % 9) + 1;

	item_choose(item.choice, 0, item.wchoice);
	item_choose(item.choice2, 0, item.wchoice2);
	item_choose(item.choice3, 0, item.wchoice3);
}
void move(int k = 0, int h = 0)
{

	if (player.y + k >= 0 && player.y + k < board_size && player.x + h >= 0 && player.x + h < board_size)
	{
		player.moveType = 0;
		int unith = 0; // unit vector h
		if (h != 0)
		{
			unith = h / abs(h);
		}
		int unitk = 0; // unit vector k
		if (k != 0)
		{
			unitk = k / abs(k);
		}
		if (table[player.y + unitk][player.x + unith] == item.ch)
		{
			item_active();
		}
		if (table[player.y + k][player.x + h] == 0)
		{
			table[player.y][player.x] = 0;
			player.y += k;
			player.x += h;
			table[player.y][player.x] = player.ch;
			if (abs(k) > 1 || abs(h) > 1) {
				player.jump_available--;
				sound.jump_sound();
			}
		}
		if (table[player.y + unitk][player.x + unith] == enemy->ch)
		{
			damage(player.y + unitk, player.x + unith);
		}
		if (player.cone_atk == 1)
		{
			int n = 0, p = 0;
			if (h == 0)
				n = 1;
			if (k == 0)
				p = 1;
			if (table[player.y + unitk + unith][player.x + unith + unitk] == enemy->ch)
				damage(player.y + unitk + unith, player.x + unith + unitk);
			if (table[player.y + unitk - unith][player.x + unith - unitk] == enemy->ch)
				damage(player.y + unitk - unith, player.x + unith - unitk);
			player.cone_atk = 0;
		}
		player.direction.x = unith;
		player.direction.y = unitk;
	}
}
void enemy_move(int i)
{
	enemy[i].direction.x = enemy[i].x;
	enemy[i].direction.y = enemy[i].y;
	if ((enemy[i].y > player.y) && (table[enemy[i].y - 1][enemy[i].x] == 0) && (enemy[i].y != 0))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].y--;
	}
	else if ((enemy[i].y < player.y) && (table[enemy[i].y + 1][enemy[i].x] == 0) && (enemy[i].y != board_size - 1))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].y++;
	}
	else if ((enemy[i].x > player.x) && (table[enemy[i].y][enemy[i].x - 1] == 0) && (enemy[i].x != 0))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].x--;
	}
	else if ((enemy[i].x < player.x) && (table[enemy[i].y][enemy[i].x + 1] == 0) && (enemy[i].x != board_size - 1))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].x++;
	}
	enemy[i].direction.x = enemy[i].x - enemy[i].direction.x;
	enemy[i].direction.y = enemy[i].y - enemy[i].direction.y;
	//else if (table[enemy[i].y][enemy[i].x + 1] != 0 || table[enemy[i].y][enemy[i].x - 1] != 0) //?
	//{
	//	table[enemy[i].y][enemy[i].x] = 0;
	//	int cont = (rand() % 2 == 0) ? 1 : -1;
	//	int cont2 = -cont;
	//	if (table[enemy[i].y + cont][enemy[i].x] == 0)
	//		enemy[i].y += cont;
	//	else if (table[enemy[i].y + cont2][enemy[i].x] == 0)
	//		enemy[i].y += cont2;
	//}
	//else if (table[enemy[i].y + 1][enemy[i].x] != 0 || table[enemy[i].y - 1][enemy[i].x] != 0) //?
	//{
	//	table[enemy[i].y][enemy[i].x] = 0;
	//	int cont = (rand() % 2 == 0) ? 1 : -1;
	//	int cont2 = -cont;
	//	if (table[enemy[i].y][enemy[i].x + cont] == 0)
	//		enemy[i].x += cont;
	//	else if (table[enemy[i].y][enemy[i].x + cont2] == 0)
	//		enemy[i].x += cont2;
	//}
	table[enemy[i].y][enemy[i].x] = enemy->ch;
}
void enemy_move4(int i) //4reaper
{
	enemy[i].direction.x = enemy[i].x;
	enemy[i].direction.y = enemy[i].y;
	if ((enemy[i].y > player.y) && (table[enemy[i].y - 1][enemy[i].x] == 0 || table[enemy[i].y - 1][enemy[i].x] == board.lava->ch) && (enemy[i].y != 0))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].y--;
	}
	else if ((enemy[i].y < player.y) && (table[enemy[i].y + 1][enemy[i].x] == 0 || table[enemy[i].y + 1][enemy[i].x] == board.lava->ch) && (enemy[i].y != board_size - 1))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].y++;
	}
	else if ((enemy[i].x > player.x) && (table[enemy[i].y][enemy[i].x - 1] == 0 || table[enemy[i].y][enemy[i].x - 1] == board.lava->ch) && (enemy[i].x != 0))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].x--;
	}
	else if ((enemy[i].x < player.x) && (table[enemy[i].y][enemy[i].x + 1] == 0 || table[enemy[i].y][enemy[i].x + 1] == board.lava->ch) && (enemy[i].x != board_size - 1))
	{
		table[enemy[i].y][enemy[i].x] = 0;
		enemy[i].x++;
	}
	for (int i = 0; i < 10; i++) {
		table[board.lava[i].y][board.lava[i].x] = board.lava->ch;
	}
	enemy[i].direction.x = enemy[i].x - enemy[i].direction.x;
	enemy[i].direction.y = enemy[i].y - enemy[i].direction.y;
	table[enemy[i].y][enemy[i].x] = enemy->ch;
}
void enemy_turn()
{
	for (int i = 0; i < enemy_horde; i++)
	{
		if (enemy[i].state == 1)
		{
			if (enemy[i].cooldown >= 0) {
				enemy[i].cooldown--;
			}
			int range = (abs(enemy[i].y - player.y) + abs(enemy[i].x - player.x));
			if (range <= enemy[i].atk_ranged && enemy[i].cooldown <= 0) {
				if (enemy[i].type == 2) {
					bomb_spawn(i);
					enemy[i].cooldown = 5;
				}
				else {
					if (enemy[i].type == 1) {
						bullet[i].pea_spawn(enemy[i].y, enemy[i].x);
					}
					damage_player(enemy[i].attack);
				}
			}
			else if (range > 1) {
				if (enemy[i].type == 4) {
					enemy_move4(i);
				}
				else {
					enemy_move(i);
				}
			}
		}
	}
}
void update_score()
{
	score = (stage * 3) + (kill * 2) + (jewel * 5);
}
void read_score() {

	FILE* fp;
	fp = fopen("data.txt", "r");
	for (int i = 0; i < 5; i++) {
		char buff[25]{};
		fscanf(fp, "%s", score_list[i].name);
		//printf("%s\n", score_list[i].name);
		fscanf(fp, "%s", buff);
		int number = 0;
		for (int j = 0; j < 24; j++) {
			if (buff[j] >= '0' && buff[j] <= '9') {
				number = (number * 10) + (buff[j] - '0');
			}
		}
		score_list[i].score = number;
		//printf("%d\n", number);
	}

	fclose(fp);
}
void write_score()
{
	FILE* fp;
	fp = fopen("data.txt", "w");
	for (int i = 0; i < 5; i++) {
		fprintf(fp, "%s\n%d\n", score_list[i].name, score_list[i].score);
	}
	fclose(fp);
}
void sort_score(String playername) {
	if (score > score_list[4].score) {
		score_list[4].score = score;
		for (int i = 0; i < playername.getSize(); i++) {
			score_list[4].name[i] = playername[i];
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (score_list[i].score < score_list[j].score) {
				char nametemp[20] = "\0";
				int temp = score_list[j].score;	//
				strcpy(nametemp, score_list[i].name);

				score_list[j].score = score_list[i].score;	//
				strcpy(score_list[i].name, score_list[j].name);

				score_list[i].score = temp;	//
				strcpy(score_list[j].name, nametemp);
			}
		}
	}
}
void pre_check()
{
	token.y = player.y;
	token.x = player.x;
	token.currentbullet = player.bullet_available;
	token.bulwarkused = player.bulwark_cooldown;
	token.item = item.state;
	token.hpSum = 0;
	for (int i = 0; i < enemy_horde; i++)
		if (enemy[i].state == 1)
			token.hpSum += enemy[i].hp;
}
int check()
{
	if ((token.y == player.y) && (token.x == player.x)
		&& (token.item == item.state)
		&& (token.currentbullet == player.bullet_available)
		&& (token.bulwarkused >= player.bulwark_cooldown))
	{
		for (int i = 0; i < enemy_horde; i++) {
			if (enemy[i].state == 1)
				token.hpSum -= enemy[i].hp;
		}
		if (token.hpSum == 0) {
			return 0;
		}
	}
	return 1;
}
void push(int y, int x, int k, int h)
{
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i].y == y && enemy[i].x == x)
		{
			table[enemy[i].y][enemy[i].x] = 0;
			enemy[i].y += k;
			enemy[i].x += h;
			if (table[enemy[i].y][enemy[i].x] == board.lava->ch)
			{
				enemy[i].hp = 0;
				enemy[i].state = 0;
			}
			else
				table[enemy[i].y][enemy[i].x] = enemy->ch;
		}
		if (bomb[i].y == y && bomb[i].x == x)
		{
			table[bomb[i].y][bomb[i].x] = 0;
			bomb[i].y += k;
			bomb[i].x += h;
		}
	}
}
void bulwark(int k, int h)
{
	for (int i = -1; i <= 1; i++)
	{
		int n = 0, p = 0;
		if (h == 0)
			n = i;
		else if (k == 0)
			p = i;
		if (table[player.y + k + p][player.x + h + n] == enemy->ch || table[player.y + k + p][player.x + h + n] == bomb->ch)
		{
			if (table[player.y + (2 * k) + p][player.x + (2 * h) + n] == 0 || table[player.y + (2 * k) + p][player.x + (2 * h) + n] == board.lava->ch)
			{
				damage(player.y + k + p, player.x + h + n);
				push(player.y + k + p, player.x + h + n, k, h);
			}
			else if (table[player.y + (2 * k) + p][player.x + (2 * h) + n] != 0)
			{
				damage(player.y + k + p, player.x + h + n);
			}
			player.bulwark_cooldown = player.bulwark_cooldown_init;
		}
	}
	punch.punch_animation(player.y, player.x, k, h);
	sound.gomu_sound();
	for (int i = 0; i < 10; i++) {
		enemy[i].enemySprite.setPosition(enemy[i].x * 32, enemy[i].y * 32);
	}
	player.moveType = 0;
}
void statchange(int subState) {
	if (state == subState) {
		state = lastState;
	}
	else {
		lastState = state;
		state = subState;
	}
}

void set_sprite(RenderWindow& window) {
	board.draw_table();
	item.draw_item();
	player.draw_player(&window);
	for (int i = 0; i < 10; i++) {
		bullet[i].draw_bullet();
	}
	for (int i = 0; i < 10; i++) {
		bomb[i].draw_bomb();
		if (i < enemy_horde) {
			double setRandom = (double)(rand() % 50) / 100;
			enemy[i].init_enemy(setRandom);
			enemy[i].draw_enemy(&window);
		}

	}
	punch.draw_punch();
	ui.draw_UI();
}
void draw_things(RenderWindow& window) {
	window.clear();
	window.draw(board.boardSprite);
	for (int i = 0; i < 10; i++) {
		window.draw(board.lavaSprite[i]);
	}
	for (int i = 0; i < 10; i++) {
		if (bomb[i].bombState == 1) {
			window.draw(bomb[i].bombSprite);
		}
	}
	for (int i = 0; i < 10; i++) {
		if (bullet[i].peaState == 1) {
		window.draw(bullet[i].peaBulletSprite);
		}
	}
	for (int i = 0; i < 10; i++) {
		if (enemy[i].state == 1) {
			window.draw(enemy[i].enemySprite);
			//window.draw(enemy[i].hpText);
		}
	}

	window.draw(bullet[0].bulletSprite);

	window.draw(player.playerSprite);
	window.draw(punch.punchSprite);
	if (item.state == 1) {
		window.draw(item.itemSprite);
	}

	window.draw(ui.healthSprite);
	window.draw(ui.healthText);

	window.draw(ui.scoreSprite);
	window.draw(ui.scoreText);

	window.draw(ui.jumpSprite);
	window.draw(ui.jumpText);

	window.draw(ui.bulletSprite);
	window.draw(ui.bulletText);
	window.draw(ui.bulwarkSprite);
	window.draw(ui.bulwarkText);
	if (player.moveType == 4) {
		window.draw(item.plateSprite);
		window.draw(item.header);
		window.draw(item.item0);
		window.draw(item.item1);
		window.draw(item.item2);
	}
	window.draw(text.helper);
}
void ui_set() {
	ui.health_bar(player.hp);
	ui.score_bar(score);
	ui.jump_bar(player.jump_available, player.moveType);
	ui.bulwark_bar(player.bulwark_cooldown, player.moveType);
	ui.bullet_bar(player.bullet_available, player.moveType);
}
void bullet_intersect() {
	for (int i = 0; i < 10; i++) {
		if (enemy[i].state == 1) {
			if (bullet[0].bulletSprite.getGlobalBounds().intersects(enemy[i].enemySprite.getGlobalBounds()))
			{
				enemy[i].hp--;
				if (enemy[i].hp <= 0) {
					enemy[i].state = 0;
				}
				sound.hit_sound();
				enemy[i].enemySprite.setColor(Color(255, 0, 0, 255));
				bullet[0].bulletSprite.setColor(Color::Transparent);
				bullet[0].bulletSprite.setPosition(-100, -100);
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	window.setKeyRepeatEnabled(false);
	text.load_font();
	sound.load_music();
	sound.play_music();
	tutorial.draw_tutorial();

	Event ev;
	Clock clock;
	View viewRect;
	viewRect.setCenter(192, 192);
	viewRect.setSize(450, 450);
	window.setView(viewRect);

	String playerInput = {};
	read_score();
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		pre_check();
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::KeyPressed:
				if (state == 0) {
					if (ev.key.code == sf::Keyboard::Enter) {
						if (menuSelect == 0) {
							if (player.hp <= 0) {
								state = 3;
							}
							else {
								state = 4;
							}
						}
						else if (menuSelect == 1) {
							state = 1;
						}
						else if (menuSelect == 2) {
							state = 2;
						}
						else if (menuSelect == 3) {
							window.close();
						}
					}
					else if (ev.key.code == Keyboard::W || ev.key.code == Keyboard::Up) {
						menuSelect--;
						if (menuSelect < 0) {
							menuSelect = 3;
						}
						sound.select_sound();
					}
					else if (ev.key.code == Keyboard::S || ev.key.code == Keyboard::Down) {
						menuSelect++;
						if (menuSelect > 3) {
							menuSelect = 0;
						}
						sound.select_sound();
					}
				}
				else if (state == 1) {
					if (ev.key.code == sf::Keyboard::Escape) {
						statchange(1);
					}
				}
				else if (state == 2) {
					if (ev.key.code == Keyboard::Escape) {
						statchange(2);
						//setting();
					}
					else if (ev.key.code == Keyboard::A || ev.key.code == Keyboard::Left) {
						if (settingSelect == 0) {
							sound.volumn_music(1);
						}
						else if (settingSelect == 1) {
							sound.volumn_sound(1);
						}
						sound.select_sound();
					}
					else if (ev.key.code == Keyboard::D || ev.key.code == Keyboard::Right) {
						if (settingSelect == 0) {
							sound.volumn_music(0);
						}
						else if (settingSelect == 1) {
							sound.volumn_sound(0);
						}
						sound.select_sound();
					}
					else if (ev.key.code == Keyboard::W || ev.key.code == Keyboard::Up) {
						settingSelect--;
						if (settingSelect < 0) {
							settingSelect = 1;
						}
						sound.select_sound();
					}
					else if (ev.key.code == Keyboard::S || ev.key.code == Keyboard::Down) {
						settingSelect++;
						if (settingSelect > 1) {
							settingSelect = 0;
						}
						sound.select_sound();
					}
				}
				else if (state == 4) {
					if (movable == 1) {
						if (ev.key.code == sf::Keyboard::F && player.jump_available > 0)
						{
							if (player.moveType == 1) {
								player.moveType = 0;
							}
							else {
								player.moveType = 1;
							}
						}
						else if (ev.key.code == sf::Keyboard::Q && player.bulwark_cooldown <= 0)
						{

							if (player.moveType == 2) {
								player.moveType = 0;
							}
							else {
								player.moveType = 2;
							}
						}
						else if (ev.key.code == sf::Keyboard::E && player.bullet_available > 0)
						{

							if (player.moveType == 3) {
								player.moveType = 0;
							}
							else {
								player.moveType = 3;
							}
						}
						else if (ev.key.code == sf::Keyboard::Escape)
						{
							statchange(5);
						}
						else if (player.moveType == 4) {
							if (ev.key.code == Keyboard::Enter) {
								if (item.currentSelect == 0) {
									item_choose(item.choice, 1, item.wchoice);
									player.moveType = 0;
									item.currentSelect = 0;
								}
								else if (item.currentSelect == 1) {
									item_choose(item.choice2, 1, item.wchoice2);
									player.moveType = 0;
									item.currentSelect = 0;
								}
								else if (item.currentSelect == 2) {
									item_choose(item.choice3, 1, item.wchoice3);
									player.moveType = 0;
									item.currentSelect = 0;
								}
							}
							else if (ev.key.code == Keyboard::W || ev.key.code == Keyboard::Up) {
								item.currentSelect--;
								if (item.currentSelect < 0) {
									item.currentSelect = 2;
								}
							}
							else if (ev.key.code == Keyboard::S || ev.key.code == Keyboard::Down) {
								item.currentSelect++;
								if (item.currentSelect > 2) {
									item.currentSelect = 0;
								}
							}
							else if (ev.key.code == sf::Keyboard::Num1)
							{
								item_choose(item.choice, 1, item.wchoice);
								player.moveType = 0;
							}
							else if (ev.key.code == sf::Keyboard::Num2)
							{
								item_choose(item.choice2, 1, item.wchoice2);
								player.moveType = 0;
							}
							else if (ev.key.code == sf::Keyboard::Num3)
							{
								item_choose(item.choice3, 1, item.wchoice3);
								player.moveType = 0;
							}
						}
						else if (player.moveType == 1) {
							if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Up)
							{
								move(-2, 0);
							}
							else if (ev.key.code == sf::Keyboard::A || ev.key.code == sf::Keyboard::Left)
							{
								move(0, -2);
							}
							else if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Down)
							{
								move(2, 0);
							}
							else if (ev.key.code == sf::Keyboard::D || ev.key.code == sf::Keyboard::Right)
							{
								move(0, 2);
							}
							else if (ev.key.code == sf::Keyboard::F)
							{
								player.moveType = 0;
							}
						}
						else if (player.moveType == 2)
						{
							if (ev.key.code == sf::Keyboard::W || ev.key.code == Keyboard::Up) {
								bulwark(-1, 0);
								player.bulwark_cooldown = player.bulwark_cooldown_init;
							}
							else if (ev.key.code == sf::Keyboard::A || ev.key.code == Keyboard::Left) {
								bulwark(0, -1);
								player.bulwark_cooldown = player.bulwark_cooldown_init;
							}
							else if (ev.key.code == sf::Keyboard::S || ev.key.code == Keyboard::Down) {
								bulwark(1, 0);
								player.bulwark_cooldown = player.bulwark_cooldown_init;
							}
							else if (ev.key.code == sf::Keyboard::D || ev.key.code == Keyboard::Right) {
								bulwark(0, 1);
								player.bulwark_cooldown = player.bulwark_cooldown_init;
							}
							else if (ev.key.code == sf::Keyboard::Q) {
								player.moveType = 0;
							}
							/*if (check() == 1) {
								player.bulwark_cooldown = player.bulwark_cooldown_init;
							}*/
						}
						else if (player.moveType == 3) {
							if (ev.key.code == sf::Keyboard::W || ev.key.code == Keyboard::Up) {
								bullet[0].fire_bullet(-1, 0, player.y, player.x);
								player.bullet_available--;
								player.moveType = 0;
							}
							else if (ev.key.code == sf::Keyboard::A || ev.key.code == Keyboard::Left) {
								bullet[0].fire_bullet(0, -1, player.y, player.x);
								player.bullet_available--;
								player.moveType = 0;
							}
							else if (ev.key.code == sf::Keyboard::S || ev.key.code == Keyboard::Down) {
								bullet[0].fire_bullet(1, 0, player.y, player.x);
								player.bullet_available--;
								player.moveType = 0;
							}
							else if (ev.key.code == sf::Keyboard::D || ev.key.code == Keyboard::Right) {
								bullet[0].fire_bullet(0, 1, player.y, player.x);
								player.bullet_available--;
								player.moveType = 0;
							}
							else if (ev.key.code == sf::Keyboard::E) {
								player.moveType = 0;
							}
						}
						else if (player.moveType == 0) {
							if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Up)
							{
								move(-1, 0);
							}
							else if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Down)
							{
								move(1, 0);
							}
							else if (ev.key.code == sf::Keyboard::A || ev.key.code == sf::Keyboard::Left)
							{
								move(0, -1);
							}
							else if (ev.key.code == sf::Keyboard::D || ev.key.code == sf::Keyboard::Right)
							{
								move(0, 1);
							}
						}
						if (ev.KeyPressed) {
							movable = 0;
						}
					}
				}
				else if (state == 5) {
					if (ev.key.code == Keyboard::Escape) {
						state = 4;
					}
					else if (ev.key.code == Keyboard::Enter) {
						if (pauseSelect == 0) {
							state = 4;
						}
						else if (pauseSelect == 1) {
							state = 1;
						}
						else if (pauseSelect == 2) {
							state = 2;
						}
						else if (pauseSelect == 3) {
							state = 0;
						}
						else if (pauseSelect == 4) {
							player.hp = -1;
							state = 4;
						}
					}
					else if (ev.key.code == Keyboard::W || ev.key.code == Keyboard::Up) {
						pauseSelect--;
						if (pauseSelect < 0) {
							pauseSelect = 4;
						}
						sound.select_sound();
					}
					else if (ev.key.code == Keyboard::S || ev.key.code == Keyboard::Down) {
						pauseSelect++;
						if (pauseSelect > 4) {
							pauseSelect = 0;
						}
						sound.select_sound();
					}
				}
				else if (state == 6) {
					if (ev.key.code == Keyboard::Backspace && playerInput.getSize() > 0) {
						String::Iterator lastInput = playerInput.end();
						playerInput.erase(playerInput.getSize() - 1);
					}
					else if (ev.key.code == Keyboard::Enter) {
						sort_score(playerInput);
						write_score();
						playerInput = {};
						state = 0;
					}
				}
				else if (state == 7) {
					if (ev.key.code == Keyboard::Enter) {
						if (nextSelect == 0) {
							if (player.hp <= 0) {
								state = 6;
							}
							else {
								state = 3;
							}
						}
						else if (nextSelect == 1) {
							state = 1;
						}
						else if (nextSelect == 2) {
							state = 2;
						}
						else if (nextSelect == 3) {
							state = 0;
						}
						sound.continuesound.stop();
					}
					else if (ev.key.code == Keyboard::W || ev.key.code == Keyboard::Up) {
						nextSelect--;
						if (nextSelect < 0) {
							nextSelect = 3;
						}
						sound.select_sound();
					}
					else if (ev.key.code == Keyboard::S || ev.key.code == Keyboard::Down) {
						nextSelect++;
						if (nextSelect > 3) {
							nextSelect = 0;
						}
						sound.select_sound();
					}
				}
				else if (state == 8) {
					if (ev.KeyPressed) {
						state = 0;
					}
				}
				break;
				/*case sf::Event::MouseButtonPressed:
					if (ev.mouseButton.button == Mouse::Left) {
						Vector2i pos = Mouse::getPosition(window);
						std::cout << "mousepos : ";
						std::cout << (pos.x - 80) / 3 << ' ' << (pos.y - 60) / 3 * 2 << std::endl;
					}
					break;*/
			case sf::Event::TextEntered:
				if (state == 6) {
					if (ev.text.unicode < 122 && ev.text.unicode > 33 && playerInput.getSize() < 20) {
						playerInput += ev.text.unicode;
						sound.single_type_sound();
					}
				}
				break;
			}
			if (ev.type == Event::Closed) {
				window.close();
			}
		}
		if (state == 0) //0menu
		{
			lastState = 0;
			window.clear();
			text.main_menu(menuSelect);
			window.draw(text.name);
			window.draw(text.gamename);
			window.draw(text.pressAnyKey);
			window.draw(text.scoreboard);
			window.draw(text.setting);
			window.draw(text.exit);
		}
		if (state == 1) //score
		{
			window.clear();
			String namep = "unknow";
			for (int i = 0; i < 5; i++) {
				text.score_menu(score_list[i].name, score_list[i].score, i);
				window.draw(text.user[i]);
				window.draw(text.userScore[i]);
			}
			window.draw(text.headScore);
		}
		if (state == 2) //setting
		{
			window.clear();
			text.setting_menu(sound.chillVolumn, sound.soundVolumn, settingSelect);
			window.draw(text.headSetting);
			window.draw(text.volumnScale);
			window.draw(text.soundScale);
		}
		if (state == 3) //initial
		{
			clear_table();
			init_state();
			init_table();
			set_table();
			set_sprite(window);
			pre_check();
			state = 4;
		}
		if (state == 4)
		{
			menuSelect = 0, pauseSelect = 0, nextSelect = 0;
			ui_set();
			if (check() == 1)
			{
				turn++;
				loop_bomb();
				enemy_turn();
				if (player.bulwark_cooldown > 0) {
					player.bulwark_cooldown--;
				}
				clear_table();
				set_table();
				board.draw_table();
				current_enemy = 0;
			}

			bullet_intersect();
			for (int i = 0; i < 10; i++) {
				bullet[i].pea_travel(&window, player.y, player.x, deltaTime);
			}
			if (bullet[0].bullet_travel(&window, deltaTime)) {
				if (player.move_player(&window, deltaTime)) {
					if (enemy[current_enemy].move_enemy(&window, deltaTime)) {
						current_enemy++;
						if (current_enemy >= enemy_horde) {
							current_enemy = 0;
							movable = 1;
						}
					}
				}
			}

			update_score();
			item.plate_display(player.moveType, item.wchoice, item.wchoice2, item.wchoice3);
			//lower
			player.animation(&window, deltaTime);
			for (short i = 0; i < 10; i++) {
				if (enemy[i].state == 1) {
					enemy[i].animation(&window, deltaTime);
				}
				if (bomb[i].bombState == 1) {
					bomb[i].animation(deltaTime);
				}
			}
			punch.punch_update(deltaTime);
			//
			draw_things(window);
			if (all_enemy() == 0 || player.hp <= 0) {
				timer += deltaTime;
				if (timer >= 0.5) {
					timer = 0;
					state = 7;
					if (player.hp <= 0) {
						sound.end_sound();
					}
					else {
						sound.continue_sound();
					}
				}
			}
		}
		if (state == 5) {
			lastState = 5;
			window.clear();
			text.pause_display(window_height, window_width, pauseSelect);
			window.draw(text.endThis);
			window.draw(text.pause);
			window.draw(text.pressAnyKey);
			window.draw(text.scoreboard);
			window.draw(text.setting);
			window.draw(text.exit);
		}
		if (state == 6) {
			window.clear();
			text.end_display(playerInput);
			window.draw(text.headEnd);
			window.draw(text.endInput);
			window.draw(text.enterToContinue);
		}
		if (state == 7) {
			lastState = 7;
			window.clear();
			text.next_display(window_height, window_width, nextSelect, player.hp, score);
			window.draw(text.pause);
			window.draw(text.pressAnyKey);
			window.draw(text.scoreboard);
			window.draw(text.setting);
			window.draw(text.exit);
		}
		if (state == 8) {
			window.draw(tutorial.tutorialSprite);
		}

		window.display();
	}
	return 0;
}
