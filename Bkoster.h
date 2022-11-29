#pragma once

#include "Player.h"

class Bkoster : public Player
{
protected:
	//int dCount=0; // number of defects from opponent
   Coords shot; // last shot taken, i==-1 means none taken so far
public:
    Bkoster( std::string );
    //~Bkoster();
    //char play(int);
	void matchInit(); 

   bool brace( Coords );
   Coords shoot();
   void sound( Coords, bool );

   void putShip(Cell[OCEAN_SIZE][OCEAN_SIZE] );
};
