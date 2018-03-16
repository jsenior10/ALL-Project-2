#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "level.h"

// i chose an approach that generates smaller rooms and then put them into  a larger map becausewith the maze
// it seemed like people would just try trace their way to the exit and with this approach we could set up
// conditions where the player may only be able to complete the level once all enemies are dead or something
// it just seemed like a better idea
// http://www.roguebasin.com/ and http://pcg.wikidot.com/ were used as resources and guidelines as they contain
//  many approaches to procedural generation and were very useful in putting this together
using namespace std;

Level::Level(Player* p, int width, int height) {
    player = p;
    map.resize(height, vector<char>(width, ' ')); //basically sets the level properly, removig this specific line gives a segmentation fault
}

vector< vector<char> > Level::getMap() {
    return map;
}

vector< vector<char> > Level::getMapWithEntities() {
    vector< vector<char> > entityMap = map;
    entityMap[player->yPos][player->xPos] = 'X';
    for(int i=0; i<chests.size(); i++) {
        entityMap[chests[i].yPos][chests[i].xPos] = '1';}
    for(int i=0; i<enemies.size(); i++) {
        entityMap[enemies[i].yPos][enemies[i].xPos] = '2';}
        for(int i=0; i<puzzles.size(); i++) {
        entityMap[puzzles[i].yPos][puzzles[i].xPos] = '3';}
    return entityMap;
}

void Level::generateMap() {

    //Random generation
    //Number of rooms will be proportional to the map size (in squares)
    int mapWidth = map[0].size();
    int mapHeight = map.size();
    int mapSize = mapWidth * mapHeight;
    int roomDensity = 75; //How many squares are needed for a room to spawn (low number -> many rooms), setting this too low makes it take too long to generate a level, i did some testing with this and it seems a room desnity between 50 and 100 is good
    int numRooms = mapSize / roomDensity;
    int avgRoomWidth = 6; //Average room width
    int avgRoomHeight = 8;// its best not to vhange the height or width as it can take ages to make the level
    float roomSizeVariation = 0.5f; //Variation in room size
    int minRoomWidth = round(roomSizeVariation * avgRoomWidth);
    int maxRoomWidth = round((2 - roomSizeVariation) * avgRoomWidth);
    int minRoomHeight = round(roomSizeVariation * avgRoomHeight);
    int maxRoomHeight = round((2 - roomSizeVariation) * avgRoomHeight);
    float enemyProbability = 0.18f;
    float chestProbability = 0.10f;
    float puzzleProbability = 0.10f;
    
    vector< vector<int> > rooms;
    vector< vector<int> > openings;
    vector<int> room(4);
    
    while(true) { //Initial seed room
	room[0] = randomNumber(0, mapWidth-1);
	room[1] = randomNumber(0, mapHeight-1);
	room[2] = randomNumber(minRoomWidth, maxRoomWidth);
	room[3] = randomNumber(minRoomHeight, maxRoomHeight);
	if(room[0] + room[2] < mapWidth && room[1] + room[3] < mapHeight) { //Not outside map
	    rooms.push_back(room);
	    break;
	}
    }
    int x, y;
    for(int i=0; i<numRooms; i++) {
	while(true) {
	    x = randomNumber(0, mapWidth-1);
	    y = randomNumber(0, mapHeight-1);
	    char side = ' ';
	    for(int j=0; j<rooms.size(); j++) {
		if(x == rooms[j][0] && y > rooms[j][1] && y < rooms[j][1] + rooms[j][3]) {
		    side = 'L'; //Left side
		    break;
		}
		else if(x == rooms[j][0] + rooms[j][2] && y > rooms[j][1] && y < rooms[j][1] + rooms[j][3]) {
		    side = 'R'; //Right
		    break;
		}
		else if(y == rooms[j][1] && x > rooms[j][0] && x < rooms[j][0] + rooms[j][2]) {
		    side = 'T'; //Top
		    break;
		}
		else if(y == rooms[j][1] + rooms[j][3] && x > rooms[j][0] && x < rooms[j][0] + rooms[j][2]) {
		    side = 'B'; //Bottom
		    break;
		}
	    }
	    if(side != ' ') { //Check if on wall
		//makes what is placed here rnadom

		//Generate the room location and size
		room[2] = randomNumber(minRoomWidth, maxRoomWidth);
		room[3] = randomNumber(minRoomHeight, maxRoomHeight);
		switch(side) {
		    case 'T':
			room[1] = y - room[3];
			room[0] = x - randomNumber(1, room[2]-1); //Randomise where the opening appears on the new room, 1 and room[2]-1 to remove corner connections
			break;
		    case 'B':
			room[1] = y;
			room[0] = x - randomNumber(1, room[2]-1);
			break;
		    case 'L':
			room[0] = x - room[2];
			room[1] = y - randomNumber(1, room[3]-1);
			break;
		    case 'R':
			room[0] = x;
			room[1] = y - randomNumber(1, room[3]-1);
			break;
		}
		//Check if the room is valid

		bool isValid = true;
		
		if(room[0] < 0 || room[1] < 0 || room[0] + room[2] >= mapWidth || room[1] + room[3] >= mapHeight) {
		    isValid = false;
	       	}
	        for(int j=0; j<rooms.size(); j++) {
		    if((isFieldOverlapping({room[0], room[0] + room[2] - 1}, {rooms[j][0], rooms[j][0] + rooms[j][2] - 1})) && (isFieldOverlapping({room[1], room[1] + room[3] - 1}, {rooms[j][1], rooms[j][1] + rooms[j][3] - 1}))) { //Uses -1 so room edges touching does not count
			isValid = false;
			break;
		    }
		}
		if(isValid) {
		    //Add puzzles, enemies, chests to the map
		    if(randomProbability() < chestProbability) { // works by: if number generated in randomProbability is less than chestProbability, place a chest until randomProbability > chestProbability, same for the other objects
            Chest chest(room[0] + 1, room[1] + 1, 1); // adds 
			chests.push_back(chest);
		    }
            if(randomProbability() < enemyProbability) {
            Enemy enemy(room[0] + 2, room[1] + 1, 1);
			enemies.push_back(enemy);
		    }
            if(randomProbability() < puzzleProbability) {
            Puzzle puzzle(room[0] + 3, room[1] + 2, 1);
			puzzles.push_back(puzzle);
		    }
		    rooms.push_back(room);
		    openings.push_back({x, y});
		    break;
		}
	    }
	}
    }
    for(int i=0; i<rooms.size(); i++) { //Draw rooms
	for(int j=0; j<=rooms[i][2]; j++) { //Draw horizontal walls, doesnt let me use ▓ for in this sorry ):
	    map[rooms[i][1]][rooms[i][0] + j] = '#';
	    map[rooms[i][1] + rooms[i][3]][rooms[i][0] + j] = '#';
	}
	for(int j=0; j<=rooms[i][3]; j++) { //Draw vertical walls
	    map[rooms[i][1] + j][rooms[i][0]] = '#';
	    map[rooms[i][1] + j][rooms[i][0] + rooms[i][2]] = '#';
	}
    }
    for(int i=0; i<openings.size(); i++) {
	map[openings[i][1]][openings[i][0]] = ' ';
    }
    player->xPos = rooms[0][0] + 1;
    player->yPos = rooms[0][1] + 1;
}



void Level::movePlayerTo(int x, int y) {
    player->xPos = x;
    player->yPos = y;
}


bool Level::isChest(int x, int y) {
    if(x == player->xPos && y == player->yPos) {
	return true;
    }
    for(int i = 0; i<chests.size(); i++ ){
		if(x == chests[i].xPos
           && y == chests[i].yPos){
            return true;
        }
    }

    return false;
}

bool Level::isEnemy(int x, int y) {
    if(x == player->xPos && y == player->yPos) {
	return true;
    }
    for(int i = 0; i<enemies.size(); i++ ){
		if(x == enemies[i].xPos
           && y == enemies[i].yPos){
            return true;
        }
    }

    return false;
}

bool Level::isPuzzle(int x, int y) {
    if(x == player->xPos && y == player->yPos) {
	return true;
    }
    for(int i = 0; i<puzzles.size(); i++ ){
		if(x == puzzles[i].xPos
           && y == puzzles[i].yPos){
            return true;
        }
    }

    return false;
}


Entity* Level::getEntityAtPosition(int x, int y) {
    if(x == player->xPos 
       && y == player->yPos) {
       return player; 
    }
    Entity* chestPtr;
    Entity* enemyPtr;
    Entity* puzzlePtr;
    for(int i=0; i<chests.size(); i++){
        if(x == chests[i].xPos
          && y == chests[i].yPos){
            chestPtr = &chests[i];
            return chestPtr;
        }
    }
    for(int i=0; i<enemies.size(); i++){
        if(x == enemies[i].xPos
          && y == enemies[i].yPos){
            enemyPtr = &enemies[i];
            return enemyPtr;
        }
    }
    for(int i=0; i<puzzles.size(); i++){
        if(x == puzzles[i].xPos
          && y == puzzles[i].yPos){
            puzzlePtr = &puzzles[i];
            return puzzlePtr;
        }
    }
}

bool Level::openChest(char direction) {
    int x = player->xPos;
    int y = player->yPos;
    vector<vector<char>> map = getMapWithEntities();
    if(direction == 'U'
      && isChest(x, y-1)){
        Entity* chests = getEntityAtPosition(x, y-1);
        chests->hasInteracted(player->chestOpen);
        return true;
    }
    if(direction == 'D'
      && isChest(x, y+1)){
        Entity* chests = getEntityAtPosition(x, y+1);
        chests->hasInteracted(player->chestOpen);
        return true;
    }
    if(direction == 'L'
      && isChest(x-1, y)){
        Entity* chests = getEntityAtPosition(x-1, y);
        chests->hasInteracted(player->chestOpen);
        return true;
    }
    if(direction == 'R'
      && isChest(x+1, y)){
        Entity* chests = getEntityAtPosition(x+1, y);
        chests->hasInteracted(player->chestOpen);
        return true;
    }
    return false;
}

bool Level::startBattle(char direction) {
    int x = player->xPos;
    int y = player->yPos;
    vector<vector<char>> map = getMapWithEntities();
    if(direction == 'U'
      && isEnemy(x, y-1)){
        Entity* enemies = getEntityAtPosition(x, y-1);
        enemies->hasInteracted(player->startBattle);
        return true;
    }
    if(direction == 'D'
      && isEnemy(x, y+1)){
        Entity* enemies = getEntityAtPosition(x, y+1);
        enemies->hasInteracted(player->startBattle);
        return true;
    }
    if(direction == 'L'
      && isEnemy(x-1, y)){
        Entity* enemies = getEntityAtPosition(x-1, y);
        enemies->hasInteracted(player->startBattle);
        return true;
    }
    if(direction == 'R'
      && isEnemy(x+1, y)){
        Entity* enemies = getEntityAtPosition(x+1, y);
        enemies->hasInteracted(player->startBattle);
        return true;
    }
    return false;
}

bool Level::startPuzzle(char direction) {
    int x = player->xPos;
    int y = player->yPos;
    vector<vector<char>> map = getMapWithEntities();
    if(direction == 'U'
      && isPuzzle(x, y-1)){
        Entity* puzzles = getEntityAtPosition(x, y-1);
        puzzles->hasInteracted(player->startPuzzle);
        return true;
    }
    if(direction == 'D'
      && isPuzzle(x, y+1)){
        Entity* puzzles = getEntityAtPosition(x, y+1);
        puzzles->hasInteracted(player->startPuzzle);
        return true;
    }
    if(direction == 'L'
      && isPuzzle(x-1, y)){
        Entity* puzzles = getEntityAtPosition(x-1, y);
        puzzles->hasInteracted(player->startPuzzle);
        return true;
    }
    if(direction == 'R'
      && isPuzzle(x+1, y)){
        Entity* puzzles = getEntityAtPosition(x+1, y);
        puzzles->hasInteracted(player->startPuzzle);
        return true;
    }
    return false;
}

void Level::cleanUp() { 
//////this function is just for later on when things need to be removed from the map
for(int i=0; i<chests.size(); i++){
    if(chests[i].isDead){
        chests.erase(chests.begin()+i);
    }
}
for(int i=0; i<enemies.size(); i++){
    if(enemies[i].isDead){
        enemies.erase(enemies.begin()+i);
    }
}
for(int i=0; i<puzzles.size(); i++){
    if(puzzles[i].isDead){
        puzzles.erase(puzzles.begin()+i);
    }
}
}

void Level::printMap(vector< vector<int> > map) { //prints the map ALONE, doesnt include any enemies, chests etc
    for(int i=0; i<map.size(); i++) {
	for(int j=0; j<map[i].size(); j++) {
	    cout << map[i][j] << " ";
	}
    
	cout << endl;
    }
}

int Level::randomNumber(int min, int max) {
    if(!isRandomInitialised) {
	srand(time(NULL));
	isRandomInitialised = true;
    }
    return (rand() % (max-min+1)) + min;
}

float Level::randomProbability() {
    if(!isRandomInitialised) {
	srand(time(NULL));
	isRandomInitialised = true;
    }
    return rand() / (RAND_MAX + 1.0);
}

bool Level::isFieldOverlapping(vector<int> field1, vector<int> field2) { //checks to make sure that the rooms are not overlapping which could cause problems for the player such as impossible levels
    sort(field1.begin(), field1.end()); sort(field2.begin(), field2.end());
    if(field1[0] == field2[0]) {
	return true;
    }
    else if(field1[0] < field2[0]) {
	if(field1[1] >= field2[0]) { //Max of field 1 is greater than min of field 2
	    return true;
	}
	else {
	    return false; //Max and min of field 1 are lower than min field 2
	}
    }
    else {
	if(field2[1] >= field1[0]) {
	    return true;
	}
	else {
	    return false;
	}
    }
}

