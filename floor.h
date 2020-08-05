#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
class Enemy;
class Potion;
class Gold;

class Floor {
	std::vector<std::vector<char>> textDisplay;
	std::vector<std::shared_ptr<Enemy>> enemy_list;
	std::vector<std::shared_ptr<Potion>> potion_list;
	std::vector<std::shared_ptr<Gold>> gold_list;

public:
	Floor();// responsible for generating chambers and enemies.
	void beNotifiedBy(Enemy& e);
	void tick();
	void consume();
};

#endif // !FLOOR_H
