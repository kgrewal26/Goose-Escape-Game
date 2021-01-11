//**************START OF GAMEPLAY.CPP FILE**************
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/


//new function to print the actors - this helps will multiple levels
void printActors(ifstream & fin, Actor & player, Actor & monster, int & lvlNum)
{
    /** each file will look like this:
	lvl #, actor x actor y, monster x monster y
	**/
	
	//get the lvl number (its passed in by reference, no return needed.
	fin >> lvlNum;
	
	int playerX = 0, playerY = 0, monsterX = 0, monsterY = 0;
	
	//read in player and monster locations
	fin >> playerX >> playerY >> monsterX >> monsterY;
	
	//update the chars and place them at the locations read above
	player.change_char(PLAYER_CHAR);
	player.update_location(playerX, playerY);

	monster.change_char(MONSTER_CHAR);
	monster.update_location(monsterX, monsterY);
}

//we created this
void printTerminal(int gameBoard[NUM_BOARD_X][NUM_BOARD_Y])
{
    //loop through gameboard
    for (int x_location = 0; x_location < NUM_BOARD_X; x_location++)
    {
        for (int y_location = 0; y_location < NUM_BOARD_Y; y_location++)
        {
            //print the character based off the object thats there
            if ( gameBoard[x_location][y_location] == SHALL_NOT_PASS)
            {
                terminal_put(x_location, y_location, WALL_CHAR);
    
            }
            else if (gameBoard[x_location][y_location] == WINNER)
            {
                terminal_put(x_location, y_location, WIN_CHAR);
            }
            else if (gameBoard[x_location][y_location] == HAMMER)
            {
                terminal_put(x_location, y_location, HAMMER_CHAR);
            }
        }
    }

}

//new function to print out walls and safezones
void readObjects(int gameBoard[NUM_BOARD_X][NUM_BOARD_Y], ifstream & fin)
{ 
    /** file will look like this:
    # of walls
    x and y locations of all walls
    location of safezone
    location of hammer
    
    repeated for all levels 
    **/
    int walls = 0;
    fin >> walls;
    
    //go through all walls and set
    for (int index = 0; index < walls; index++)
    {
        int wallX = 0;
        int wallY = 0;
        
        fin >> wallX >> wallY;
        
        gameBoard[wallX][wallY] = SHALL_NOT_PASS;
        
    }
    
    //read in the safezone location and place
    int safezoneX = 0, safezoneY = 0;
    fin >> safezoneX >> safezoneY;
    gameBoard[safezoneX][safezoneY] = WINNER;
    
    int hammers = 0;
    fin >> hammers;
    
    for (int count = 0; count < hammers; count++)
    {
        int hammerX = 0, hammerY = 0;
        fin >> hammerX >> hammerY;
        gameBoard[hammerX][hammerY] = HAMMER;
    }
}

void onHammer(Actor & player, int gameBoard[NUM_BOARD_X][NUM_BOARD_Y])
{  
   
    //if the user is on the hammer location
    if (gameBoard[player.get_x()][player.get_y()] == HAMMER)
    {
        //pick up the hammer
        player.pickUpHammer();
        out.writeLine("You picked up a hammer");
    }
}

bool canMoveOnWall(Actor & player, int gameBoard[NUM_BOARD_X][NUM_BOARD_Y],
                         int xMove, int yMove)
{  
   //if the player is at a wall location
    if (gameBoard[player.get_x() + xMove][player.get_y() + yMove] 
        == SHALL_NOT_PASS)
    {
        //check if they have a hammer
        if (player.getHammer() > 0)
        {
            //if they have a hammer use it up, tell them
            //and allow them to pass over wall (return true)
            player.usedHammer();
            out.writeLine("You just used a hammer!");
            return true;
        }
        //if they dont have a hammer dont let them move
        return false;
    }
    
    //if they arent on a wall, they can move freely regardless
    return true;
}
bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
}

void movePlayer(int key, Actor & player,int gameBoard[NUM_BOARD_X][NUM_BOARD_Y])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
        
    if (player.can_move(xMove, yMove) && 
         canMoveOnWall(player, gameBoard, xMove, yMove))
    {
        player.update_location(xMove, yMove);
    }       
}

//we created this
void moveGoose(Actor & goose, Actor const & player)
{
    //will test and move the goose in all 4 directions (x,-x,y,-y)
    //better explained in the find direction function
    findDirection(goose, player, 1, 0);
    findDirection(goose, player, -1, 0);
    findDirection(goose, player, 0, 1);
    findDirection(goose, player, 0, -1);
}

//we created this
void findDirection(Actor & goose, Actor const & player, int changeX,int changeY)
{
    Actor temp(MONSTER_CHAR, goose.get_x(), goose.get_y());
    
    //takes current distance from player to goose
    double dist = goose.findDistance(player);
    
    //changes the coordinates on a temporary actor
    temp.changeCoords(changeX, changeY);
    
    //if that temporary actor is closer than the current distance
    if (player.findDistance(temp) < dist)
    {
        //move the goose to that location
        goose.update_location(changeX, changeY);
    }
}

//we created this
bool hasWon(Actor const & player, int gameBoard[NUM_BOARD_X][NUM_BOARD_Y])
{
    return gameBoard[player.get_x()][player.get_y()] == WINNER;
}

//**************END OF GAMEPLAY.CPP FILE**************
