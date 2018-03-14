#include <iostream>
#include <string>
#include "weaponset.h"
#include "libsqlite.hpp"
#include "global.h"
using namespace std;
    bool Weapons::assignWeapon(int weapon, sqlite::sqlite &db){
        auto cur2 = db.get_statement(); // create query
        cur2->set_sql("SELECT duration FROM weapon WHERE idWeapon=?");
        cur2->prepare();
        cur2->bind(1,weapon);
        cur2->step();
        int duration=cur2->get_int(0);
        auto cur3 = db.get_statement(); // create query
        cur3->set_sql("INSERT INTO weapons_user(idWeapon,idUser,duration) VALUES(?,?,?)");
        cur3->prepare();
        cur3->bind(1,weapon);
        cur3->bind(2,globalUserID); 
        cur3->bind(3,duration);
        cur3->step();
        return true;
    }
    void Weapons::printWeapons(sqlite::sqlite &db){
        auto cur = db.get_statement(); // create query
        cur->set_sql("SELECT w.idWeapon, w.type, w.damage, w.attack, w.duration, w.price FROM weapon w, users u WHERE (u.idUser=? AND u.gold > w.price)"); //query
        cur->prepare();
        cur->bind(1, globalUserID);
        cout<<"+---------------+--------+--------+----------+-------+"<<endl;
        cout<<"|      Type     | Damage | Attack | Duration | Price |"<<endl;
        cout<<"+---------------+--------+--------+----------+-------+"<<endl;
        while(cur->step()){
            cout<<"| "<<cur->get_int(0)<<"-"<< cur->get_text(1)<<"\t"<<"|    "<<cur->get_int(2)<<"   "<<"|   "<<cur->get_int(3)<<"   "<<"|    "<<cur->get_int(4)<<"    |   "<<cur->get_int(4)<<"  |"<<endl;
            cout<<"+---------------+--------+--------+----------+-------+"<<endl;
        }  
    }
    
