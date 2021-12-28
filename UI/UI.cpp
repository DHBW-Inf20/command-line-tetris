#ifndef _tile_
#define _tile_
#include "./DataClasses/Tile.cpp"
#endif

#include <stdio.h>

#include "../Utilities/AnsiEscape.h"

class UI
{
    private:
        Color actualColor;
        int colorTesting; // Testzwecke
        Tile * field [22][12];
        void init()
        {
            colorTesting = 0;
            
            // Clear Field
            for(int b = 0; b < 22; b++)
            {
                for(int c = 0; c < 12; c++)
                {
                    field[b][c] = nullptr;
                }
            }
            
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
        /* ~UI() Irgendwie so geht das
        {
            for(int f = 0; f < 22; f++)
            {
                delete [] field[f];
            }
            delete [] field;
        } */
};

void UI::draw()
{   
    colorTesting++; // für testzwecke
    hideCursor();
    clearLine();
    for(int i=0; i<=sizeof(field)/sizeof(field[0]);i++)
    {        
        for(int j=0; j<=sizeof(field[i])/sizeof(Tile *);j++)
        {                  
            if(field[i][j] != nullptr) // Sicherstellen, dass ein Objekt existiert
            {
                // Irgendwo in diesem IF gibt es einen Fehler, der zu stackdumpfile führt
                actualColor = field[i][j]->getColor();
                switch (actualColor)
                {
                case Color::yellow:
                    setTextColor(YELLOW_TXT);
                    break;
                case Color::black:
                    if((colorTesting%2) == 0) // Für Testzwecke. Er kommt hier rein, dann aber kein 2. mal
                        setTextColor(BLACK_TXT);
                    else
                        setTextColor(BLUE_TXT);
                    break;
                case Color::blue:
                    setTextColor(BLUE_TXT);
                    break;
                case Color::green:
                    setTextColor(GREEN_TXT);
                    break;
                case Color::orange:
                    setTextColor(WHITE_TXT); // Eigentlich orange, gibt es jedoch nicht bei dem ANSI Zeugs!!! 
                    break;
                case Color::red:
                    setTextColor(RED_TXT);
                    break;
                case Color::turquoise:
                    setTextColor(CYAN_TXT);
                    break;
                case Color::purple:
                    setTextColor(MAGENTA_TXT);
                    break;
                default:
                    setTextColor(WHITE_TXT);
                    break;
                }
            }     
            else
            {
                setTextColor(WHITE_TXT); // Kein Tile)(nullptr) => White
            }               
            moveTo(i,j);
            moveUp(1);     
            puts("█");      
        }  
     
    } 
    moveTo(0,0);
}