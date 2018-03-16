#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include "libsqlite.hpp"
#include "puzzle.h"
#include "global.h"
#include "battles.h"

Puzzle::Puzzle(int x, int y, int HP) 
{
    xPos = x;
    yPos = y;
    currentHealth = HP;
}
