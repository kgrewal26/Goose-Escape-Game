//**************START OF ACTOR CLASS**************
#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

//new constant for the uses in a new hammer
const int NEW_HAMMER = 3;

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;
    
    //our added data type - allows players to break through walls
    //the value represents how many more times the player can break a wall
    //note that the goose can do this on its own (without a hammer)
    int hammerLeft;
    
  public:
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        hammerLeft = 0;
        put_actor();
    }

    Actor(char initPlayerChar, int x0, int y0)
    {
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        hammerLeft = 0;
        update_location(x0,y0);
    }
    
    //added function to see if the actor has a hammer usage
    int getHammer() const
    {
        return hammerLeft;
    }
    
    //if the player uses the hammer, this will decrease the usage
    void usedHammer()
    {
        hammerLeft--;
    }
    
    //if the user picksup a new hammer, this will give them 3 more uses
    void pickUpHammer()
    {
        hammerLeft += NEW_HAMMER;
    }
    
    int get_x() const
    {
        return location_x;
    }
    
    int get_y() const
    {
        return location_y;
    }
    
    string get_location_string() const
    {
        char buffer[80];
        itoa(location_x,buffer,10);
        string formatted_location = "(" + string(buffer) + ",";
        itoa(location_y,buffer,10);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }
    
    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'),max(int(new_actor_char),int(' ')));
    }

    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
          && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }
    
    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
    }
    
    //we added this
    void changeCoords(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            location_x += delta_x;
            location_y += delta_y;
        }
    }
    
    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }
    
    double findDistance(Actor const & other) const
    {
        return sqrt(pow(((*this).location_x - other.location_x),2) +
                   pow(((*this).location_y - other.location_y), 2));
    }
    
};
#endif
//**************END OF ACTOR CLASS**************
