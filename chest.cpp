#include <iostream>
#include <vector>
#include "utils.h"
#include "chest.h"

Chest::Chest(int x, int y, int HP) {
    xPos = x;
    yPos = y;
    currentHealth = HP;
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
    
    cur->set_sql("SELECT COUNT(idPowerup) FROM powerups");
    cur->prepare();
    cur->step();
    int numOfPowerups = cur->get_int(0);
    srand(time(0));
    int idPowerup = rand() % numOfPowerups + 1;
    cur2-> set
}
