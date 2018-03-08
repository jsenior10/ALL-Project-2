#ifndef LOGTABLEFUNCTION_H
#define LOGTABLEFUNCTION_H

#include <iostream>
using namespace std;
#include <string>
#include "libsqlite.hpp"
int insertLogTable(int id, string actionValue){
    sqlite::sqlite db( "dungeonCrawler.db" ); // open database
    auto cur2 = db.get_statement(); // create query
    cur2->set_sql("INSERT INTO logTable(idUser, action) VALUES(?, ?)");
    cur2->prepare(); // run query
    cur2->bind( 1, id );
    cur2->bind( 2, actionValue );
    if (cur2->step()){
        return 0;
    }
    else{
        return 1;
    }
}

#endif