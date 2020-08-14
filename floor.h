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

	// helper function for constructor.
	// modify potion_list and text_display.
	void select_potion(int row, int col);
	// helper function for constructor.
	// modify gold_list and text_display.
	void select_gold(int row, int col);
	// helper function for constructor.
	// modify enemy_list and text_display.
	void select_enemy(int row, int col);

public:
	// constructor.
	// responsible for generating enemies, potions, and gold piles.
	Floor(std::vector<std::vector<char>> &text_display,
		  std::shared_ptr<Player> player,
		  std::vector<std::vector<std::pair<int, int>>> &availables,
		  int potion_num, int gold_num, int enemy_num);

	Floor(std::vector<std::vector<char>> &text_display,
		  std::shared_ptr<Player> player,
		  std::vector<std::shared_ptr<Enemy>> enemy_list,
		  std::vector<std::shared_ptr<Potion>> potion_list,
		  std::vector<std::shared_ptr<Gold>> gold_list,
		  std::vector<std::vector<std::pair<int, int>>> &availables,
		  int enemy_num);

	// accessor.
	std::vector<std::vector<char>> getTextDisplay();

	// enemies notify floor when they are slain.
	void beNotifiedBy(Enemy &e);

	// turn on/off enemy random moves.
	void ERMSwitch();

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
