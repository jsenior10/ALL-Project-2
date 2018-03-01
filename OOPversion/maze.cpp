#include <ctime>
#include <cstdlib>
#include <iostream>

#include "maze.h"

Maze::Maze() {}

Maze::Maze(int mazeSize)
{
  std::srand(time(0));


  std::cout << "Making maze of size " << mazeSize << std::endl;

  for(int i = 0; i < mazeSize; i++) {
    std::vector<int> tempRow(0,mazeSize);
    this->_maze.push_back(tempRow);
    for (int j = 0; j < mazeSize; j++) {
      this->_maze[i].push_back(1);
    }
  }
  this->_foundExit = false;
  this->_mazeSize = mazeSize;
  int _col = 0;
  int _row = findStart();
  this->_maze[_row][_col] = 0;

  generateMaze(_row, _col);
  //this->_maze[_row][_col] = 2;
}

Maze::~Maze() {}

void Maze::generateMaze(int &row, int &col)
{

  bool made = false;
  while(made == false)
    {
    if(col == this->_mazeSize - 1) {
      this->_foundExit = true;
    }
    if(canFindPath(row, col)) {
      findPath(row, col);
    }
    else if(canMove(row, col)) {
      //2 means you can't move from that square,
      //setting any lower stops maze from being made
      this->_maze[row][col] = 2;
      //move to first open space that can be found
      move(row, col);
    }
    else {
      made = true;
    }
  }
}

void Maze::move(int &row, int &col)
{
  if(this->_maze[row][col+1] == 0)
    col = col + 1;
  else if(this->_maze[row+1][col] == 0)
    row = row + 1;
  else if(this->_maze[row][col-1] == 0)
    col = col - 1;
  else if(this->_maze[row-1][col] == 0)
    row = row - 1;
  else
    //if maze cant be solved it generates a
    //new one so the player doesnt have something
    //that is impossible to solve
    generateMaze(row, col);

}

bool Maze::canMove(int row, int col)
{
  if(this->_maze[row][col+1] == 0 &&
     col < this->_mazeSize-1)
    return true;
  else if(this->_maze[row+1][col] == 0 &&
          row < this->_mazeSize-1)
    return true;
  else if(this->_maze[row][col-1] == 0 &&
          col > 0)
    return true;
  else if(this->_maze[row-1][col] == 0 &&
          row > 0)
    return true;
  else
    return false;
}

void Maze::findPath(int &row, int &col)
{
  bool foundSolution = false;

  while(foundSolution == false) {

    int direction = (1 + std::rand() % 4) * 3;
    switch(direction) {
    case 3:
      if(col + 1 <= this->_mazeSize - 1 &&
         this->_maze[row][col + 2] == 1 &&
         this->_maze[row-1][col+1] == 1 &&
         this->_maze[row+1][col+1] == 1 &&
         this->_maze[row][col + 1] == 1) {
        if(col == this->_mazeSize - 2 &&
           this->_foundExit == true) {
        }
        else {
          col++;
          foundSolution = true;
        }
      }
      break;
    case 6:
      if(row + 1 <= this->_mazeSize - 2 &&
         this->_maze[row + 2][col] == 1 &&
         this->_maze[row+1][col+1] == 1 &&
         this->_maze[row+1][col-1] == 1 &&
         this->_maze[row + 1][col] == 1 &&
         col != 0 && col != this->_mazeSize - 1) {
        row++;
        foundSolution = true;
      }
      break;
    case 9:
      if(col - 1 >= 0 &&
         this->_maze[row][col - 2] == 1 &&
         this->_maze[row-1][col-1] == 1 &&
         this->_maze[row+1][col-1] == 1 &&
         this->_maze[row][col - 1] == 1 &&
         col - 1 != 0) {
        col--;
        foundSolution = true;
      }
      break;
    case 12:
      if(row - 1 >= 1 &&
         this->_maze[row - 2][col] == 1 &&
         this->_maze[row-1][col+1] == 1 &&
         this->_maze[row-1][col-1] == 1 &&
         this->_maze[row - 1][col] == 1 &&
         col != 0 &&
         col != this->_mazeSize - 1) {
        row--;
        foundSolution = true;
      }
      break;
    }
  }
  this->_maze[row][col] = 0;
}

bool Maze::canFindPath(int row, int col)
{
  bool solvable = false;

  if(row <= this->_mazeSize - 3 &&
     this->_maze[row + 2][col] == 1 &&
     this->_maze[row+1][col+1] == 1 &&
     this->_maze[row+1][col-1] == 1 &&
     this->_maze[row + 1][col] == 1 &&
     col != 0 &&
     col != this->_mazeSize - 1) {
    //if adjacent space can be moved to
    solvable = true;
}
  else if(col <= this->_mazeSize - 2 &&
         this->_maze[row][col + 2] == 1 &&
         this->_maze[row-1][col+1] == 1 &&
         this->_maze[row+1][col+1] == 1 &&
         this->_maze[row][col + 1] == 1) {
   if(col == this->_mazeSize - 2 &&
      this->_foundExit == true) {
     ; //do nothing
   }
   else {
       solvable = true;
   }
 }
 else if(row >= 2 &&
         this->_maze[row - 2][col] == 1 &&
         this->_maze[row-1][col+1] == 1 &&
         this->_maze[row-1][col-1] == 1 &&
         this->_maze[row - 1][col] == 1 &&
         col != 0 &&
         col != this->_mazeSize - 1) {
   //if not on extreme left or right
   solvable = true;
 }
 else if(col >= 1 &&
         this->_maze[row][col - 2] == 1 &&
         this->_maze[row-1][col-1] == 1 &&
         this->_maze[row+1][col-1] == 1 &&
         this->_maze[row][col - 1] == 1 &&
         col - 1 != 0) {
   solvable = true;
 }
  return solvable;
}

int Maze::findStart()
{
  return 1 + std::rand() % (this->_mazeSize - 2);
}

int Maze::getTileAt(int x, int y)
{
  return this->_maze[x][y];
}

void Maze::setTileAt(int x, int y, int value)
{
  this->_maze[x][y] = value;
}

std::vector<std::vector< int > > Maze::getMaze()
{
  return this->_maze;
}
