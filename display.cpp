#include <iostream>
#include <vector>
#include <cstdlib> 
#include "level.h"
#include "display.h"

void Display::open(string s) {
    if(s == "death_screen") { //deathscreen is just setup incase we want to have a specific screen show up when the player dies
	isDeathScreenOpen = true;
    }
}

void Display::close(string s) {
    if(s == "death_screen") {
	isDeathScreenOpen = false;
    }
}

void Display::changeFocus(string s) {
    if(s == "death_screen") {
	currentFocus = "death_screen";
    }
}

string Display::getFocus() {
    return currentFocus;
}

void Display::moveSelection(char direction) {
    switch(direction) {
	case 'L':
	    //Do something
	    break;
	case 'R':
	    //Do something
	    break;
    }
}

void Display::displayLevel(Level level) {
    vector< vector<char> > map = level.getMapWithEntities(); // getMapWithEntities set up for later when there are enemies and other things to dsiplay, right now it just prints the level without any enemies oe anythiong
    vector< vector<char> > nextScreen(map.size()+2, vector<char>(map[0].size()+2, ' ')); //Contains what we will show
    //Set level up into nextScreen
    //cout << string(50, '\n');
    system("clear");
    nextScreen[0][0] = ' ';
    for(int i=1; i<=map[0].size(); i++) {
	nextScreen[0][i] = ' ';
    }
    nextScreen[0][nextScreen[0].size()-1] = ' ';
    for(int i=1; i<=map.size(); i++) {
	nextScreen[i][0] = ' ';
	for(int j=1; j<=map[0].size(); j++) {
	    nextScreen[i][j] = map[i-1][j-1];
	}
	nextScreen[i][nextScreen[i].size()-1] = ' ';
    }
    nextScreen[nextScreen.size()-1][0] = ' ';
    for(int i=1; i<=map[0].size(); i++) {
	nextScreen[nextScreen.size()-1][i] = ' ';
    }
    nextScreen[nextScreen.size()-1][nextScreen[0].size()-1] = ' ';
    //Add windows over this

    
    for(int i=0; i<nextScreen.size(); i++) {
	for(int j=0; j<nextScreen[0].size(); j++) {
	    cout << nextScreen[i][j] << ' ';
	}
	cout << endl;
    }

}
