#include "game.h"

#include <iostream>

Game::Game()
{
  std::cout << "Starting Game" << std::endl;
  Maze maze = Maze(31);
  for (int i = 0; i<31; i++) {
    for (int j = 0; j<31; j++) {
      std::cout << "Getting tile at " << i << " " << j << std::endl;
      std::cout << maze.getTileAt(i, j) << std::endl;
    }
  }
}

Game::~Game() {}
