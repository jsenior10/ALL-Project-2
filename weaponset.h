#ifndef WEAPONSET_H
#define WEAPONSET_H
#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;
class Weapons{
    public:
    int idUser;
    bool assignWeapon(int weapon, sqlite::sqlite &db);
    void printWeapons(sqlite::sqlite &db);       
};
#endif