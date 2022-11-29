//#include "stdafx.h"
#include "Random.h"

Random::Random( std::string n) : Player(n)
{

}

void Random::matchInit()
{
   int row = rand()%OCEAN_SIZE;
   for (int j=0; j<SHIP_SIZE; j++ )
   { myOcean[row][j].ship=true; }
}

bool Random::brace( Coords c )
{  
   myOcean[c.i][c.j].torpedo = true;;
   return myOcean[c.i][c.j].ship;
}

Coords Random::shoot() 
{
   Coords ret;

   do
   {
      ret.i = rand()%OCEAN_SIZE;
      ret.j = rand()%OCEAN_SIZE;
   }
   while ( yourOcean[ret.i][ret.j].ship );
   yourOcean[ret.i][ret.j].torpedo = true;
   return ret; 
}

void Random::sound( Coords c, bool hit ) 
{
   if(hit){ yourOcean[c.i][c.j].ship = true; }
}