#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <string>

class Enemy : public Character
{
public:
    Enemy(int hit_points, int att_power, int magic_energy, std::string (type));
    void attack(Character& player);
    int spell(Character& player);
    ~Enemy(); // Unused for now
};            //https://www.tutorialspoint.com/cplusplus/cpp_constructor_destructor.htm

#endif // ENEMY_H

