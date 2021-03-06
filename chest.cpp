#include <iostream>
#include <vector>
#include "libsqlite.hpp"
#include "chest.h"
#include "global.h"

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
    std::cout << "You found a small health upgrade! Health increased by 5.";
}

int healthUpgrade(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET maxHealth=maxHealth+10 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
        std::cout << "You found a health upgrade! Health increased by 10.";
}

int gold20(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+20 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
    std::cout << "You found 20 gold";
}

int gold40(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+40 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
    std::cout << "You found 40 gold";
}

int gold70(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+70 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
    std::cout << "You found 70 gold";
}

int gold100(sqlite::sqlite &db){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+100 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,2); //change by global variable here
    cur2->step();
    return 0;
    std::cout << "You found 100 gold";
}

int Chest::openTheChest(){
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

    
    if (randPowerup == 1){
        
    }
    
    if (randPowerup == 2){
        
    }
    
    if (randPowerup == 3){

    }
    
    if (randPowerup == 4){

    }
    
    if (randPowerup == 5){

    }
    
    if (randPowerup == 6){

    }
    return 0;
}
