/*****************************************************************************************************
 ** Program       Filename: GameOfLife
 ** Current       File: gameOfLife.cpp
 ** Author:       Jordan Grant
 ** Date:         9.30.15
 ** Description: 	Conways Game of Life: This program creates a 2D grid with
 cells that exist as live or dead. The rules of Conways Game of Life are as follows:
 1. If an occupied cell has zero or one neighbor, it dies of loneliness.
 2. If an occupied cell has more than three neighbors, it dies of overcrowding.
 3. If an empty cell has exactly three occupied neighbor cells, there is a birth of a
 new cell to replace the empty cell.
 4. Births and deaths are instantaneous and occur at the changes of generation.

 The Grid begins dead until the user specifies a start position at which point cells
 are switched alive in a pattern that will begin that sequence. The program then goes
 through a loop of 100 updates of the Game.

 ** Input: User inputs the start position they would like to observe
 ** Output: 1) Prompt for user input
 2) 100 iterations of the chosen pattern
 *******************************************************************************************************/


#include <iostream>
#include <string>
#include <unistd.h>
#include "golFunctions.hpp"


int main()
{
  int choice = 1;

  /** define GameOfLife and temp arrays and initialize the game to NULL **/
  char gameOfLife[ROWS][COLUMNS] = {},
       temp[ROWS][COLUMNS] = {};

  while (choice > 0) //loop as long as user desires
  {

    std::cout
      << "\nPlease enter your choice in pattern\n"
      << "\tEnter 1 for Pulsar\n"
      << "\tEnter 2 for Gliders\n"
      << "\tEnter 3 for Glider Cannon: Gosper's Glider Gun\n"
      << "\tEnter 4 for Queen Bee Shuttle\n"
      << "\tEnter 0 to quit" << std::endl;

    std::cin >> choice; //get user's choice

    if (choice > 0 && choice <= LAST_PATTERN )
    {
      seedGameboard(gameOfLife, choice);
      /*
       ** for loop prints the board and updates the game 100 times
       ** usleep() institues a pause that allows the changes to be followed
       as they are printed.
       */
      for (int i = 0; i < 100; i++)
      {
        printGame(gameOfLife);
        SLEEP();
        updateGame(gameOfLife, temp);
      }
    }
  }

  return 0;
}
