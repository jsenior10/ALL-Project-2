#include <iostream>
#include <vector>
#include "utils.h"
#include "chest.h"

Chest::Chest(int x, int y, int HP, int max) {
    xPos = x;
    yPos = y;
    Health = HP;
    maxHealth = max;
};