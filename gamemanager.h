#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "mainchar.h"
#include "enemy.h"

class GameManager
{
    // Constructor will execute setup and also the main game loop
    public:
        GameManager();
    bool chooseToStart();
    void gameLoop();

    // Event methods
    void enemyEvent();
    void trapEvent();
    void restEvent();
    void healEvent();

    // ----- Data members ------ //

    // Main character
    int start_hp;
    int start_att;
    int start_magic;
    MainChar* player;

    //game set-up
    int steps_to_end;
    int steps_before_event;
    int r;                  //event determiner , variable for random()
    int event_bit;         //1 - event occurs; 0 - it does not
    std::string answer;   //yes/no input

    // Enemy data
    Enemy *foe;
    int levelSelector;       //determines enemy level (0 - weak, 1 - strong)
    int nameFinder;         //finds enemy name
    int statsFinder;       //finds enemy stats from enemy array
    std::string foeName;  //enemy name

     // trap  variables
    int trapSelector;    //determines which trap you find
    int eventSelector;  //determines whether you escape or not
};

#endif
