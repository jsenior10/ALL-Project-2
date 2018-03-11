#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

using namespace std;

class Entity { // this is the enitity properties like enemy position etc
public:
    int xPos;
    int yPos;
    int currentHealth;
    int maxHealth;
    bool isDead = false; // this will also be used for when a chest opens or something to avoid redundant variables
    
    void hasInteracted(int);
};

#endif
