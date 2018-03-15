#include <iostream>
#include <vector>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "level.h"
#include "entity.h"
#include "display.h"
#include "utils.h"
#include "battles.h"
#include "intro.h"
#include "loginForm.h"
#include "global.h"
#include "menu.h"

using namespace std;

int openTheChest(){
    sqlite::sqlite db("dungeonCrawler.db"); //opens database connection
    auto cur = db.get_statement();
    int numOfPowerups = 6;
    
    srand(time(0));
    int randPowerup = rand() % numOfPowerups + 1;
    
    cur-> set_sql("SELECT * FROM powerups WHERE idPowerup=?");
    cur-> prepare();
    cur->bind(1,randPowerup);
    cur->step();
    
    if (randPowerup == 1){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET maxHealth=maxHealth+5 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,globalUserID); //change by global variable here
    cur2->step();
    return 0;
    cout << "You found a small health upgrade! Health increased by 5.";
    cur2 = db.get_statement();
    }
    
    if (randPowerup == 2){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET maxHealth=maxHealth+10 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,globalUserID); //change by global variable here
    cur2->step();
    cout << "You found a health upgrade! Health increased by 10.";

    cur2 = db.get_statement();
    }
    
    if (randPowerup == 3){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+20 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,globalUserID); //change by global variable here
    cur2->step();
    cout << "You found 20 gold";
        
    cur2 = db.get_statement();
    }
    
    if (randPowerup == 4){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+40 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,globalUserID); //change by global variable here
    cur2->step();
    cout << "You found 40 gold";

    cur2 = db.get_statement();
    }
    
    if (randPowerup == 5){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+70 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,globalUserID); //change by global variable here
    cur2->step();
    std::cout << "You found 70 gold";

    cur2 = db.get_statement();
    }
    
    if (randPowerup == 6){
    auto cur2 = db.get_statement(); 
    cur2->set_sql("UPDATE users SET gold=gold+100 WHERE idUser =?");
    cur2->prepare();
    cur2->bind(1,globalUserID); //change by global variable here
    cur2->step();
    cout << "You found 100 gold";

    cur2 = db.get_statement();
    }
    return 0;
}



void question()
{
    while (true)
  {
    sqlite::sqlite db("dungeonCrawler.db");
    auto cur = db.get_statement();
    int numOfQuestions = 7;
    
    srand(time(0));
    int qNum = rand() % numOfQuestions + 1 ; //generate a number between 1-7, this decides the question you will recieve
    
    cur->set_sql("SELECT * FROM puzzle WHERE num=?");
    cur->prepare();
    cur->bind(1,qNum);
    cur->step();
    
    string Quest = cur->get_text(1);
    std::cout << "\033[2J" << std::endl;
    std::cout << Quest << std::endl;
    
    string userAnswer;
    std::cin >> userAnswer;
    
    string dbAnswer = cur->get_text(2);
    if(userAnswer == dbAnswer)
    {
		std::cout << "correct!" << std::endl;  
        break;
    }
    else
    {
		std::cout << "Incorrect!" << std::endl;
        break;
    }
  }
}
int wait(int sec){
    usleep(sec * 1000000); //the parameter works in micro-seconds, converts microseconds to seconds
}

char getKey() { //this be copy and pasted from somewhere i dont understand this
    struct termios old_tio, new_tio;                 //^its a template^//
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
    char key = getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    return key;
}

bool getUserInput(char key, Level &level, Display &display) { //Returns true if handled succsesfully
    string currentFocus = display.getFocus(); // player movement is handled in level.cpp
    if(currentFocus == "level") {
	switch(key) {
        case 65:
	    case 'w': 
		if(level.playerMove('U')) { return true; }
        else if(level.startBattle('U')) {Battles battle; battle.startBattle();}
        else if(level.openChest('U')) {openTheChest(); /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        else if(level.startPuzzle('U')) {question(); /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		break;
        case 68:
	    case 'a':
		if(level.playerMove('L')) { return true; }
        else if(level.startBattle('L')) {Battles battle; battle.startBattle();}
        else if(level.openChest('L')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		else if(level.startPuzzle('L')) {question(); /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        break;
        case 66:
	    case 's':
		if(level.playerMove('D')) { return true; }
        else if(level.startBattle('D')) {Battles battle; battle.startBattle();}   
        else if(level.openChest('D')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		else if(level.startPuzzle('D')) {question(); /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        break;
        case 67:
	    case 'd':
		if(level.playerMove('R')) { return true; }
        else if(level.startBattle('R')) {Battles battle; battle.startBattle();} 
        else if(level.openChest('R')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		else if(level.startPuzzle('R')) {question(); /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        break;
	}
	return false;
    }
}

int gameLoop(){
        Player player(1, 1);
        Player* playerptr;
        playerptr = &player;
        Level level(playerptr, 40, 40); //x length, y length
        level.generateMap();
        Display display;
        char key;
        bool validKey;
        while(true) { //runs indefinitely right now can probably easily have conditions added where it ends on death or some shit
        display.displayLevel(level);
        validKey = false;
        while(!validKey) {
            key = getKey();
          
            validKey = getUserInput(key, level, display);
        }
        level.cleanUp();
        }
        return 0;
    }



int main () {
    Intro intro; //creates object for the intro
    intro.intro(); // shows the intro screen
    wait(1); //waits 5 seconds
    
    loginForm login;
    login.loginOrRegist();
    if (menu()==1){
        gameLoop();
    }
    
    
}
