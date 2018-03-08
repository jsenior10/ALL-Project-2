#ifndef CHEST_H
#define CHEST_H
#include "entity.h"
#include <vector>
class Chest : Entity{
    public:
<<<<<<< HEAD
    bool isOpen;
    Chest(int, int);
=======
    
    int xPos;
    int yPos;
    int Health;
    int maxHealth;
    bool isOpen;
    
    private:
    
    int box(int,int,int,int);
	int puzzle(int,int,int,int);
>>>>>>> 4a9044d519534e63e289cfab76d5fbde129de4a6
};

#endif