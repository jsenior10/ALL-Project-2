// ALL 2.cpp : Defines the entry point for the console application.

#include <iostream>
#include "libsqlite.hpp"

using namespace std;


//Armour bronze - 20 points
int armourbronze(int armour) {
	armour = armour + 20;
	cout << armour << endl;
    //insert to db
}
//Armour silver - 60 points
int armoursilver(int armour) {
	armour = armour + 60;
	cout << armour << endl;
    //insert to db
}
//Armour gold - 100 points
int armourgold(int armour) {
	armour = armour + 100;
	cout << armour << endl;
    //insert to db
}

//Level jump - 1 level
int leveljump() {
  int level = 0;
	level = level + 1;
	cout << level << endl;
}

//Duration increase - up 3
int durincsmall() {
    sqlite::sqlite db( "dungeonCrawler.db" ); 
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE weapons_user SET duration=duration+3 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,1); //change by global variable here
    cur2->step();
    return 0;
}
//Duration increase - up 6
int durincmedium() {
    sqlite::sqlite db( "dungeonCrawler.db" ); 
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE weapons_user SET duration=duration+6 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,1); //change by global variable here
    cur2->step();
    return 0;
}
//Duration increase - up 20
int durinclarge() {
    sqlite::sqlite db( "dungeonCrawler.db" ); 
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE weapons_user SET duration=duration+20 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,1); //change by global variable here
    cur2->step();
    return 0;
}

int armourcall(){ 
    sqlite::sqlite db( "dungeonCrawler.db" ); 
    auto cur = db.get_statement();   
    cur->set_sql("SELECT armor, username FROM users WHERE idUser=?");
    cur->prepare();
    cur->bind(1,2); //change by global variable here
    cur->step();
    int armouruser = cur->get_int(0);
    cout << armouruser << endl;
}


int main(){   
      
    armourcall();

    int test;
    cout << "Do you want to use a (1) small, (2) medium or (3) large potion. Type the corresponding number to buy it." << endl;
    cin >> test;

    if(test == 1)
    {
        durincsmall();
        cout << "small done" << endl;
    }
    else if(test == 2)
    {
        durincmedium();
        cout << "medium done" << endl;
    }
    else if(test == 3)
    {
        durinclarge();
        cout << "large done" << endl;
        
    }
    else
    {
	cout << "Something has gone seriously wrong here!";
    }
    
    //durincsmall();
    //durincmedium();
    //durinclarge();

    //leveljump();
    
    return 0;
}
//user id 2 called thor
  