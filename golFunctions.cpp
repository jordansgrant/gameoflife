/**************************************************************************************************
 ** Program       Filename: GameOfLife
 ** Current       File: golFunctions.cpp
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
 *****************************************************************************************************/

#include "golFunctions.hpp"

/*********************************************************************
 ** Function: Copy 2D array
 ** Description: After the nextGen is updated, copies the contents to currentGen
 ** Parameters: Takes two 2D char arrays that are ROWSxCOLUMNS
 ** Pre-Conditions: Call at the end of updateGame() or the output will be a step
 behind the current generation
 ** Post-Conditions: printGame() will now output the most recently modified generation
 *********************************************************************/
void copy(char currentGen[ROWS][COLUMNS], char nextGen[ROWS][COLUMNS])
{
  for (int row = 0; row < ROWS; row++)
    for (int column = 0; column < COLUMNS; column++)
      currentGen[row][column] = nextGen[row][column];
}

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
 ** Post-Conditions: Both currentGen and nextGen will be updated
 *********************************************************************/
void updateGame(char currentGen[ROWS][COLUMNS], char nextGen[ROWS][COLUMNS])
{
  for (int row = 0; row < ROWS; row++)
  {
    for (int column = 0; column < COLUMNS; column++)
    {
      bool live = true;
      char lod = currentGen[row][column];

      live = liveOrDie(neighbors(currentGen, row, column), lod);

      if (live == true)
        nextGen[row][column] = 'x';
      else
        nextGen[row][column] = '-';
    }
  }

  copy(currentGen, nextGen);
}

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
int neighbors(char currentGen[ROWS][COLUMNS], int row, int column)
{
  int occupied = 0;

  if (currentGen[row][column - 1] == 'x') // left neighbor
    occupied++;
  if (currentGen[row][column + 1] == 'x') // right neighbor
    occupied++;
  if (currentGen[row + 1][column] == 'x') // bottom neighbor
    occupied++;
  if (currentGen[row - 1][column] == 'x') // top neighbor
    occupied++;
  if (currentGen[row + 1][column + 1] == 'x') // bottom right neighbor
    occupied++;
  if (currentGen[row - 1][column - 1] == 'x') // top left neighbor
    occupied++;
  if (currentGen[row + 1][column - 1] == 'x') // bottom left neighbor
    occupied++;
  if (currentGen[row - 1][column + 1] == 'x') // top right neighbor
    occupied++;

  return occupied;
}

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
bool liveOrDie(int n, char lod)
{
  if (n == 3 && lod == '-')      // current cell come to life?
    return true;
  else if (n <= 1 && lod == 'x') // current cell die of lonliness?
    return false;
  else if (n > 3 && lod == 'x')  // current cell die of overcrowding?
    return false;
  else if (lod == '-')           // current cell remain dead
    return false;
  else                           // current cell remain alive
    return true;
}

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
void printGame(char array[ROWS][COLUMNS])
{
  CLEAR();
  for (int row = 3; row < ROWS - 2; row++)
  {
    for (int column = 2; column < COLUMNS - 2; column++)
    {
      std::cout << array[row][column];
    }
    std::cout << std::endl;
  }
}

/*********************************************************************
 ** Function: Seed Game Board
 ** Description: clears game and seeds game board with live cells ('x')
 ** Parameters: 2D char array with dimension ROWSxCOLUMNS, user choice of pattern
 ** Pre-Conditions: Game board allocated and player choice collected
 *********************************************************************/
void seedGameboard(char array[ROWS][COLUMNS], int pattern) {
  /** initially set all cells to dead('-') **/
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLUMNS; j++)
      array[i][j] = '-';

  /*
   **Switch case to set initial states of the game by user input:
   **1)Pulsar 2)Gliders 3) Glider Cannon 4)Queen Bee Shuttle
   ***Each block of assignments represent a distinct pattern (eg. a single glider)
   */
  switch (pattern)
  {
    case PULSAR: //Pulsar http://www.conwaylife.com/wiki/Pulsar
      /** Pulsar top left quadrant **/
      array[6][17] = 'x';
      array[6][18] = 'x';
      array[6][19] = 'x';
      array[8][15] = 'x';
      array[9][15] = 'x';
      array[10][15] = 'x';
      array[8][20] = 'x';
      array[9][20] = 'x';
      array[10][20] = 'x';
      array[11][17] = 'x';
      array[11][18] = 'x';
      array[11][19] = 'x';

      /** Pulsar bottom left quadrant **/
      array[13][17] = 'x';
      array[13][18] = 'x';
      array[13][19] = 'x';
      array[18][17] = 'x';
      array[18][18] = 'x';
      array[18][19] = 'x';
      array[14][15] = 'x';
      array[15][15] = 'x';
      array[16][15] = 'x';
      array[14][20] = 'x';
      array[15][20] = 'x';
      array[16][20] = 'x';

      /** Pulsar top right quadrant **/
      array[6][23] = 'x';
      array[6][24] = 'x';
      array[6][25] = 'x';
      array[11][23] = 'x';
      array[11][24] = 'x';
      array[11][25] = 'x';
      array[8][22] = 'x';
      array[9][22] = 'x';
      array[10][22] = 'x';
      array[8][27] = 'x';
      array[9][27] = 'x';
      array[10][27] = 'x';

      /** Pulsar bottom right quadrant **/
      array[14][22] = 'x';
      array[15][22] = 'x';
      array[16][22] = 'x';
      array[14][27] = 'x';
      array[15][27] = 'x';
      array[16][27] = 'x';
      array[13][23] = 'x';
      array[13][24] = 'x';
      array[13][25] = 'x';
      array[18][23] = 'x';
      array[18][24] = 'x';
      array[18][25] = 'x';

      break;

    case GLIDERS: //gliders https://en.wikipedia.org/wiki/Glider_(Conway%27s_Life)
      /** left most glider **/
      array[2][6] = 'x';
      array[3][7] = 'x';
      array[4][7] = 'x';
      array[4][6] = 'x';
      array[4][5] = 'x';

      /** second to left glider **/
      array[2][12] = 'x';
      array[3][13] = 'x';
      array[4][13] = 'x';
      array[4][12] = 'x';
      array[4][11] = 'x';

      /** second to right glider **/
      array[2][18] = 'x';
      array[3][19] = 'x';
      array[4][19] = 'x';
      array[4][18] = 'x';
      array[4][17] = 'x';

      /** right most glider **/
      array[2][24] = 'x';
      array[3][25] = 'x';
      array[4][25] = 'x';
      array[4][24] = 'x';
      array[4][23] = 'x';

      break;

    case GLIDER_GUN: //Glider Cannon http://www.conwaylife.com/wiki/Gosper_glider_gun

      /** left feeder block **/
      array[10][4] = 'x';
      array[10][5] = 'x';
      array[11][4] = 'x';
      array[11][5] = 'x';

      /** left figure **/
      array[10][14] = 'x';
      array[11][14] = 'x';
      array[12][14] = 'x';
      array[9][15] = 'x';
      array[13][15] = 'x';
      array[8][16] = 'x';
      array[8][17] = 'x';
      array[14][16] = 'x';
      array[14][17] = 'x';
      array[11][18] = 'x';
      array[9][19] = 'x';
      array[13][19] = 'x';
      array[10][20] = 'x';
      array[11][20] = 'x';
      array[12][20] = 'x';
      array[11][21] = 'x';

      /** right figure **/
      array[8][24] = 'x';
      array[9][24] = 'x';
      array[10][24] = 'x';
      array[8][25] = 'x';
      array[9][25] = 'x';
      array[10][25] = 'x';
      array[7][26] = 'x';
      array[11][26] = 'x';
      array[6][28] = 'x';
      array[7][28] = 'x';
      array[11][28] = 'x';
      array[12][28] = 'x';

      /** right feeder block **/
      array[8][38] = 'x';
      array[9][38] = 'x';
      array[8][39] = 'x';
      array[9][39] = 'x';

      break;

    case QUEEN_BEE: //Queen Bee Shuttle http://www.conwaylife.com/wiki/Queen_bee_shuttle
      /** Left feeder block **/
      array[11][11] = 'x';
      array[11][12] = 'x';
      array[12][11] = 'x';
      array[12][12] = 'x';

      /** Right feeder block **/
      array[11][31] = 'x';
      array[11][32] = 'x';
      array[12][31] = 'x';
      array[12][32] = 'x';

      /** Center figure 'Queen Bee' **/
      array[11][16] = 'x';
      array[10][17] = 'x';
      array[12][17] = 'x';
      array[13][18] = 'x';
      array[9][18] = 'x';
      array[10][19] = 'x';
      array[11][19] = 'x';
      array[12][19] = 'x';
      array[8][20] = 'x';
      array[9][20] = 'x';
      array[13][20] = 'x';
      array[14][21] = 'x';

      break;
  }
}
