#include <iostream>
#include <string>
#include <stdlib.h>
//#include "libsqlite.hpp"
#include <ncurses.h>
#include <unistd.h> //for usleep stuff
using namespace std;
int waitAbit(int sec){
    usleep(sec * 1000000); //the parameter works in micro-seconds 
}
int main(){
    initscr();
    addstr(" Wait until your opponent get ready \n");
    addstr("The opponent is cutting his nails");
    refresh();
    getch();
    clear();
    addstr("Let's get started \n");
    refresh();
    getch();
    int v1 = rand() % 5;
    cout<< v1<< endl;
    refresh();
    getch();
    endwin();
    return 0;
}