#include "gamemanager.h"
#include "variables.h"
#include "include.h"
#include "mainchar.h"
#include "enemy.h"

#include <iostream>
#include <fstream>    //for reading text files
#include <windows.h> //Sleep()
#include <ctime>    //time() for srand()


using namespace std;

 // Constructor to set up game and enter game loop
GameManager::GameManager()
{

      //If the sequence for random remains the same,
     //numbers will be repeated for each run of the program.
    //The game will execute the same way each time.
   //By using  srand(time(0)), we use computers internal clock.
  //The time is continually changing. Therefore, the sequence is unique each time.
 //https://mathbits.com/MathBits/CompSci/LibraryFunc/rand.htm

    srand( (unsigned) time(0) );

    // See if player wants to start game
    if ( !chooseToStart() )
      return;



    // ----- data members ----- //

    // Player variables
    start_hp = 25;
    start_att = 10;
    start_magic = 5;
    player = new MainChar(start_hp, start_att, start_magic, "");

    // Game variables
    steps_to_end = 20;
    steps_before_event = 0;
    r = 1;
    event_bit = 1;
    answer = "";

    //enemy pointer
    foe = 0;

    // Enemy-related variables
    levelSelector = 0;
    nameFinder = 0;
    statsFinder = 0;
    foeName = "";

    // trap-related variables
    trapSelector = 0;
    eventSelector = 0;


    //display initial stats
    Sleep(2000);
    cout << "\n____________________________________________________________________________________" <<endl;
    cout << "You are " << steps_to_end << " steps away from the treasure." << endl;
    cout << "Initial stats: " << endl ;
    cout << start_hp << " hit points | " << start_att << " attacking power | "<< start_magic << " magic points." <<endl;
    cout << "____________________________________________________________________________________" <<endl;
    cout << "Good luck!\n" << endl;

    gameLoop();

    return;
};

// start the game on user consent
bool GameManager::chooseToStart()
{

    string line;
    ifstream intro("intro.txt");

    while(getline(intro, line))
       {cout << line << endl;
       }

    intro.close();


    Sleep(2000);
    cout << "\n\n\nWill you?" << endl;
    cout << ">>" ;

    string play_bit;
    while( (play_bit != "yes" ) && ( play_bit != "no" ) )
    {
        cin >> play_bit;
        if( (play_bit != "yes" ) && ( play_bit != "no" ) )
            cout << "Answer 'yes' or 'no'." << endl;
    }


    if( play_bit == "no" )
    {
        cout << "Never mind .";
        Sleep(500);
        return false;
    }

    // play_bit = 'yes'
    return true;
};



// ----- Event Methods ----- //

void GameManager::enemyEvent()
{
    Sleep(2000);
    cout << "___" << endl;
    cout << "*You walk " << steps_before_event << " steps" << endl;
    statsFinder = random(5); //default setting for a weak enemy

    //chance of getting strong enemy - 1/4
    levelSelector = random(4);
    if( levelSelector == 1 )
    {
        statsFinder = random(4);
        nameFinder = 1;
    }


    Sleep(1000);

    // Strong enemy case
    if( nameFinder == 1 )
    {
        // Get enemy data and start combat
        foeName = strong_enemy_names[statsFinder];
        foe = new Enemy(strong_enemies[statsFinder][0], strong_enemies[statsFinder][1], strong_enemies[statsFinder][2], foeName);
        battle(*player, *foe);
        delete foe;
    }

    // Weak enemy case
    if( nameFinder == 0 )
    {
        // Get enemy data and start combat
        foeName = weak_enemy_names[statsFinder];
        foe = new Enemy(weak_enemies[statsFinder][0], weak_enemies[statsFinder][1], weak_enemies[statsFinder][2], foeName);
        battle(*player, *foe);
        delete foe;
    }
    return;
};

void GameManager::trapEvent()
{
    Sleep(2000);
    cout << "___" << endl;
    cout << "*You walk " << steps_before_event << " steps." << endl;
    cout << "Something doesn't feel right..." << endl;
    trapSelector = random(4); //chooses trap
    Sleep(1000);


    cout << "It's a trap!" << endl << traps[trapSelector] << endl;
    eventSelector = random( trap_stats[trapSelector][1] ); //random probability
    Sleep(1000);

    // Trap triggered
    if( eventSelector == 0 )
    {
        cout << trap_events[trapSelector][1] ;
        cout << " You lose " << min(trap_stats[trapSelector][0], player->hp) << " hit points." << endl;
        player->hp -= min( trap_stats[trapSelector][0], player->hp );
        //min = return trap_stats < current_hp ? trap_stats : current_hp
        //loose hp saved in array , else if lower ; loose all current hp
        //http://www.cplusplus.com/reference/algorithm/min/
        //assign the local variable value to the data members in line 180
        //https://beginnersbook.com/2017/08/cpp-this-pointer/
    }

    // Trap avoided
    else

        cout << trap_events[trapSelector][0] << endl;

    cout << endl;
    return;
};

void GameManager::restEvent()
{
    Sleep(2000);
    cout << "___" << endl;
    cout << "*You walk " << steps_before_event << " steps" << endl;
    Sleep(1000);

    string line;
    ifstream intro("rest.txt");

    while(getline(intro, line))
       {cout << line << endl;
       }

    intro.close();

    Sleep(500);
    cout << "\nWill you like to take rest?" << endl;
    cout << ">>";
    cin  >> answer;

    cout << endl ;
    while( ( answer != "yes" ) && ( answer!="no" ) )
    {
        cout << "Answer 'yes' or 'no'." << endl;
        cout << ">>";
        cin >> answer;
    }

    // take rest
    if( answer == "yes" )
    {
        cout << "You take rest inside the cave, recovering from previous battles." << endl;
        cout << "You notice that the object has now disappeared." << endl;
        cout << "You heal " << min(10, player->hp_init - player->hp) << " hit points." << endl << endl;
        player->hp += min(10, player->hp_init - player->hp);
        //increase hp by 10
        //else if 10>current hp , increase the hp you lost (initial hp - current hp)
    }

    // no rest
    if( answer == "no" )
    {
        // special item
        cout << "You walk away and collect the object ahead of you. It's a sword" << endl;
        cout << "You change your weapon from blade to a sword.\n";
        cout << "Your attack power increases by 1.\n" << endl ;
        player->att_pow++;
    }
    return;
};

void GameManager::healEvent()
{
    Sleep(2000);
    cout << "___" << endl;
    cout << "*You walk " << steps_before_event << " steps" << endl;
    Sleep(1000);

    string line;
    ifstream intro("heal.txt");

    while(getline(intro, line))
       {cout << line << endl;
       }

    cout << "Will you eat the apple?" << endl;
    cout << ">>";
    cin  >> answer;

    cout << endl ;
    while( ( answer != "yes" ) && ( answer != "no" ) )
    {
        cout << "Answer 'yes' or 'no'." << endl;
        cout << ">>";
        cin  >> answer;
    }
    Sleep(500);

    // eat
    if( answer == "yes" )
    {
        // Randomly decide the effect
        int heal_choice=random(2);

        // Bitter
        if( heal_choice == 0 )
        {
            cout << "The apple tastes bitter. It seems to be draining your very life force." << endl;
            cout << "You lose " << min(6, player->hp) << " hit points." << endl << endl;
            player->hp -= min(6, player->hp);
            //mius 6 hp
            //if lower than 6 , minus all
        }
        // Sweet
        else
        {
            cout << "The apple tastes sweet. You feel raw magical power surging through your veins." << endl;
            cout << "You gain 2 magic points." << endl << endl;
            player->magic += 2;
        }
    }

    // apple not eaten
    else
        cout << "You leave the tree behind."<< endl << endl;

    return;
};




// The game loop itself
// Uses r to determine randomly what events occur at a given step
void GameManager::gameLoop()
{
    while( ( steps_to_end > 0 ) && ( dead_check(*player) == 0 ) )
    {
        answer = "";
        event_bit = 1;   //assumes something happens, unless we go to default case
        r = random(21); //determines what event happens

        if( r <= 4 )
            r = 0;    //case 0 means case <= 4

        switch(r)
        {
            // enemy event
            case 0:
                enemyEvent();
                break;

            //trap event
            case 5:
                trapEvent();
                break;

            //rest event
            case 6:
                restEvent();
                break;

            //heal event
            case 7:
                healEvent();
                break;

            //walk forward (no event)
            default:
                event_bit = 0;
                steps_to_end--;
                steps_before_event++;
                break;

            }

        // to Check if game will continue after an event has occurred
        if( ( event_bit == 1 ) && ( player->hp > 0 ) )
        {
            Sleep(1000);
            cout <<'\t'<<"--The treasure is " << steps_to_end << " steps away.--" << endl << endl;
            steps_to_end--;
            steps_before_event = 1;
        }
    }

    // Ending
    // Check if player won
    if( ( steps_to_end <= 0 ) && ( player->hp > 0 ) )
    {
        Sleep(2000);
        cout << "___" << endl;
        cout << "*You walk " << steps_before_event << " steps" << endl;
        Sleep(1000);

       string line;
       ifstream intro("end.txt");
       while(getline(intro, line))
         {cout << line << endl;
         }

        Sleep(1000);
        cout << "\nCongratulations, " << player->name <<" you have won the game." << endl;
    }
    return;
};


//https://www.asciiart.eu/
//http://asciiflow.com/
