#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
public:
    Player(int, int); // these parameters are just for the position
    int chestOpen = 1; // i already set the chest to have health and i cant be bothered to change it so i just made opening it run on a damage system where you go decrease the chests health to 0 and then it opens ths chest
    int startBattle = 1;
    int startPuzzle = 1;
};

#endif
