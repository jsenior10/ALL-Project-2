#include <iostream>
using namespace std;
#include <string>
#include "libsqlite.hpp"
//CREATE TABLE logTable(
//idLog INTEGER PRIMARY KEY AUTOINCREMENT,
//idUser INTEGER NOT NULL,
//action text NOT NULL,
//time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
//);
bool insertLogTable(int idUser, string action){
    sqlite::sqlite db( "dungeonCrawler.db" ); // open database
    
    auto cur = db.get_statement(); // create query
    cur->set_sql("INSERT INTO logTable(idUser, action) VALUES(?,?)");
    cur->prepare(); // run query
    cur->bind( 1, idUser );
    cur->bind( 2, action );
    cur->step();  
    return true;
}