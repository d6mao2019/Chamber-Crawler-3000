#include "floor.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include <cstdlib>
#include <stdexcept>

// helper.
// determine which spot is still available (empty) and randome select num from them.
// remain silent if num < availables.size().
std::vector<std::pair<int, int>> generate_locations(std::vector<std::vector<char>> &text_display, int num)
{
    std::vector<std::pair<int, int>> result;
    /* get all locations. */
    std::vector<std::pair<int, int>> all;
    for (int i = 0; i < text_display.size(); ++i)
    {
        for (int j = 0; j < text_display[i].size(); ++j)
        {
            if (text_display[i][j] == '.')
                all.emplace_back(i, j);
        }
    }
    /* random select. */
    num = (num <= all.size()) ? num : all.size();
    for (int i = 0; i < num; ++i)
    {
        int rest = num - 1;
        int j = rand() % rest + i;
        std::swap(all[i], all[j]);
        result.push_back(all[i]);
    }
    return result;
}
// helper.
std::vector<std::shared_ptr<Enemy>> generate_enemies(std::vector<std::vector<char>> &text_display, int num)
{
    std::vector<std::pair<int, int>> locations = generate_locations(text_display, num);
    std::vector<std::shared_ptr<Enemy>> result;
    for (int i = 0; i < locations.size(); ++i)
    {
        int type = rand() % 18;
        if (0 <= type && type < 4) // human.
        {
            auto e = std::make_shared<Human>(locations[i].first, locations[i].second);
            result.push_back(e);
        }
        if (4 <= type && type < 7) // dwarf.
        {
            auto e = std::make_shared<Dwarf>(locations[i].first, locations[i].second);
            result.push_back(e);
        }
        if (7 <= type && type < 12) // halfling.
        {
            auto e = std::make_shared<Halfling>(locations[i].first, locations[i].second);
            result.push_back(e);
        }
        if (12 <= type && type < 14) // elf.
        {
            auto e = std::make_shared<Elf>(locations[i].first, locations[i].second);
            result.push_back(e);
        }
        if (14 <= type && type < 16) // orc.
        {
            auto e = std::make_shared<Orc>(locations[i].first, locations[i].second);
            result.push_back(e);
        }
        if (16 <= type && type < 18) // merchant.
        {
            auto e = std::make_shared<Merchant>(locations[i].first, locations[i].second);
            result.push_back(e);
        }
    }
    return result;
}
Floor::Floor(int enemy_num, int positon_num, int gold_num)
{
    /* text_display */
    /* spawn enemies. */
    enemy_list = generate_enemies(text_display, enemy_num);
    /* spawn potions. */
    for (int i = 0; i < positon_num; ++i)
    {
    }
    /* spawn gold piles. */
    for (int i = 0; i < gold_num; ++i)
    {
    }
}

std::vector<std::vector<char>> Floor::getTextDisplay() { return text_display; }

void Floor::beNotifiedBy(Enemy &e)
{
    int original_size = enemy_list.size(); // debugging purpose.
    /* modify vector. */
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        if (**i == e)
            enemy_list.erase(i);
    }
    if (enemy_list.size() != original_size - 1) // debugging purpose.
        throw std::logic_error{"Bug: something wrong with the enemy list. added or removed improperly sometime."};
    /* modify text display. */
    text_display[e.getRow()][e.getCol()] = '.';
}

void Floor::ERMSwitch()
{
    if (ERM)
        ERM = false;
    else
        ERM = true;
}

std::vector<Direction> available_directions(std::shared_ptr<Enemy> e, std::vector<std::vector<char>> &text_display)
{
    std::vector<Direction> result;
    int row = e->getRow();
    int col = e->getCol();
    if (text_display[row - 1][col] == '.') // north.
        result.push_back(Direction::no);
    if (text_display[row + 1][col] == '.') // south.
        result.push_back(Direction::so);
    if (text_display[row][col - 1] == '.') // west.
        result.push_back(Direction::we);
    if (text_display[row][col + 1] == '.') // east.
        result.push_back(Direction::ea);
    if (text_display[row - 1][col - 1] == '.') // north west.
        result.push_back(Direction::nw);
    if (text_display[row - 1][col + 1] == '.') // north east.
        result.push_back(Direction::ne);
    if (text_display[row + 1][col - 1] == '.') // south west.
        result.push_back(Direction::sw);
    if (text_display[row + 1][col + 1] == '.') // south east.
        result.push_back(Direction::se);
    return result;
}

void Floor::tick()
{
    /* enemy randome moves. */
    if (ERM)
    {
        for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
        {
            std::vector<Direction> availables = available_directions(*i, text_display);
            Direction direction = availables[rand() % availables.size()];
            (*i)->move(direction);
        }
    }
    /* enemy attack player. */
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        player->beAttackedBy(**i);
    }
}

void Floor::attack_enemy(Direction direction)
{
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        (*i)->beAttackedBy(*player);
    }
}

void Floor::consume_potion(Direction direction)
{
    for (auto i = potion_list.begin(); i != potion_list.end(); ++i)
    {
    }
}
