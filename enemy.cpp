#include "enemy.h"
#include <cstdlib> //https://en.cppreference.com/w/cpp/header/cstdlib
                   //https://www.programiz.com/cpp-programming/library-function/cstdlib
#include <iostream>
using namespace std;

// Enemy constructor will initialise relevant data members
// and tell the player that the enemy blocks their way
Enemy::Enemy( int hit_points, int att_power, int magic_energy, string (type) )
    :Character(hit_points, att_power, magic_energy, type)
{
    if( name != "" )
    {
        cout << "A " << name << " blocks your way." << endl << endl;
    }
}

// Attack function
void Enemy::attack(Character& player)
{
    cout << "The " << name << " attacks!" << endl;
    cout << "You lose " << min(att_pow, player.hp) << " hit points." << endl << endl;
    player.hp -= min(att_pow, player.hp);
}

// Gets enemy spell and casts it
int Enemy::spell(Character& player)
{
    // Cast unsuccesful
    if( magic == 0 )
    {
        cout << "The " << name << " attempts to cast a spell, but fails!" << endl << endl;
        return 1; // Spell has failed to cast
    }

    // Spell successfully cast
    cout << "The " << name << " casts a spell!" << endl;

    // Different enemies have different spells
    if( name == "skeleton" )
    {
        cout << "The skeleton rebuilds itself, healing all of the damage it has taken." << endl << endl;
        hp = 11;
        magic--;
        return 0;
    }
    if( name == "magic carpet" )
    {
        cout << "The carpet wraps itself around your body.\n";
        cout << "You lose " << min(6,player.hp) << " hit points.\n" << endl;
        player.hp -= min(6, player.hp);
        magic--;
        return 0;
    }
    if( name=="mad warlock" )
    {
        cout << "The warlock summons flames at you." << endl;
        cout << "You lose " << min(6, player.hp) << " hit points.\n";
        cout << "The flames damage your weapon, reducing your attack power by 1." << endl << endl;
        player.hp -= min(6, player.hp);
        player.att_pow--;
        magic--;
        return 0;
    }

    if( name == "possessed corpse" )
    {
        cout << "It casts a spell on itself, doubling its attack power." << endl << endl;
        att_pow *= 2;
        magic--;
        return 0;
    }

    // If no spell was cast
    return 1;
}
Enemy::~Enemy() {}
