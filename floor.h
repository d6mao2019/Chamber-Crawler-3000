#ifndef FLOOR_H
#define FLOOR_H
#include <memory>
#include <vector>
class Enemy;
class Potion;
class Gold;
class Player;

class Floor
{
	std::vector<std::vector<char>> text_display;
	std::vector<std::shared_ptr<Enemy>> enemy_list;
	std::vector<std::shared_ptr<Potion>> potion_list;
	std::vector<std::shared_ptr<Gold>> gold_list;
	std::shared_ptr<Player> player;
	bool ERM; // enemy random move controller.

public:
	Floor(int enemy_num, int positon_num, int gold_num); // responsible for generating chambers and enemies.
	void beNotifiedBy(Enemy &e);						 // enemies notify floor when they are slain.
	void ERMSwitch();									 // turn on/off enemy random moves.
	// tick does two things.
	// 1. enemies move randomly if ERM is turned on.
	// 2. enemies attack player if close enough.
	void tick();
	// let the player attack the enemy indicated by direction.
	// report an error if no enemy is located at the specified direction.
	void attack_enemy(Direction direction);
	// let the player consume the potion indicated by direction.
	// report an error if no potion is located at the specified direction.
	void consume_potion(Direction direction);
};

#endif // !FLOOR_H
