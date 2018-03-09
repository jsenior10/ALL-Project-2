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
#include "intro.h";

using namespace std;

int wait(int sec){
    usleep(sec * 1000000); //the parameter works in micro-seconds 
}
char getKey() {
    struct termios old_tio, new_tio;   //template
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
    char key = getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    return key;
}

bool getUserInput(char key, Level &level, Display &display) { //Returns true if handled succsesfully
    string currentFocus = display.getFocus(); // player movement is handled in level.cpp. but the controls are handled here
    if(currentFocus == "level") {
	switch(key) {
        case 65:
	    case 'w': 
		if(level.playerMove('U')) { return true; }
		break;
        case 68:
	    case 'a':
		if(level.playerMove('L')) { return true; }
		break;
        case 66:
	    case 's':
		if(level.playerMove('D')) { return true; }
		break;
        case 67:
	    case 'd':
		if(level.playerMove('R')) { return true; }
		break;
	}
	return false;
    }
    else if(currentFocus == "death_screen") {
	switch(key) {
	    case 'a':
		display.moveSelection('L');
		return true;
		break;
	    case 'd':
		display.moveSelection('R');
		return true;
		break;
	}
	return false;
    }
}
int main () {
    intro();
    wait(3);
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
	    if(key == 'z') { //Debugging
		return 0;
	    }
	    validKey = getUserInput(key, level, display);
	}
	//level.cleanUp(); this can be uncommented later on when we have things that need to be removed from the map
    }
    return 0;
}
