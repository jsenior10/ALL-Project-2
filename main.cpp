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

using namespace std;

bool displayMaze = true;

int displayOption(int mazeOn)
{
    if(mazeOn == 1)
    {
        displayMaze = true;
    }
    if(mazeOn == 2)
    {
        displayMaze = false;
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
        else if(level.openChest('U')) {cout << "fgfds"; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        else if(level.startPuzzle('U')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		break;
        case 68:
	    case 'a':
		if(level.playerMove('L')) { return true; }
        else if(level.startBattle('L')) {Battles battle; battle.startBattle();}
        else if(level.openChest('L')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		else if(level.startPuzzle('L')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        break;
        case 66:
	    case 's':
		if(level.playerMove('D')) { return true; }
        else if(level.startBattle('D')) {Battles battle; battle.startBattle();}   
        else if(level.openChest('D')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		else if(level.startPuzzle('D')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        break;
        case 67:
	    case 'd':
		if(level.playerMove('R')) { return true; }
        else if(level.startBattle('R')) {Battles battle; battle.startBattle();} 
        else if(level.openChest('R')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
		else if(level.startPuzzle('R')) {return true; /*CALL THE FUCNTION TO RUN WHEN INTERACTING HERE*/}
        break;
	}
	return false;
    }
}
int main () {
    Intro intro; //creates object for the intro
    intro.intro(); // shows the intro screen
    wait(5); //waits 5 seconds
    
    loginForm login;
    login.loginOrRegist();
    
    Player player(1, 1);
    Player* playerptr;
    playerptr = &player;
    Level level(playerptr, 40, 40); //x length, y length
    level.generateMap();
    Display display;
    char key;
    bool validKey;
    while(displayMaze == true)
    {
        display.displayLevel(level);
        validKey = false;
        
        while(!validKey)
        {
            key = getKey();
            
            if(key == 'z')
            {
                cout << "homo";//Debugging
            }
            
	    validKey = getUserInput(key, level, display);
	}
	level.cleanUp();
    }
    return 0;
}
