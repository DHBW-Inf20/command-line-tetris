#ifndef _tile_
#define _tile_
#include "./DataClasses/Tile.cpp"
#endif

#include <stdio.h>

#include "../Utilities/AnsiEscape.h"

class UI
{
    private:
        Tile field [12][22];

    public:
        void draw();
};

void UI::draw()
{  
    clearScreen();
    for(int i=0; i<sizeof(field)/sizeof(field[0]);i++)
    {
        for(int j=0; j<sizeof(field[i])/sizeof(Tile);j++)
        {
            printf("■");
        }
        printf("\n");
    }
}