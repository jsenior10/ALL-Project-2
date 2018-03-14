#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <unistd.h> 
#include "entity.h"

class Puzzle : public Entity 
{
    public:
    Puzzle(int, int, int);
    bool question();
};

#endif
