#include <iostream>
#include <vector>
#include "utils.h"
#include "chest.h"

Chest::box(int x, int y, int HP, int max) {
    xPos = x;
    yPos = y;
    Health = HP;
    maxHealth = max;
};

Chest::puzzle(int x,int y,int HP, int max)
{
	xPos = x;
    yPos = y;
    Health = HP;
    maxHealth = max;
};