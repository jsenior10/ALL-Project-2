#ifndef CHEST_H
#define CHEST_H
#include "entity.h"
#include <vector>
class Puzzle : Entity{
    public:
    bool encountered;
    Puzzle(int,int);
};
#endif