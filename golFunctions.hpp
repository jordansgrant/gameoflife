/************************************************************************************************
 ** Program       Filename: GameOfLife
 ** Current       File: golFunctions.hpp
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
 **************************************************************************************************/


#ifndef GOLFUNCTIONS_HPP
#define GOLFUNCTIONS_HPP

#ifdef _WIN32
#define CLEAR() system("CLS")
#else
#define CLEAR() system("clear")
#endif

#define ROWS 24
#define COLUMNS 44

enum PATTERNS {
  PULSAR = 1,
  GLIDERS,
  GLIDER_GUN,
  QUEEN_BEE,
  LAST_PATTERN=QUEEN_BEE
};

#include <iostream>
#include <string>

/*********************************************************************
 ** Function: Copy 2D array
 ** Description: After the nextGen is updated, copies the contents to currentGen
 ** Parameters: Takes two 2D char arrays that are ROWSxCOLUMNS
 ** Pre-Conditions: Call at the end of updateGame() or the output will be a step
 behind the current generation
 ** Post-Conditions: printGame() will now output the most recently modified generation
 *********************************************************************/
void copy(char currentGen[ROWS][COLUMNS], char lastGen[ROWS][COLUMNS]);

/*********************************************************************
 ** Function: Update Game of Life
 ** Description: This function goes to each cell and:
 1) checks for the number of live neighbors (neighbors() function)
 2) applies the rules for life or death (liveOrDie() function)
 3) modifies the current cell in nextGen with the appropriate state
 4) transfers nextGen back to currentGen for printing and to get
 ready for the next round
 ** Parameters: Takes two 2D char arrays that are ROWSxCOLUMNS
 ** Pre-Conditions: currentGen must be initialized to a "starting state"
 nextGen should be pre-initialized with some value
 (can be NULL - will just be overwritten)
 ** Post-Conditions: If copy() is used: Both currentGen and nextGen will be updated
 If copy()is not used then only nextGen will be updated
 *********************************************************************/
void updateGame(char currentGen[ROWS][COLUMNS], char nextGen[ROWS][COLUMNS]);

/*********************************************************************
 ** Function: Live Neighbors
 ** Description: finds the number of live neighbors by using the x,y
 coordinates of the current cell and checking each of the
 surrounding neighbors for "life"". If a neighboring cell is
 occupied (alive) it adds 1 to the counter.
 ** Parameters: 2D char array with dimensions ROWS*COLUMNS, 2 ints representing the
 coordinates of the current cell.
 ** Pre-Conditions: Feeds into the liveOrDie() function so it must be called inside
 ** Post-Conditions: returns an integer to liveOrDie representing the number of
 live neighbors
 *********************************************************************/
int neighbors(char currentGen[ROWS][COLUMNS], int row, int column);

/*********************************************************************
 ** Function: Current Cell Live or Die?
 ** Description: Receives the number of live neighbors from neighbors() function
 along with the char occupying the current cell (lod). Applies the
 rules of Conways Game of life.
 1. If an occupied cell has zero or one neighbor, it dies.
 2. If an occupied cell has more than three neighbors, it dies.
 3. If an empty cell has exactly three occupied neighbor cells it
 comes to life
 ** Parameters: int representing live neighbors, char of the current cell
 ** Pre-Conditions: must have a bool variable to receive whether teh cell should
 live or die. neighbors() function should be used to generate the
 first paramater.
 ** Post-Conditions: returns true or false.
 for true: current cell lives in the nextGen
 for false: current cell dies in the nextGen
 *********************************************************************/
bool liveOrDie(int n, char lod);

/*********************************************************************
 ** Function: Print Array
 ** Description: Prints a 20x40 2D char array
 ** Parameters: 2D char array with dimension ROWSxCOLUMNS
 ** Pre-Conditions: 1) if GameOfLife is just begun:
 The current generation must be initialized to start position
 2) else the temp array must be copied to GameOfLife array after update()
 ** Post-Conditions: A segment of the Game of life is printed to the screen, excluding a
 2 cell wide band around the parimeter. This avoids seeing strange
 behavior as sequences reach the edge of the board.
 *********************************************************************/
void printGame(char array[ROWS][COLUMNS]);

/*********************************************************************
 ** Function: Seed Game Board
 ** Description: clears game and seeds game board with live cells ('x')
 ** Parameters: 2D char array with dimension ROWSxCOLUMNS, user choice of pattern
 ** Pre-Conditions: Game board allocated and player choice collected
 *********************************************************************/
void seedGameboard(char array[ROWS][COLUMNS], int choice);

#endif

