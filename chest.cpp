#include <iostream>
#include <vector>
#include "utils.h"
#include "chest.h"

Chest::Chest(int x, int y, int HP) {
    xPos = x;
    yPos = y;
    currentHealth = HP;
}
