#include <string>
#include "mainchar.h"
#include "enemy.h"


int random(int a);

// Check if dead
template <class T>
int dead_check(T& thing);


template <>
int dead_check<>(MainChar& player);

// Get probability of spell
int spellProb(Enemy foe);
void battle(MainChar& player, Enemy& foe);
