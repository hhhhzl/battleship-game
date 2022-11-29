#pragma once

#include <vector>
#include "Player.h"
using namespace std;

class Battle
{
private:
    vector<Player*> players;

public:
    Battle();
    ~Battle();
    void copyOcean( Player*, Cell[OCEAN_SIZE][OCEAN_SIZE] );
    bool isAfloat(Cell[OCEAN_SIZE][OCEAN_SIZE] );
	void tourney();
    int run(); // does one round, each player x each other
    void pit( Player*, Player* );
    void takeTurn(Player*, Player*, Cell[OCEAN_SIZE][OCEAN_SIZE],
         Cell[OCEAN_SIZE][OCEAN_SIZE]  );
	//char padded(Player*, int);
	void bunches(); // does a bunch of rounds
	void sort();
	void shuffle();

   const bool checkCoords( Coords );
   const bool braceCheck( Coords , Cell[OCEAN_SIZE][OCEAN_SIZE]);
   const bool shipShape( Cell[OCEAN_SIZE][OCEAN_SIZE] );
   const void sink(  Cell[OCEAN_SIZE][OCEAN_SIZE]);

    // return the points for the given combination of choices.
    // Assumes we are scoring the player giving the FIRST 
    // char here.
    //int slap( char, char );
 
    void standings();
};

