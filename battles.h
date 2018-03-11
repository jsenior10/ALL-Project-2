#ifndef BATTLES_H
#define BATTLES_H
#include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
#include "battleScenario.h"
#include <unistd.h> 
class Battles{
	
    public:
    int startBattle();
    int idUser;
    int idMonster;
    void printWeapons();
    void printMonsterStatus(int);
    int setUserVariables();
    int monsterAttack();
};
#endif
