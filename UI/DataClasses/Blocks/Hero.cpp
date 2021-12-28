#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif
class Hero:TetrisBlock
{
    public:
        void rotateRight()override
        {
            
        }
        Hero()
        {
            // Color of Tiles: Turquise
            /*  
                X A X X  */
            matrix[1][0] = new Tile(Color::red);
            matrix[1][1] = new Tile(Color::red);
            matrix[1][1] = new Tile(Color::red);
            matrix[1][2] = new Tile(Color::red);
            anchorPositionX = 1; // Spalte 1
            anchorPositionY = 0; // Reihe 0
            angle = 0; 
        }            
        }
};