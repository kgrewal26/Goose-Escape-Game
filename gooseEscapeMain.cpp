//**************START OF MAIN**************

#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

	// Printing the instructions
    out.writeLine("Escape the Goose!");
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");
	out.writeLine("You can pickup a Hammer(H) to break through walls!");
	out.writeLine("Each Hammer only has 3 Uses!");
	//files with actor & object locations per level
	ifstream actorsIn("actorLocations.txt");
    ifstream objectsIn("objectLocations.txt");
   
    //create actors player and goose
    Actor player; 
    Actor monster;

	int lvlNum = 0;
    int keyEntered = TK_A;
    
	while (lvlNum < MAX_LEVEL && keyEntered != TK_ESCAPE && keyEntered 
          != TK_CLOSE && captured(player, monster))
    {    
       	int gameBoard[NUM_BOARD_X][NUM_BOARD_Y] = {0};
           
        //read objects locations and print actors
        readObjects(gameBoard, objectsIn);
        printTerminal(gameBoard);
        printActors(actorsIn, player, monster, lvlNum);
        
        out.writeLine("Starting Level") ;

   	    
   	    keyEntered = TK_A;
        while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
                        && !captured(player,monster) && !hasWon(player, gameBoard))
    	{
    	    //get player key press
    	    keyEntered = terminal_read();
            
            if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
            {
     
        	    movePlayer(keyEntered,player, gameBoard);
                onHammer(player, gameBoard);
                moveGoose(monster, player);
                	    
            }
      	}
        
        if (keyEntered != TK_CLOSE)
        {
        
            if (hasWon(player, gameBoard))
            {
                out.writeLine("The player successfully reached the safezone!");
                
                //this sends the player back to 0,0
                //-1 since the function takes delta x and y as parameters
                player.update_location(-1*player.get_x(), -1*player.get_y());
                monster.update_location(-1*monster.get_x(), -1*monster.get_y());
                terminal_clear();
            }
            else if (captured(player, monster)) //added for extra insurance
            {
                out.writeLine("Oh No! The goose caught you!");
                out.writeLine("Now you need to tranfer to UofT! :(");
                
                //moved this line here so it only happens when they lose
                while (terminal_read() != TK_CLOSE);
                terminal_close();
            }
        }
    }
	out.writeLine("You have beaten the game!");
	while (terminal_read() != TK_CLOSE);
	cout << "end";
    terminal_close();
}

//**************END OF MAIN**************
