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
	// determine which spot is still available (empty) and randome select num from them.
	// remain silent if num < availables.size().
	std::vector<std::vector<std::pair<int, int>>> choose_locations(int enemy_num, int potion_num, int gold_num);
	// helper function for constructor.
	// modify enemy_list and text_display.
	void generate_enemies(std::vector<std::pair<int, int>> &locations);
	// helper function for constructor.
	// modify potion_list and text_display.
	void generate_potions(std::vector<std::pair<int, int>> &locations);
	// helper function for constructor.
	// modify gold_list and text_display.
	void generate_golds(std::vector<std::pair<int, int>> &locations);

public:
	// constructor.
	// responsible for generating enemies, potions, and gold piles.
	Floor(int enemy_num, int potion_num, int gold_num);

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
