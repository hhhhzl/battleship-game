#pragma once
#include <iostream>
#include <vector>
#include "Player.h"

const int CONNER_NUMBERS = 4;
struct denseP
{
   int prob; // the prob for each cell
};

class YourLastName:
   public Player
{
   protected :
      int minValue; // to store the min value in density matrix
      int maxValue; // to store the current max value in de
      denseP dense[OCEAN_SIZE][OCEAN_SIZE];
      Coords shot; // last shot taken, i==-1 means none taken so far
      Coords lasthit; // last hit shot taken.

     // put variables here to act as global variables within your file
     // You could, for example, you could have variables here to
     // record the Coords of the last torpedo you fired.

   public:
      YourLastName( string n );
      bool brace( Coords );
      Coords shoot(); // function for shooting strategy
      void sound( Coords, bool );
      void matchInit(); // init the match
      void initDenseP(); // init the density matrix
      void printDenseBoard(); // helper function for printing the density board
      void putShip(Cell[OCEAN_SIZE][OCEAN_SIZE] ); // function for init the location of the ship
      int checkHitNumber(); // count the how many points have been hitted 
      int checkHitDirection(); // check the direction (h or v) if we have hitted 2 points or more
      Coords makeMove(Coords); // function to check where to move
      Coords checkHorizontal(Coords); // function to only check horizontal neighbors
      Coords checkVertical(Coords); // function to only check vertical neighbors
      Coords checkBoth(Coords); // function to check both vertical and horizontal neighbors
};

