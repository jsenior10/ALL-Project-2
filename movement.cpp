#include <iostream>
#include <curses.h>

using namespace std;

bool running = true;
int playerX = 2; // sets player starting position
int playerY = 2;

char map[12][13] =  //draws a small map with an array in order to test movement and collision etc
{
	"            ",
	" 1111111111 ",
	" 1        1 ",
	" 111    1 1 ",
	" 1  1 1   1 ",
	" 1  1  1  1 ",
	" 1  1  1  1 ",
	" 1 1  1   1 ",
	" 1   1    1 ",
	" 1  1     1 ",
	" 1  1111111 ",
	"            "

};
// Draw Map
//
void drawMap()
{
  for (int i = 0; i < 12; i++) {
    // addstr is nCurses equiv
    // of cout or print
    addstr(map[i]);
    addstr("\n");
    }
}


// Detect Char input
// and move player in direction
void getUserInput()
{
char userInput = getch();
  if (userInput == 'w') {
    int playerY2 = playerY - 1;
    if (map[playerY2][playerX] == ' ') {
      map[playerY][playerX] = ' ';
      playerY--;
      map[playerY][playerX] = 'x';
    }
  }
  if (userInput == 'a') {
    int playerX2 = playerX - 1;
    if (map[playerY][playerX2] == ' ') {
      map[playerY][playerX] = ' ';
      playerX--;
      map[playerY][playerX] = 'x';
    }
  }
  if (userInput == 's') {
    int playerY2 = playerY + 1;
    if (map[playerY2][playerX] == ' ') {
      map[playerY][playerX] = ' ';
      playerY++;
      map[playerY][playerX] = 'x';
    }
  }
  if (userInput == 'd') {
    int playerX2 = playerX + 1;
    if (map[playerY][playerX2] == ' ') {
      map[playerY][playerX] = ' ';
      playerX++;
      map[playerY][playerX] = 'x';
    }
  }
}

// Main game update
// Runs through all functions required
void update()
{
  getUserInput();
  clear();
  drawMap();
  refresh();
}


//
//
int main()
{
  // Initate nCurses display
  initscr();
  while( true ) {
    update();
  }
  // End nCurses display
  endwin();
  return 0;
}
