// Battle.cpp
// This is the driver class for the Battleship Tournament.
// Barrett Koster 2020



#include <iostream>
#include <string>
#include <ctime>

#include "Bkoster.h"
#include "Random.h"
#include "YourLastName.h"
#include "Battle.h"

bool bug = false;

void printOcean( Cell osh[OCEAN_SIZE][OCEAN_SIZE] );

// create the Battle and run the tournament.
int main()
{
    cout <<"program starting \n";

    int seed = (int)time(0);
    if(bug)
    {
       cout << "enter seed or -1 for random: ";
       cin >> seed;
       if (seed == -1)
       {
          seed = (int)time(0);
       }
    }
    cout << "random seed: " << seed << endl;
    srand(seed);


    Battle* theBattle = new Battle();
    theBattle->tourney();
  
    delete theBattle;
    return 0;
}

// This lets you play everyone against everyone a bunch of
// times, then shows the score board.  You can then pick
// how many to cut off the bottom and do it again.
// cut==0 quits.
void Battle::tourney()
{
	bool keepGoing = true;
	int clip;
	while (keepGoing)
	{
		//run();
		bunches();
		sort();
		standings();
		cout << "How many to delete before rerun? ";
		cin >> clip;
		if (clip == 0) { keepGoing = false;  }
		for (int i = 0; i < clip; i++) { players.pop_back(); }
	}

}


// add tothe players vector all of the Player objects
// in the tournament.
// also start the random number generator.
Battle::Battle()
{
   cout <<"Battleship Tournament\n\n";


	players.push_back(new Bkoster("bar1"));
   players.push_back(new YourLastName("arty"));
   players.push_back(new YourLastName("arthur"));
   players.push_back(new Random("bob"));
	players.push_back(new Bkoster("bar2"));
	players.push_back(new Random("sue"));
}


// run() (everyone vs. everyone once)  5 times.
// For each of the 5, sort them by accumulated score.
void Battle::bunches()
{
   int times = 5;
   for (Player *p : players) { p->setScore(0); }

   //for (Player* it : players) { it->clearRankSum();  }
   for (int i = 0; i < times; i++)
   {
      run(); // now starts all scores at 0
   }
}


// play each player against every other once.
// Score accumulates (do not zero to start).
// Put the vector of Players in random order, then
// play each one against each other, once.  
// Each player gets an accumulated score from all
// opponents.  
int Battle::run()
{
    //int ROUNDS = 200 + rand()%5; // slightly random so you can't game
	                             // the end
	shuffle();

   int playerCount = (int)(players.size());
    for ( int i=0; i<playerCount-1; i++ )
    {
        for ( int j=i+1; j<playerCount; j++ )
        {
            Player *p0 = players[i];
            Player *p1 = players[j];

            pit( p0, p1 );
        }
    }

    return 0;
}

// put players vector in order of score
void Battle::sort()
{
	int playerCount = (int)(players.size());

	for (int i = 0; i < playerCount - 1; i++)
	{
		for (int j = i + 1; j < playerCount; j++)
		{
			if (players[i]->getScore() < players[j]->getScore())
			{
				Player* temp = players[i];
				players[i] = players[j];
				players[j] = temp;
			}
		}
	}
}


// randomize the order of players
void Battle::shuffle()
{
	int playerCount = (int)(players.size());

	for (int i = 0; i < playerCount; i++)
	{
		int j = rand() % playerCount;
		if (j!=i)
		{
			Player* temp = players[i];
			players[i] = players[j];
			players[j] = temp;
		}
	}
}

// put the two players against each other for 200+ rounds.
// We score and record what each player plays.
void Battle::pit( Player* p0, Player* p1 )
{
    cout <<"pitting " <<p0->getName() <<" against " 
       <<p1->getName() <<endl;

	p0->rinit(); // Player init, can't be changed by student
	p1->rinit();
	p0->matchInit(); // your init, whatever you need to do
	p1->matchInit();

   Cell home0[OCEAN_SIZE][OCEAN_SIZE];
   Cell home1[OCEAN_SIZE][OCEAN_SIZE];

   // TODO: use return values to check players
   copyOcean( p0, home0 );
   copyOcean( p1, home1 );

   if ( !shipShape(home0) ) { sink(home0); cout <<p0->getName() <<" dq ship placement\n"; }
   if ( !shipShape(home1) ) { sink(home1); cout <<p1->getName() <<" dq ship placement\n"; }

   int limit = 100;
   int turns = 0;
   bool win0 = !isAfloat(home1);
   bool win1 = !isAfloat(home0);
   while (turns<limit && !win0 && !win1 )
   {
      turns++; // just to avoid infinite loops

      takeTurn( p0, p1, home0, home1 );
      takeTurn( p1, p0, home1, home0 );

      win0 = !isAfloat(home1);
      win1 = !isAfloat(home0);
      if(bug){ p1->showOcean(); }
      if(bug){ p0->showOcean(); }
      
      if( bug){ string e; cout <<"enter: "; getline( cin,e);  }

   }
   if( bug){ string e; cout <<"enter: "; getline( cin,e);  }
   if (win0) { p0->addToScore(1);  cout <<p0->getName() <<" wins \n"; }
   if (win1) { p1->addToScore(1);  cout <<p1->getName() <<" wins \n"; }

   if (bug) { cout <<"game ends in " <<turns <<" turns\n"; }
}

// make sure ship is placed 4 in a row  col, no spaces, no bends
// return true if it's good, false if not.
// how: find min i and j, max i and j, compute difi and difj.
// One should be 4, the other 0.
const bool Battle::shipShape( Cell osh[OCEAN_SIZE][OCEAN_SIZE] )
{
   bool ret = false; // not ok until we say so
   int mini = OCEAN_SIZE;
   int maxi = 0;
   int minj = OCEAN_SIZE;
   int maxj = 0;

   for ( int i=0; i<OCEAN_SIZE; i++ )
   {
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         if ( osh[i][j].ship )
         {
            if ( i<mini ) { mini = i; }
            if ( i>maxi ) { maxi = i; }
            if ( j<minj ) { minj = j; }
            if ( j>maxj ) { maxj = j; }
         }
      }
   }

   int difi = maxi-mini;
   int difj = maxj-minj;
   if ( (difj*difi==0) && ((difi+difj)==3) ) { ret = true; }
   return ret;
}

// fire torpedos in all of myOcean.  sink my ship.
// this disqualifies this player, basically.
const void Battle::sink(  Cell osh[OCEAN_SIZE][OCEAN_SIZE])
{
   //cout <<getName() <<" is disqualified this match\n";
   for ( int i=0; i<OCEAN_SIZE; i++ )
   {
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         osh[i][j].torpedo = true;
      }
   }
}


// player p0 fires on p1
void Battle::takeTurn( Player* p0, Player* p1, 
   Cell home0[OCEAN_SIZE][OCEAN_SIZE], Cell home1[OCEAN_SIZE][OCEAN_SIZE]  )
{
   // TODO: add the try-catch padding here
   Coords c = p0->shoot();
   if (bug){ cout <<p0->getName() <<"  fires at " <<c.i <<"," <<c.j <<endl; }
   if ( !checkCoords(c) ) { sink(home0); cout <<p0->getName() <<" dq for ij out of range\n"; }
   else
   {
      //home1[c.i][c.j].torpedo = true;
      bool hitCheck = braceCheck( c, home1 );
      bool hit = p1->brace( c );
      if ( hitCheck!=hit ) { sink(home1); cout<<p1->getName() <<" dq for misreport hit\n"; }
      else
      {
         string s = (hit)?"hit":"miss";
         if(bug){ cout <<p1->getName() <<" reports " <<s <<endl;}
         p0->sound( c, hit );
      }
   }
}

// return true if these are in range
const bool Battle::checkCoords( Coords c )
{
   return 0<=c.i && c.i<OCEAN_SIZE && 0<=c.j && c.j<OCEAN_SIZE;
}

// This is what brace SHOULD return  
const bool Battle::braceCheck( Coords c, Cell home1[OCEAN_SIZE][OCEAN_SIZE])
{
   home1[c.i][c.j].torpedo = true;
   return home1[c.i][c.j].ship;
}


// copy player p's home ocean to this array.
// Check it to be valid (right config of ship)
void Battle::copyOcean( Player* p, Cell osh[OCEAN_SIZE][OCEAN_SIZE]  )
{
   bool ok = true;
   int count=0;
   for ( int i=0; i<OCEAN_SIZE; i++ )
   {
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         bool ship = p->peek( Coords{i,j} );
         osh[i][j].ship = ship;
         osh[i][j].torpedo = false;
         if(ship) { count++; }
      }
   }
   if ( count!=SHIP_SIZE ) { ok = false; }
   // TODO: we also need to check for straight line
}




// return true if there is still some part of a ship afloat
bool Battle::isAfloat( Cell osh[OCEAN_SIZE][OCEAN_SIZE]  )
{  bool afloat = false;  // until you find out
   for ( int i=0; !afloat && i<OCEAN_SIZE; i++ )
   {
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         Cell c = osh[i][j];
         if ( c.ship && !c.torpedo ) { afloat = true; }
      }
   }
   //if(bug){ printOcean(osh); cout<<" isAfloat reports " <<afloat <<endl;}
   return afloat;
}

void printOcean( Cell osh[OCEAN_SIZE][OCEAN_SIZE] )
{
   for ( int i=0; i<OCEAN_SIZE; i++ )
   {
      for ( int j=0; j<OCEAN_SIZE; j++ )
      {
         Cell c = osh[i][j];
         string s = (c.ship?"s":"-");
         string t = (c.torpedo?"t":"-");
         cout <<" " <<s <<t <<" ";
    
      }
      cout <<endl;
   }

}

/*
// this gets a single play out of a player objects.  
// student code here can be buggy, so it's in a try-catch
// block to try to handle problems.  If your code geeks,
// we play 'c' for you.  
char Battle::padded(Player* p, int r)
{
	//cout << "entering padded for " << p->getName() << endl;
	char c = 'x';
	try
   { //c = p->play(r); 
   // TODO: we need to take a turn here.  
   }
	catch (...)
	{
		cout << "error in play from " << p->getName() << endl;
		c = 'c';
	}
	return c;
}
*/

/*
// this function computes how many points go to the 
// first player here, the giver of 'my'.  It should be
// the same as the table in the writeup.
int Battle::slap( char my, char your )
{
    int ret=0;

    if ( my=='c' && your =='c' ) { ret = 5; }
    else if ( my=='c' && your =='d' ) { ret = 0; }
    else if ( my=='d' && your =='c' ) { ret = 6; }
    else if ( my=='d' && your =='d' ) { ret = 2; }

    return ret;
}*/

// prints out the score board.  If you want it sorted,
// do that before you call this.
void Battle::standings()
{
	int playerCount = (int)(players.size());

	cout << "\n\nstandings:\n";
	//sort();   

    for ( int i=0; i<playerCount; i++ )
    {
        players[i]->report();
    }
}

// de-allocate all of the Player objects.
Battle::~Battle()
{
    for ( auto p : players )
    {
        delete p;
    }
}


