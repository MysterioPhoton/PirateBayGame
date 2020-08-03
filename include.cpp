#include <iostream>    // Reading 'help' file
#include <cstdlib>    // rand(), srand()
#include <windows.h> //Sleep()
#include <fstream>  // ifstream

#include "mainchar.h"
#include "enemy.h"
#include "include.h"

// ----- Extra functions ----- //

// return a random integer between 0 and a-1
int random(int a)
{
    return rand()%a;
}


// checks if enemy has died
// http://www.cplusplus.com/doc/oldtutorial/templates/
// class can have members that use template parameters as types
template <class T>
int dead_check(T& thing)
{
    if(thing.hp<=0)
    {
        Sleep(1000);
        std::cout << thing.name << " has been slaughtered." << std::endl << std::endl;
        return 1;
    }
    else
        return 0;

}

// checks if user has died
// https://isocpp.org/wiki/faq/templates
// template specialization for any datatype
   /* template<>
      void foo(const T& x)*/

template <>
int dead_check<>(MainChar& player)
{
    if( player.hp <= 0 )
    {
        Sleep(1000);
        std::cout << "You have died!\n" << std::endl;
        std::cout << R"(

.|''|,  '''|.  '||),,(|,  .|''|,    .|''|, \\  // .|''|, '||''|
||  || .|''||   || || ||  ||..||    ||  ||  \\//  ||..||  ||
`|..|| `|..||. .||    ||. `|...     `|..|'   \/   `|...  .||.
    ||
 `..|'
                                                                )" <<std::endl<<std::endl ;
        //ascii art from <http://asciiflow.com/>
        Sleep(1000);
        return 1;
    }
    else
        return 0;

}

// probability of an enemy attempting to cast a spell
int spellProb(Enemy foe)
{
    //probability of casting a spell is 1/prob
    //probability of a non-magic enemy casting a spell
    int prob=100;

    if( foe.name == "skeleton" )
        prob = foe.hp;

    else if( ( foe.name=="magic carpet" ) || ( foe.name == "possessed corpse" ) )
        prob = 1;

    else if( foe.name == "mad warlock" )
        prob = 16 - foe.hp;

    return prob;
}

//battle event
void battle(MainChar& player, Enemy& foe)
{
    int foeChoice = 0;
    // Loops until one battler is defeated
    while( ( foe.hp > 0 ) && ( player.hp > 0 ) )
    {
        //--- Enemy turn ---//
        Sleep(1000);
        foeChoice = random( spellProb(foe) );
        if( (foeChoice == 0) )               //if the enemy casts a spell
        {
            if( (foe.spell(player) == 1) ) //spell function is called if it can be casted
                                          // 1 indicates spell not been cast
                foe.attack(player);      //if no spell, player is attacked
        }
        else
            foe.attack(player);


        //--- Player turn ----//

        Sleep(1000);
        if(player.hp>0)
        {
            std::cout << "_______________________________________________________________________________________"<<std::endl;
            std::cout << player.name << " :hit points " << player.hp << "|att. power " << player.att_pow << "|magic points " << player.magic << std::endl;
            std::cout << foe.name << " :" << foe.hp << " hit points remaining." << std::endl;
            std::cout << "_______________________________________________________________________________________"<<std::endl;

            Sleep(1500);
            std::cout << "What will you do?" << std::endl;
            Sleep(2000);
            std::cout << "Choose: 'attack', 'bolt' or 'heal'." << std::endl;
            std::cout << "Type 'help' if you need the rules of combat explained.\n" << std::endl;
            std::string choice = "";

            // get the player's choice of action
            while( (choice != "attack") && (choice != "bolt") && (choice != "heal") )
            {
                std::cout << ">>";
                std::cin >> choice;
                std::cout << std::endl;
                if(choice == "help")
                {

                    std::string line;
                    std::ifstream help("help.txt");
                    while( getline(help, line) )
                    {
                        std::cout << line << std::endl;
                    }
                    std::cout << std::endl;
                    help.close();
                }


                if( ( choice != "attack" ) && ( choice != "bolt" ) && ( choice != "heal" ) )
                    std::cout << "Please choose 'attack', 'bolt' or 'heal'." << std::endl;
            }


            if(choice == "attack")
                player.attack(foe);

            if(choice == "bolt")
                player.bolt_spell(foe);

            if(choice == "heal")
                player.heal_spell();

        }
    }

    // ending the fight
    if(dead_check(foe) == 1)
        return;

    // dead_check for player happens in main loop
    // so we don't need to call it here
    if(player.hp <= 0)
        return;

}


