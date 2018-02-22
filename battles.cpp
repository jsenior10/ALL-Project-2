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
    int num = rand() % 5;
    cout << num << endl;
	cur->set_sql("SELECT * FROM monsters WHERE idMonster = num"); // 0-idOnster . 1-name . 2-health . 3-attack . 4-counterattack   
	cur->prepare();
    if (cur->step()){
        cout << "You will fight against :" << endl;
        refresh();
    }else{
        cout<<"not ok"<<endl;
    }
	
    
    //load mosnter variables about random number
    
    refresh();
    getch();
    endwin();
    return 0;
}