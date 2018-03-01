#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;
class Weapons{
    public:
    bool assignWeapon(int idUser){
        
        
        return true;
    }
    void printWeapons(){
        sqlite::sqlite db( "dungeonCrawler.db" ); // open database
        auto cur = db.get_statement(); // create query
        cur->set_sql("SELECT type AS Type, damage AS Damage, attack AS Attack, duration AS Duration, price AS Price FROM weapon"); //query
        cur->prepare();
        while(cur->step()){
            cout<< cur->get_text(0)<<cur->get_int(1)<<cur->get_int(2)<<cur->get_int(3)<<endl;
        }
    }
};
int main(){
    Weapons var;
    var.printWeapons();
    return 0;
}