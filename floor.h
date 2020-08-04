#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
class Enemy;
class Item;

class Floor {
	std::vector<std::vector<char>> textDisplay;
	std::vector<std::shared_ptr<Enemy>> enemy_list;
	std::vector<std::shared_ptr<Item>> item_list;

public:
	Floor();// responsible for generating chambers and enemies.
	void beNotifiedBy(Enemy& e);
};

#endif // !FLOOR_H
