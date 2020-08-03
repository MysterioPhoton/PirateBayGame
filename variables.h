

//weak enemies (level 0)
int weak_enemies[4][3] = { // {hit point , attack power, magic points}
                           {2,3,1},
                           {5,3,0},
                           {4,3,3},
                           {7,4,0}
                          };

std::string weak_enemy_names[4]= {"skeleton",
                                  "giant rat",
                                  "possessed corpse",
                                  "magic carpet"
                                 };

//strong enemies (level 1)
int strong_enemies[4][3] = { // {hit point , attack power, magic points}
                            {6,8,0},
                            {8,2,3},
                            {14,5,1},
                            {8,8,0}
                           };

std::string strong_enemy_names[4]= {"huge spider",
                                    "mad warlock",
                                    "goblin",
                                    "big venomous snake"
                                   };



//traps
std::string traps[4]= {"You are sinking into the sand!",
                       "You are teetering on the edge of a deep pit!",
                       "An arrow is whizzing towards you!",
                       "You are struck by lightening!"
                      };

int trap_stats[4][2] = { // {damage, probability }
                         {2,2},
                         {5,2},
                         {7,3},
                         {10,3}
                       };

std::string trap_events[4][2]=  // {avoid trap , fall into}
{
    {"You crawl out of it using all your might.","You fail to escape and get sucked into it."},
    {"You manage to regain your balance and escape unharmed.","You fall into the dark pit and thud against the ground."},
    {"You duck, narrowly avoiding the missile.","The arrow strikes you, creating a deep wound."},
    {"You move away from the strike. You are unharmed.","You don't move away  in time , you are burnt to a crisp."}
};

