#pragma once

#include "Player.h"

class Random : public Player
{
public:
    Random( std::string );
    //~Random();
    void matchInit();
    bool brace( Coords  );
    Coords shoot() ;
    void sound( Coords, bool ) ;
};

