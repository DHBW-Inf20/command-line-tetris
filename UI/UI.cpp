#ifndef _tile_
#define _tile_
#include "./DataClasses/Tile.cpp"
#endif

#include <stdio.h>

#include "../Utilities/AnsiEscape.h"

#ifndef _config_
#define _config_
#include "Config.cpp"
#endif

#ifndef _utilities_
#define _utilities_
#include "../Utilities/Utilities.h"
#endif


class UI
{
    private:
        Color actualColor;            

    public:
        void draw(std::vector<std::vector<Tile*>>); // [Reihe][Spalte]);
        UI()
        {
               
        }
        
        void init(std::vector<std::vector<Tile*>> & field)
        {
            clearScreen();   
            
            // Clear Field
            for(int b = 0; b < rowCount; b++)
            {
                for(int c = 0; c < columnCount; c++)
                {
                    field[b][c] = nullptr;
                }
            }
            
            for(int k = 0; k < columnCount; k++)
            {   // Oben und Unten Rand
                field[0][k] = new Tile(Color::black);
                field[rowCount-1][k] = new Tile(Color::black);
            }
            
            // Die obersten zwei Zeilen fehlen, deshalb +1 put
            // Die linkeste Zeile fehlt, deshalb +1 bei put

            for(int h = 1; h < rowCount-1; h++)
            {   // Links und Rechts Rand, [1;21] weil die bei der anderen schon gemacht wurden
                field[h][0] = new Tile(Color::black);
                field[h][columnCount-1] = new Tile(Color::black);
            }
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

void UI::draw(std::vector<std::vector<Tile*>> field) // [Reihe][Spalte])
{          
    clearLine();
    hideCursor();
    for(int i=0; i<rowCount;i++)
    {        
        for(int j=0; j<columnCount;j++)
        {                  
            if(field[i][j] != nullptr) // Sicherstellen, dass ein Objekt existiert
            {
                actualColor = field[i][j]->getColor();
                switch (actualColor)
                {
                case Color::yellow:
                    setTextColor(YELLOW_TXT);
                    break;
                case Color::black:
                    setTextColor(BLACK_TXT);
                    break;
                case Color::blue:
                    setTextColor(BLUE_TXT);
                    break;
                case Color::green:
                    setTextColor(GREEN_TXT);
                    break;
                case Color::orange:
                    setTextColor(BLUE_TXT); // Eigentlich orange, gibt es jedoch nicht bei dem ANSI Zeugs!!! @JDEV
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
                setTextColor(WHITE_TXT); // Kein Tile(nullptr) => White
            }               
            moveTo(i+1,(j*2)+1);
            puts("██"); //▉
            moveUp(1);                
        }  
     
    } 
    moveTo(0,0);
}