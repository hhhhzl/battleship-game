// Prisoner.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include "Player.h"

// comstructor, pass in the name of the Player
Player::Player( std::string n )
{
   name = n;
	//rank = 0;
	//rankSum = 0;
   score = 0;
   clearOcean( myOcean );
   clearOcean( yourOcean );
}

// sets ocean to blank, no ships, no torpedos
void Player::clearOcean( Cell oc[OCEAN_SIZE][OCEAN_SIZE]  )
{
   for ( int i=0; i<OCEAN_SIZE; i++ )
   {  for ( int j=0; j<OCEAN_SIZE; j++ )
      { 
         oc[i][j].ship = false;
         oc[i][j].torpedo = false;
      }
   }
}

void Player::showOcean()
{
   cout <<endl;
   cout<<"Situation for player " <<name <<endl;
   cout <<"my ocean                        your ocean\n";
   for ( int i=0; i<OCEAN_SIZE; i++ )
   {
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         Cell c =myOcean[i][j];
         string s = (c.ship?"s":"-");
         string t = (c.torpedo?"t":"-");
         cout <<" " <<s <<t <<" ";
      }
      cout <<"      ";
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         Cell c =yourOcean[i][j];
         string s = (c.ship?"s":"-");
         string t = (c.torpedo?"t":"-");
         cout <<" " <<s <<t <<" ";
      }
      cout <<endl;  
   }

}


// clears the match record for the next match
const void Player::rinit()
{
   clearOcean( myOcean );
   clearOcean( yourOcean );
}

const bool Player::peek( Coords c){ return myOcean[c.i][c.j].ship; }


// puts the opposing player's play into the vector
// that stores them (yourChoices).  
const void Player::record( int r, char x )
{
    //yourChoices[r] = x;
    yourChoices.push_back(x);
}

const void Player::addToScore( int x )
{
    score += x;
}

int Player::report()
{
    std::cout <<"player " <<name <<" scored " <<score 
		//<<" rank=" <<rank 
		//<<" rankSum=" <<rankSum
		<<".\n";
    return score;
}

// fire torpedos in all of myOcean.  sink my ship.
// this disqualifies this player, basically.
const void Player::sinkMe( )
{
   cout <<getName() <<" is disqualified this match\n";
   for ( int i=0; i<OCEAN_SIZE; i++ )
   {
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         myOcean[i][j].torpedo = true;
      }
   }
}
