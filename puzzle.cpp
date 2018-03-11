#include <iostream>
#include <vector>
#include "utils.h"
#include "puzzle.h"

Puzzle::Puzzle(int x, int y, int HP) {
    xPos = x;
    yPos = y;
    currentHealth = HP;
}
