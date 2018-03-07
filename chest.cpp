#include <iostream>
#include <vector>
#include "utils.h"
#include "chest.h"

int Chest::Chest(int x, int y, int HP, int max) {
    xPos = x;
    yPos = y;
    Health = HP;
    maxHealth = max;
};

int Chest::puzzle(int x,int y,int HP, int max)
{
	xPos = x;
    yPos = y;
    Health = HP;
    maxHealth = max;
};