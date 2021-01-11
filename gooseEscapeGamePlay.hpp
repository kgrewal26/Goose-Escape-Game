//**************START OF GAMEPLAY.HPP FILE**************

#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"


// Going further:  Learn how to use an enum for these values
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int HAMMER = 3;

//a new constant made for max levels:
const int MAX_LEVEL = 3;
	
//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('O');
const int WIN_CHAR = int('%'); //% sign, a special character used in the ancient game "Rogue"
const int HAMMER_CHAR = int('H');


//These functions print locate and print the objects and actors to terminal
void printActors(ifstream & fin, Actor & player, Actor & monster, int & lvlNum);
void printTerminal(int gameBoard[NUM_BOARD_X][NUM_BOARD_Y]);
void readObjects(int gameBoard[NUM_BOARD_X][NUM_BOARD_Y], ifstream & fin);

//these two make it possible for walls to be broken.
// Will be frequently called
void onHammer(Actor & player, int gameBoard[NUM_BOARD_X][NUM_BOARD_Y]);
bool canMoveOnWall(Actor & player, int gameBoard[NUM_BOARD_X][NUM_BOARD_Y], 
                         int xMove, int yMove);
                         
bool captured(Actor const & player, Actor const & monster);

//these two functions move the goose - read actual function for more info
void moveGoose(Actor & goose, Actor const & player);
void findDirection(Actor & goose,Actor const & player, int changeX,int changeY);


void movePlayer(int key,Actor & player,int gameBoard[NUM_BOARD_X][NUM_BOARD_Y]);

bool hasWon(Actor const & player, int gameBoard[NUM_BOARD_X][NUM_BOARD_Y]);
#endif
//**************END OF GAMEPLAY.HPP FILE**************
