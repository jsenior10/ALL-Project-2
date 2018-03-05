 #include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
#include "battleScenario.h"
#include <ncurses.h>
#include <unistd.h> //for usleep stuff
using namespace std;
int waitAbit(int sec){
    usleep(sec * 1000000); //the parameter works in micro-seconds 
}

class Battles{
    public:
    int idMonster;
    int idUser;
    void printWeapons(){
        //function to print all the weapons the user has
        int counter = 2;
        sqlite::sqlite db( "dungeonCrawler.db" ); // open database
        auto cur = db.get_statement(); // create query
        //join query between weapon and weaponds_user
        cur->set_sql("SELECT w.type, w.damage, w.attack, wu.duration FROM weapon w, weapons_user wu  WHERE (idUser=? AND w.idWeapon = wu.idWeapon)"); 
        //  0-type. 1-damage. 2-attack. 3-duration from weapons_user. 
        cur->prepare();
        cur->bind(1,idUser);
        addstr("Your weapons:\n");
        cout<<"1- Punch"<<"   "<<"10%\n"<<endl;
        while(cur->step()){
            int totalDamage = cur->get_int(1)*cur->get_int(2);
            //example output weapon(duration) attack%
            cout<<counter<<"- "<<cur->get_text(0)<<"("<<cur->get_int(3)<<") "<<totalDamage<<"&"<<endl;
            counter = counter +1;
        }
        refresh();
    }
    int userAttack(int weaponToAttack){
        //function that receives the id of the weapon to attack
        
        return 0;
    }
    int monsterAttack(){
        return 0;
    }
};
int battle(int id_user, int id_monster, int id_weapon){
    //set the monsters and users variables
    sqlite::sqlite db("dungeonCrawler.db");//open database
    auto cur_battle = db.get_statement();//create query
    cur_battle->set_sql("SELECT u.maxHealth, u.armor, u.damage, u.attack, m.health, m.attack, m.counterAttack FROM users u, monsters m WHERE (u.idUser==? AND m.id_monster=?)");
    //0-user health . 1-user armor . 2-user damage . 3-user attack . 4-monster health . 5-monster attack . 6 . monster counterattack
    cur->prepare();
    cur->bind(1,id_user);
    cur->bind(2,id_monster);
    int user_health = cur->get_int(0);
    int user_health = cur->get_int(0);
    
}
int main(){
	sqlite::sqlite db("dungeonCrawler.db");//open database
	auto cur = db.get_statement();//create query
    auto cur2 = db.get_statement();
    srand(time(0));
    initscr();
    int something;
    addstr(" Wait until your opponent get ready \n");
    refresh();
    addstr("The opponent is cutting his nails");
    getch();
    addstr("Let's get started \n");
    refresh();
    getch();
    cur->set_sql("SELECT COUNT(idMonster) FROM monsters");//to get the number os monsters that exist
    cur->prepare();
    cur->step();
    int numOfMonsters = cur->get_int(0);
    int num = rand() % numOfMonsters + 1; //generate a number between 1-4
    if (num > 0){
        cur2->set_sql("SELECT * FROM monsters WHERE idMonster=?"); // 0-idOnster . 1-name . 2-health . 3-attack . 4-counterattack   
        cur2->prepare();
        cur2->bind(1,num);
        cur2->step();
        cout<<"You will fight against: "<< cur2->get_text(1)<<endl;
        int idMonster = num;
        refresh();
        if (idMonster==1)
            warrior();
        else if (idMonster==2)
            mage();
        else if (idMonster==3)
            hunter();
        else if (idMonster==4)
            dragQueen();
        else
            addstr("you are not lucky today");
        refresh();
    }
    //load mosnter variables about random number
    cur = db.get_statement();//clean the one used before to create query
    Battles var;
    var.idUser = 1;
    var.printWeapons(); //print all the weapons the user has
    getch();
    endwin();
    return 0;
}