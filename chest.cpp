#include <iostream>
#include <vector>
#include "libsqlite.hpp"
#include "utils.h"
#include "chest.h"

Chest::Chest(int x, int y, int HP) {
    xPos = x;
    yPos = y;
    currentHealth = HP;
}

int smallHealthUpgrade(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET maxHealth=maxHealth+5 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
}

int healthUpgrade(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET maxHealth=maxHealth+10 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
}

int gold20(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+20 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
}

int gold40(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+40 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
}

int gold70(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+70 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
}

int gold100(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+100 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
}

bool Chest::openTheChest(){
    sqlite::sqlite db("dungeonCrawler.db"); //opens database connection
    auto cur = db.get_statement();
    int numOfPowerups = 6;
    
    srand(time(0));
    int randPowerup = rand() % numOfPowerups + 1;
    
    cur-> set_sql("SELECT * FROM powerups WHERE num=?");
    cur-> prepare();
    cur->bind(1,randPowerup);
    cur->step();
    
    string powerupName = cur->get_text(1);
    std::cout << "You found " << powerupName;
}
