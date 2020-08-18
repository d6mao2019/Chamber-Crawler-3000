#ifndef FLOOR_H
#define FLOOR_H
#include <memory>
#include <vector>

enum class Direction;
class Player;
class Enemy;
class Potion;
class Gold;

class Floor
{
	std::vector<std::vector<char>> text_display;
	std::vector<std::shared_ptr<Enemy>> enemy_list;
	std::vector<std::shared_ptr<Potion>> potion_list;
	std::vector<std::shared_ptr<Gold>> gold_list;
	std::shared_ptr<Player> player;
	bool ERM = 1; // enemy random move controller.

	// helper function for constructor.
	// modify potion_list and text_display.
	void select_potion(int row, int col);
	// helper function for constructor.
	// modify gold_list and possibly enemy_list. modify text_display.
	void select_gold(int row, int col, std::vector<std::pair<int, int>> &avialables);
	// helper function for constructor.
	// modify enemy_list and text_display.
	void select_enemy(int row, int col);

public:
	// constructor: does nothing.
	Floor();
	// constructor: read in locations of characters and items from input.
	Floor(std::vector<std::vector<char>> &text_display,
		  std::vector<std::shared_ptr<Enemy>> enemy_list,
		  std::vector<std::shared_ptr<Potion>> potion_list,
		  std::vector<std::shared_ptr<Gold>> gold_list,
		  std::shared_ptr<Player> player,
		  std::vector<std::vector<std::pair<int, int>>> &availables);
	// constructor: randomly spawn enemies, potions, and golds.
	Floor(std::vector<std::vector<char>> &text_display,
		  std::shared_ptr<Player> player,
		  std::vector<std::vector<std::pair<int, int>>> availables,
		  int potion_num, int gold_num, int enemy_num);
	// copy constructor.
	Floor(const Floor &other);
	// copy assignment operator.
	void operator=(const Floor &other);

	std::vector<std::vector<char>> getTextDisplay() const;
	bool getERM() const;
	std::shared_ptr<Player> getPlayer() const;

	// turn on/off enemy random moves.
	void ERMSwitch();

	// tick does two things.
	// 1. enemies move randomly if ERM is turned on.
	// 2. enemies attack player if close enough.
	void tick();

	// moves the player on the map.
	bool move_player(Direction direction);

	// let the player attack the enemy indicated by direction.
	// report an error if no enemy is located at the specified direction.
	void attack_enemy(Direction direction);

	// let the player consume the potion indicated by direction.
	// report an error if no potion is located at the specified direction.
	void consume_potion(Direction direction);

	// let the player pick up the gold indicated by direction.
	// report an error if the gold is a dragon hoard whose dragon has not been slain yet.
	void pick_up_gold(Direction direction);
};

std::ostream &operator<<(std::ostream &out, const Floor &f);

#endif // !FLOOR_H
