#include "floor.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include <cstdlib>
#include <stdexcept>

std::vector<std::vector<std::pair<int, int>>> Floor::find_locations(int enemy_num, int potion_num, int gold_num)
{
    std::vector<std::pair<int, int>> enemies;
    std::vector<std::pair<int, int>> potions;
    std::vector<std::pair<int, int>> golds;
    std::vector<std::vector<std::pair<int, int>>> result{enemies, potions, golds};
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
    int remaining = all.size();
    enemy_num = (enemy_num <= remaining) ? enemy_num : remaining;
    remaining = remaining - enemy_num;
    for (int i = 0; i < enemy_num; ++i)
    {
        int rest = all.size() - i;
        int j = rand() % rest + i;
        std::swap(all[i], all[j]);
        result[0].push_back(all[i]);
    }
    potion_num = (potion_num <= remaining) ? potion_num : remaining;
    remaining = remaining - potion_num;
    for (int i = enemy_num; i < enemy_num + potion_num; ++i)
    {
        int rest = all.size() - i;
        int j = rand() % rest + i;
        std::swap(all[i], all[j]);
        result[1].push_back(all[i]);
    }
    gold_num = (gold_num <= remaining) ? gold_num : remaining;
    for (int i = enemy_num + potion_num; i < enemy_num + potion_num + gold_num; ++i)
    {
        int rest = all.size() - i;
        int j = rand() % rest + i;
        std::swap(all[i], all[j]);
        result[2].push_back(all[i]);
    }
    return result;
}

void Floor::generate_enemies(std::vector<std::pair<int, int>> &locations)
{
    for (int i = 0; i < locations.size(); ++i)
    {
        int type = rand() % 18;
        if (0 <= type && type < 4) // human.
        {
            auto e = std::make_shared<Human>(locations[i].first, locations[i].second);
            enemy_list.push_back(e);
            text_display[locations[i].first][locations[i].second] = 'H';
        }
        if (4 <= type && type < 7) // dwarf.
        {
            auto e = std::make_shared<Dwarf>(locations[i].first, locations[i].second);
            enemy_list.push_back(e);
            text_display[locations[i].first][locations[i].second] = 'W';
        }
        if (7 <= type && type < 12) // halfling.
        {
            auto e = std::make_shared<Halfling>(locations[i].first, locations[i].second);
            enemy_list.push_back(e);
            text_display[locations[i].first][locations[i].second] = 'L';
        }
        if (12 <= type && type < 14) // elf.
        {
            auto e = std::make_shared<Elf>(locations[i].first, locations[i].second);
            enemy_list.push_back(e);
            text_display[locations[i].first][locations[i].second] = 'E';
        }
        if (14 <= type && type < 16) // orc.
        {
            auto e = std::make_shared<Orc>(locations[i].first, locations[i].second);
            enemy_list.push_back(e);
            text_display[locations[i].first][locations[i].second] = 'O';
        }
        if (16 <= type && type < 18) // merchant.
        {
            auto e = std::make_shared<Merchant>(locations[i].first, locations[i].second);
            enemy_list.push_back(e);
            text_display[locations[i].first][locations[i].second] = 'M';
        }
    }
}

// constructor.
Floor::Floor(int enemy_num, int potion_num, int gold_num)
{
    // text display.
    // how to generate initial text display???
    // a note: should place player before placing other things on the floor.
    auto locations = find_locations(enemy_num, potion_num, gold_num);
    generate_enemies(locations[0]);
    generate_potions(locations[1]);
    generate_golds(locations[2]);
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
