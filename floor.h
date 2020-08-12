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
	std::vector<std::vector<char>> textDisplay;
	std::vector<std::shared_ptr<Enemy>> enemy_list;
	std::vector<std::shared_ptr<Potion>> potion_list;
	std::vector<std::shared_ptr<Gold>> gold_list;
	std::shared_ptr<Player> player;

public:
	Floor();					 // responsible for generating chambers and enemies.
	void beNotifiedBy(Enemy &e); // enemies notify floor when they are slain.
	void tick();				 // random move of enemies.
	void consume();
};

#endif // !FLOOR_H
