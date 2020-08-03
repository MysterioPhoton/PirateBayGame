#include "mainchar.h"
#include <iostream>
#include <cstdlib>
#include <windows.h> //for Sleep()
using namespace std;

MainChar::MainChar(int hit_points, int att_power, int magic_energy, string type)
    :Character(hit_points,att_power,magic_energy,type)
{
    hp_init = hp;
    // Get player name

    cout << "\nWhat is your name, adventurer?" << endl;
    cout << ">>";
    cin  >> name;
    cout << "\nGreetings, " << name << "." << endl << endl;
    cout << "\t\t\t Welcome to " <<endl ;
    cout << R"(
 *******    **                          **                   ******
/**////**  //                          /**                  /*////**                 **   **
/**   /**   **   ******    ******     ******    *****       /*   /**     ******     //** **
/*******   /**  //**//*   //////**   ///**/    **///**      /******     //////**     //***
/**////    /**   /** /     *******     /**    /*******      /*//// **    *******      /**
/**        /**   /**      **////**     /**    /**////       /*    /**   **////**      **
/**        /**  /***     //********    //**   //******      /*******   //********    **
//         //   ///       ////////      //     //////       ///////     ////////    //
)" << '\n';


//https://stackoverflow.com/questions/37765925/ascii-art-in-c
//raw string literal starts with R”( and ends in )”.
//R is the return character; it tells terminal emulator to move the cursor at the start of the line.
}

void MainChar::bolt_spell(Character& foe)
{
    // Test if spell can be cast
    if(magic != 0)
    {
        cout << "You cast a fiery bolt of magical energy to hurl at your foe." << endl;
        cout << "The bolt does " << min(7, foe.hp) << " damage to the " << foe.name << "." << endl;

        // Update relevant data members
        foe.hp -= min(7, foe.hp);
        magic--;
    }

    // Spell not cast successfully
    else
        cout << "No magic points remaining!" << endl;

    cout << endl;
};



void MainChar::heal_spell()
{
    // Successful cast
    if(magic != 0)
    {
        cout << "You surround yourself with a mystical power, healing some damage." << endl;
        cout << "You heal " << min(10, hp_init-hp) << " hit points." << endl;
        hp += min(10, hp_init-hp);
        magic--;
    }

    // Failed cast
    else
        cout << "No magic points remaining!" << endl;

    cout << endl;
};

void MainChar::attack(Character& foe)
{
    int hit_bit = rand()%4; // determines whether critical hit happens
    int damage = att_pow;
    cout << "You attack the " << foe.name << "." << endl;
    Sleep(300);

    if( hit_bit == 0 )
    {
        damage += 2;
        cout << "You get a critical hit!" << endl;
    }

    cout << "Your attack does " << min(damage, foe.hp) << " damage." << endl;
    foe.hp -= damage;
    cout << endl;
}

MainChar::~MainChar() {}
