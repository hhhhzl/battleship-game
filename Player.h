#pragma once

#include <string>
#include <vector>
using namespace std;

const int OCEAN_SIZE = 7;
const int SHIP_SIZE = 4;

struct Cell
{
   bool ship; // true means this cell has a ship in it
   bool torpedo; // true means a torpedo has been fired in this cell
};

// index in 2d of a cell 0 to OCEAN_SIZE-1  ^2
struct Coords
{
   int i;
   int j;
};

class Player
{
protected:
   Cell myOcean[OCEAN_SIZE][OCEAN_SIZE];
   Cell yourOcean[OCEAN_SIZE][OCEAN_SIZE];

   vector<char> myChoices; // 'c' or 'd' for as many rounds as there
   vector<char> yourChoices; // have been played so far

   string name;// Player's name eg "bob"

private:
	int score = 0; // this score accumulates over all other players,
	               // so do not reset at the start of a set of 200.

public:
   Player( std::string );
   virtual ~Player(){}
   void clearOcean( Cell[OCEAN_SIZE][OCEAN_SIZE]  );
   void showOcean();

   // peek takes Coords as an argument and returns true
   // if there is a ship there.  This is for the tournament
   // program to check on the correctness of the program.  This
   // is not for actually firing torpedos.
  const bool peek( Coords c );

   // brace takes a Coords as an argument and returns true
   // a torpedo in myOcean hits a ship.  This is like
   // peek but also records the torpedo.
   virtual bool brace( Coords c )=0;

   // This function is a request for this Player to fire a
   // torpedo at the opponent's ocean.  It is up
   // to this player to record the location of the fire
   // if they want.
   virtual Coords shoot()=0 ;

   // This is the system reporting to this player the results
   // of shooting at the other player 
   // as Coords c, hit=true is a hit, false=miss
   virtual void sound( Coords, bool ) =0;

	// called before the 200 rounds with each player
	// Students should use this to initialize whatever 
	// the start of playing an opponent.
	virtual void matchInit()=0;

	const void rinit(); // is called before each player plays another player
			  // for 200 rounds.  It clears out old records of
			  // previous choices.


   // record what the other player played, given round number
   // and their character 'c' or 'd'
   const void record( int , char );

   const void sinkMe( );

   int report();

   const void addToScore( int );
   const string getName() { return name; }
   const int getScore() { return score; } 
	const void setScore(int s) { score = s; }
};
