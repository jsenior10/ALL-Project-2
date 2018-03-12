#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;
class Weapons{
    public:
    int idUser;
    bool assignWeapon(int weapon, sqlite::sqlite &db){
        auto cur2 = db.get_statement(); // create query
        cur2->set_sql("SELECT duration FROM weapon WHERE idWeapon=?");
        cur2->prepare();
        cur2->bind(1,weapon);
        cur2->step();
        auto cur3 = db.get_statement(); // create query
        cur3->set_sql("INSERT INTO weapons-user(idWeapon,idUser,duration) VALUES (?,?,?)");
        cur3->prepare();
        cur3->bind(1,weapon);
        cur3->bind(2,idUser);
        cur3->bind(3,cur2->get_int(0));
        return true;
    }
    void printWeapons(sqlite::sqlite &db){
        auto cur = db.get_statement(); // create query
        cur->set_sql("SELECT w.idWeapon, w.type, w.damage, w.attack, w.duration, w.price FROM weapon w, users u WHERE (u.idUser=? AND u.gold > w.price)"); //query
        cur->prepare();
        cur->bind(1,idUser);
        cout<<"+---------------+--------+--------+----------+-------+"<<endl;
        cout<<"|      Type     | Damage | Attack | Duration | Price |"<<endl;
        cout<<"+---------------+--------+--------+----------+-------+"<<endl;
        while(cur->step()){
            cout<<"| "<<cur->get_int(0)<<"-"<< cur->get_text(1)<<"\t"<<"|    "<<cur->get_int(2)<<"   "<<"|   "<<cur->get_int(3)<<"   "<<"|    "<<cur->get_int(4)<<"    |   "<<cur->get_int(4)<<"  |"<<endl;
            cout<<"+---------------+--------+--------+----------+-------+"<<endl;
        }  
    }
    
};
