#ifndef MAZE_H
#define MAZE_H

#include <vector>

class Maze
{
public:
  Maze();
  Maze(int mazeSize);
  ~Maze();
  void generateMaze(int row, int col);
  void move(int *row, int *col);
  bool canMove(int row, int col);
  void findPath(int &row, int &col);
  bool canFindPath(int row, int col);

  int findStart();

  int getTileAt(int x, int y);
  void setTileAt(int x, int y, int value);
  // Arrays start at 0 you fucking autstic cunt.
  std::vector<std::vector<int>> getMaze();

private:
  std::vector<std::vector<int>> _maze;
  int _mazeSize;
  bool _foundExit = false;
  int _col, _row;
};

#endif
