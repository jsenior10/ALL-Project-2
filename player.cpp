#include "player.h"
#include "level.h"

Player::Player (int x, int y) {
    xPos = x;
    yPos = y;
}

bool Level::playerMove(char direction) { //Returns true if valid move, false if not
    int x = player->xPos;
    int y = player->yPos;
    vector< vector<char> > map = getMapWithEntities();
    if(direction == 'U' && map[y-1][x] == ' ') { //up
	player->yPos = y-1;
	return true;
    }
    else if(direction == 'L' && map[y][x-1] == ' ') { //left
        player->xPos = x-1;
        return true;
    }
    else if(direction == 'D' && map[y+1][x] == ' ') { //down
        player->yPos = y+1;
        return true;
    }
    else if(direction == 'R' && map[y][x+1] == ' ') { //right
        player->xPos = x+1;
        return true;
    }
    return false;
}
