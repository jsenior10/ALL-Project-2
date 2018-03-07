#ifndef CHEST_H
#define CHEST_H
#include <vector>
class Chest {
    public:
    int xPos;
    int yPos;
    int Health;
    int maxHealth;
    bool isOpen;
    Chest(int, int, int, int);
	puzzle(int,int,int,int);
};
#endif