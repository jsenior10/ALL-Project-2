#ifndef LEVEL_H
#define LEVEL_H
using namespace std;

#include "player.h"
#include "entity.h"
#include "chest.h"
#include "enemy.h"
#include "puzzle.h"

static bool isRandomInitialised = false;

class Level {

private:
    
    vector< vector<char> > map;
    Player* player;
    /* Map characters:
       (space) - open ground
       # - wall
       P - player
       1 - chest
       2 - enemy
       3 - puzzle
    */
    vector<Chest> chests;
    vector<Enemy> enemies;
    vector<Puzzle> puzzles;

    void movePlayerTo(int, int); //Move the player to any location
    
public:
    
    Level(Player*, int, int); //Constructor
    vector< vector<char> > getMap(); //Return the map
    vector< vector<char> > getMapWithEntities(); //Returns the map with all entities
    void generateMap(); //Creates the map
    vector< vector<int> > getDistanceMap(int, int, int); //Gets the map but shows the distances from a single space
    bool playerMove(char); //Moves the player in a specified direction
    Entity* getEntityAtPosition(int, int); //Gets a pointer to the entity at a given location
    void cleanUp(); //Removes all things interacted with after interacting
    bool isChest(int, int); //checks if theres a chest in the direction the player is moving
    bool openChest(char); // doesnt actually open the chest, but reduces it's 'health' to 0 so it disappears when interacted with
    bool isEnemy(int, int); //checks if theres an enemy in the direction the player is moving
    bool startBattle(char); //doesnt actually start the battle, but reduces it's 'health' to 0 so it disappears when interacted with
    bool isPuzzle(int, int); //checks if theres a puzzle in the direction the player is moving
    bool startPuzzle(char); //doesnt actually start  the puzzle, but reduces it's 'health' to 0 so it disappears when interacted with
    void printMap(vector< vector<int> >);
    int randomNumber(int, int); // this is used in the generation of the map
    bool isFieldOverlapping(vector<int>, vector<int>); // checks if rooms overlaps and prevents it
    float randomProbability(); // this is used in placing things on the map
};
#endif
