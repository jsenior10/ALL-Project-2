#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include "entity.h"

class Puzzle : public Entity 
{
    private:
    Puzzle(int, int, int);
    question();
};

#endif
