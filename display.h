#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
private:
    bool isDeathScreenOpen = false; // some ad setupfor a screen for when the player dies
    string currentFocus = "level";
    
public:
    void open(string); //Open a window (inventory, death screen)
    void close(string); //Close a window
    void changeFocus(string); //Change focus to an open window to control it
    string getFocus(); //Returns the current focus
    void moveSelection(char); //Moves the selection in a window
    void displayLevel(Level); //Displays the level (and whatever focus)
};

#endif
