#include <iostream>
#include <vector>
#include "enemy.h"

Enemy::Enemy(int x, int y, int HP) {
    xPos = x;
    yPos = y;
    currentHealth = HP;
}
