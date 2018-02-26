#include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
//
//  g++ --std=c++14 battles.cpp -lncurses -o battles -lsqlite3
//
#include <ncurses.h>
#include <unistd.h> //for usleep stuff
using namespace std;
int waitAbit(int sec){
    usleep(sec * 1000000); //the parameter works in micro-seconds 
}
int main(){
	sqlite::sqlite db("dungeonCrawler.db");//open database
	auto cur = db.get_statement();//create query
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
    cur->set_sql("SELECT COUNT(idMonster) FROM monsters");
    cur->prepare();
    cur->step();
    int numOfMonsters = cur->get_int(0);
    int num = rand() % numOfMonsters;
    cout << num << endl;
	cur->set_sql("SELECT * FROM monsters WHERE idMonster =?"); // 0-idOnster . 1-name . 2-health . 3-attack . 4-counterattack   
	cur->prepare();
    cur->bind(1,num);
    cur->step();
    if (num > 0){
        cout << "You will fight against :" << endl;
        refresh();
    }else{
        cout<<"not ok"<<endl;
        refresh();
    }
    //load mosnter variables about random number
    refresh();
    getch();
    endwin();
    return 0;
}