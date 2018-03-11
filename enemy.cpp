#include <iostream>
#include <vector>
#include "utils.h"
#include "enemy.h"

Enemy::Enemy(int x, int y, int HP) {
    xPos = x;
    yPos = y;
    currentHealth = HP;
}
