#ifndef _tile_
#define _tile_
#include "./DataClasses/Tile.cpp"
#endif

#include <stdio.h>

#include "../Utilities/AnsiEscape.h"

class UI
{
    private:
        Tile field [22][12];

    public:
        void draw();
};

int ji;

void UI::draw()
{   
    hideCursor();
    clearLine();
    for(int i=0; i<sizeof(field)/sizeof(field[0]);i++)
    {          
        for(int j=0; j<sizeof(field[i])/sizeof(Tile);j++)
        {                  
            if(j==ji)
            {
                setTextColor(BLUE_TXT);
            }     
            else{
                 setTextColor(RESET_COLOR);
            }                
            moveTo(i,j);
            moveUp(1);     
            puts("■");          
        }  
     
    } 

    
    moveTo(0,0);
    if(ji>10)
    ji=0;
    else
    ji++;
}