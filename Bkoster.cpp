//#include "stdafx.h"
#include "Bkoster.h"




Bkoster::Bkoster( std::string n ) : Player(n)
{
}

bool Bkoster::brace( Coords c )
{
   myOcean[c.i][c.j].torpedo = true;
   return myOcean[c.i][c.j].ship;
}

void Bkoster::matchInit()
{
   clearOcean( myOcean );
   clearOcean( yourOcean );
   putShip( myOcean );
   shot.i = -1;
}


// always put the ship in row2, left side
void Bkoster::putShip(  Cell oc[OCEAN_SIZE][OCEAN_SIZE]  )
{
   for ( int i=0; i<4; i++ )
   {
     oc[2][i].ship = true;
   }
}


// pick a place to shoot a torpedo in yourOcean.
// The strategy of Bkoster is just to shoot in order,
// the same order that you would read (left to right,
// top to bottom).  
Coords Bkoster::shoot()
{
   Coords ret;

   if ( shot.i == -1 ) { ret.i = 0, ret.j = 0;  }
   else
   {
      ret = shot;
      ret.j++;
      if ( ret.j == OCEAN_SIZE )
      { ret.j=0; ret.i++; }
   }
   shot = ret; // save this one, will be last one next time
   yourOcean[ret.i][ret.j].torpedo = true;
   return ret;
}

// record whether there is a ship at these coordinates
// (which is the same as 'hit' or 'miss', given that
// this is a place you fired a torpedo).  
void Bkoster::sound( Coords c, bool sh )
{
   yourOcean[c.i][c.j].ship = sh;
}
