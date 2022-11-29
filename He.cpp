// Zhilin He
// ITP 165, 2022 fall
// HW 8 Battleship
#include "He.h"

// constructor.  passes the player name to Player.  
// You can add other setup things here if you want.
YourLastName::YourLastName( string n) : Player(n)
{
   // your code here ?
}

// brace takes a Coords as an argument and returns true if
// a torpedo there in myOcean hits a ship.  This is you
// reporting  fairly whether your ship was hit.  
// This is also the only chance you get to
// record this fact in case you want to do something about
// it.   (It may not help you that much to know if YOU are 
// being hit.)
bool YourLastName::brace( Coords c )
{
   myOcean[c.i][c.j].torpedo = true;
   return myOcean[c.i][c.j].ship; // leave this line in
}

// shoot() is a request to this Player to fire a
// torpedo at the opponent's ocean.  The return value
// is the place you want to shoot at your opponent.
// It is up to this you to record where you made this shot
// if you want to remember it.  

// Summary of my Strategy:
// 1. The algorithm will initialize a 7*7 dense matrix, each cell store a integer
// of the probablity of the a ship was put on that cell (dense prob). The 
// generalizes matrix looks like:
//      | 3 | 4 | 5 | 6 | 5 | 4 | 3 |
//      | 3 | 4 | 5 | 6 | 5 | 4 | 3 |
//      | 4 | 5 | 6 | 7 | 6 | 5 | 4 |
//。    ｜ 5 | 6 | 7 | 8 | 7 | 6 | 5 |
//      | 4 | 5 | 6 | 7 | 6 | 5 | 4 |
//      | 3 | 4 | 5 | 6 | 5 | 4 | 3 |
//      | 3 | 4 | 5 | 6 | 5 | 4 | 3 |
// the center cells have more probabilty to be put a ship.
// 2. if the player has not hit a ship, then fire the max probability, for example, // hit the center cell first, which dense prob == 8. then 7, then 6
// 3. if the player has hit a ship, check the location of the hitted cell, for example P(x,y), hit the horizontal or vertical neighbor cells of P(x, y) with max dense probability. For example, if cell(3,3) == 8 has a ship, then hit either neighbor with prob == 7
// 4. if the player has hit a ship, but last fire has missed, continue hit the neighbors of last hitted spot. 
// for example, cell(3,3) hitted, then cell (3,4) == 7 missed, so shoot either (4,3) == 7, (2,3) == 7, or (3,2) == 7;
// 5. if the player has hit two times or more, check the direction of the two shots, h or v. Then keep hitting horizontal or vertical neighbors.

// REMARK: 
// 1. every time when have shot at the cell, the density prob of the cell will become 0 if misses the shot.
// 2. every time when have shot at the cell, the density prob of the cell will become -1 if hit the ship.

// Results: the strategy can bit Bkoster player with around 6:4, and bit Random player with 10:0.
Coords YourLastName::shoot()
{  
  // your code here
   // Here is a place where you need to put some code.  Where do you
   // shoot next?  What is your strategy?  The variable 
   // yourOcean[][] is there for you to record all of your 
   // previous torpedos and whether they hit a ship. 

  // always shoot the cell with the most prob
  Coords where;
  if (yourOcean[shot.i][shot.j].ship){
    dense[shot.i][shot.j].prob = -1;
    lasthit.i = shot.i;
    lasthit.j = shot.j;
    where = makeMove(shot);
  } else if (yourOcean[lasthit.i][lasthit.j].ship){
    where = makeMove(lasthit);
  }else{
    int counter = 0;
    for (int i = 0; i<OCEAN_SIZE; i++){
      for (int j =0; j<OCEAN_SIZE; j++){ 
        if(dense[i][j].prob == maxValue){
          where.i = i;
          where.j = j;
          counter ++;
        }
      }
    }
    if (counter == 1){
      maxValue --;
    } 
  }
  
  shot.i = where.i;
  shot.j = where.j;
  dense[where.i][where.j].prob = 0;
  yourOcean[where.i][where.j].torpedo = true;
  return where;
}

// This is the system reporting to you the results
// of shooting at the other player 
// as Coords c, hit=true is a hit, false=miss.  
// You should at least record that you fired a torpedo
// here and whether there is a ship or not
// at this location in yourOcean (the other player's).  
// You may also 
// want to set up information for your next shot 
// (depending on whether you hit or missed).
void YourLastName::sound( Coords c, bool hit )
{
   // your code here
  yourOcean[c.i][c.j].ship = hit;
}


// This function is called before a match starts,
// before the two players start firing torpedos. 
// At the very least, you need to put a ship in
// your ocean, 4 consecutive cells verticle or
// horizontal (with ship=true).  You may also
// set up anything else you like for your strategy.

// start the game
void YourLastName::matchInit()
{
    // your code here
    shot.i = 2;
    shot.j = 1;
    clearOcean( myOcean );
    clearOcean( yourOcean );
    initDenseP();
    putShip(myOcean);
}

// function for put the ship
void YourLastName::putShip(  Cell oc[OCEAN_SIZE][OCEAN_SIZE])
{
  // we always want to put the ship in the lowest dense probability
  // which are 4 conners;
  int place = rand()%CONNER_NUMBERS; // generate a random conner
  int direction = rand()%2; // direction to put 0 for h, 1 for v
  
  if (place == 0){
    if (direction == 0){
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[0][j].ship = true;
      }
    }else{
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[j][0].ship = true;
      }  
    }
    
  }else if (place == 1){
    if (direction == 0){
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[0][3 + j].ship = true;
      }
    }else{
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[j][OCEAN_SIZE - 1].ship = true;
      }  
    }
    
  }else if (place == 2){
    if (direction == 0){
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[OCEAN_SIZE - 1][j].ship = true;
      }
    }else{
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[0][3 + j].ship = true;
      }  
    }
    
  }else if (place == 3){
    if (direction == 0){
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[OCEAN_SIZE - 1][3 + j].ship = true;
      }
    }else{
      for (int j = 0; j<SHIP_SIZE; j++){
         oc[3 + j][OCEAN_SIZE - 1].ship = true;
      }  
    }  
  }
}

// initial the dense matrix
void YourLastName::initDenseP(){
  // init the dense board
  for (int i = 0; i<OCEAN_SIZE; i++){
    for (int j =0; j<OCEAN_SIZE; j++){
      dense[i][j].prob = 0;
    }
  }

  // if we put the ship horizontally
  for (int row = 0; row<OCEAN_SIZE; row++){
    for (int col = 0; col<OCEAN_SIZE - SHIP_SIZE + 1; col++){
      for (int j = 0; j<SHIP_SIZE; j++){
        dense[row][col+j].prob ++;
      }
    }
  }

  // if we put the ship vertically
  for (int col = 0; col<OCEAN_SIZE; col++){
    for (int row = 0; row<OCEAN_SIZE - SHIP_SIZE + 1; row++){
      for (int j = 0; j<SHIP_SIZE; j++){
        dense[row+j][col].prob ++;
      }
    }
  }

  int min = 100;
  int max = 0;
  for (int i = 0; i<OCEAN_SIZE; i++){
    for (int j =0; j<OCEAN_SIZE; j++){
      if (dense[i][j].prob > max){
        max = dense[i][j].prob;
      }else if (dense[i][j].prob < min){
        min = dense[i][j].prob;
      }
    }
  }
  minValue = min;
  maxValue = max;
}

// helper function for print the dense board
void YourLastName::printDenseBoard(){
  for (int i = 0; i<OCEAN_SIZE; i++){
    for (int j =0; j<OCEAN_SIZE; j++){
      cout << dense[i][j].prob;
    }
    cout << endl;
  }
}

// check the how many cell that fired hitted total
int YourLastName::checkHitNumber(){
  int counter = 0;
  for (int i = 0; i<OCEAN_SIZE; i++){
    for (int j =0; j<OCEAN_SIZE; j++){
      if( dense[i][j].prob == -1){
        counter ++;
      }
    }
  }
  return counter;
}

// check the direction of two or more hitts, 0 for h and 1 for vertical
int YourLastName::checkHitDirection(){
  int counter = 0;
  Coords where;
  for (int i = 0; i<OCEAN_SIZE; i++){
    for (int j =0; j<OCEAN_SIZE; j++){
      if( dense[i][j].prob == -1){
        
        if (counter == 1){
          if (where.i == i){
            return 0;
          }else if (where.j ==j){
            return 1;
          }
        }else{
          where.i = i;
          where.j = j;
          counter ++;
        }    
      }
    }
  }
}

// determine which neighbor cell to put the next shoot
Coords YourLastName::makeMove(Coords shot){
  Coords where;
  if (checkHitNumber() == 1){
      if ( (shot.i > 0 && shot.j > 0) && (shot.i + 1 < OCEAN_SIZE && shot.j + 1 < OCEAN_SIZE)){
        // in the middle, look for horizontal and vertical neighbors max value
        where = checkBoth(shot);
      } else if(shot.i == 0 || shot.i == OCEAN_SIZE -1) {
        // at first or last row, only look for horizontal neighbors max value
        where = checkHorizontal(shot);
      } else if(shot.j == 0 || shot.j == OCEAN_SIZE -1) {
        // at first or last col, only look for vertical neighbors max value
        where = checkVertical(shot);   
      }
    }else if (checkHitNumber() == 2 || checkHitNumber() == 3){
     // if hit twice or three times, check direction of hits
      if (checkHitDirection() == 0){
        // direction is h, only look for horizontal neighbors max value
        where = checkHorizontal(shot);     
      } else {
        // direction is v, only look for vertical neighbors max value
        where = checkVertical(shot);     
      }
    }
  return where;
}

// check which horizontal neighbors to put the next shoot
Coords YourLastName::checkHorizontal(Coords shot){
  int max = 0;
  Coords where;
  for (int j = shot.j -1; j<shot.j +2; j++){
    if (dense[shot.i][j].prob > max){ max = dense[shot.i][j].prob; }
  } 
  for (int j = shot.j -1; j<shot.j +2; j++){
    if (dense[shot.i][j].prob == max){where.i = shot.i;where.j = j;}
  }
  return where;
}

// check which vertical neighbors to put the next shoot
Coords YourLastName::checkVertical(Coords shot){
  Coords where;
  int max = 0;
  for (int i = shot.i -1; i<shot.i +2; i++){
    if (dense[i][shot.j].prob > max){max = dense[i][shot.j].prob; }
  } 
  for (int i = shot.i -1; i<shot.i +2; i++){
    if (dense[i][shot.j].prob == max){where.i = i;where.j = shot.j;}
  }
  return where;
}

// check which horizontal or vertical neighbors to put the next shoot
Coords YourLastName::checkBoth(Coords shot){
  Coords where;
  int max = 0;
  // check horizontal neighbors
  for (int i = shot.i -1; i< shot.i +2; i++){
    for (int j = shot.j -1; j<shot.j +2; j++){
      if (dense[i][j].prob > max){ max = dense[i][j].prob; }
    } 
  }
  // check vertical neighbors
  for (int i = shot.i -1; i<shot.i +2; i++){
    for (int j = shot.j -1; j<shot.j +2; j++){
      if (dense[i][j].prob == max){ where.i = i; where.j = j;}
    } 
  }
  return where;
}


