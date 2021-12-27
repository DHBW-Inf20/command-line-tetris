#ifndef _tile_
#define _tile_
#include "./DataClasses/Tile.cpp"
#endif

#include <stdio.h>

#include "../Utilities/AnsiEscape.h"

class UI
{
    private:
        Tile * field [22][12];
        void init()
        {
            for(int k = 0; k < 12; k++)
            {   // Oben und Unten Rand
                field[0][k] = new Tile(Color::black);
                field[21][k] = new Tile(Color::black);
            }
            for(int h = 1; h < 21; h++)
            {   // Links und Rechts Rand
                field[h][0] = new Tile(Color::black);
                field[h][11] = new Tile(Color::black);
            }
        }

    public:
        void draw();
        UI()
        {
            clearScreen();
            init();
        }
};

int ji;

void UI::draw()
{   
    hideCursor();
    clearLine();
    for(int i=0; i<sizeof(field)/sizeof(field[0]);i++)
    {        
        for(int j=0; j<sizeof(field[i])/sizeof(Tile *);j++)
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
            puts("█");      
        }  
     
    } 

    
    moveTo(0,0);
    if(ji>10)
    ji=0;
    else
    ji++;
}