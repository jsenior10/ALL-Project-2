#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;
int main(){
    sqlite::sqlite db( "dungeonCrawler.db" ); // open database
    auto cur = db.get_statement(); // set the cursor
    cur->set_sql("SELECT * FROM users");//create query
    cur->prepare(); // run query
     while(cur->step() == true){
         int id = cur->get_int(0);
         string name = cur->get_text(1);
         string pass = cur->get_text(2);
         int level = cur->get_int(3);
         int gold = cur->get_int(4);
         cout<<id << "  " << name << "  " << pass << "  " << level << "  " << gold << endl;
     }
    return 0;
    
}