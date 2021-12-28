#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class CleverlandZ:TetrisBlock
{
    public:
        void rotateRight()override
        {
            
        }
        CleverlandZ()
        {
            /*  X X     
                  A X  */
            matrix[0][0] = new Tile(Color::red);
            matrix[0][1] = new Tile(Color::red);
            matrix[1][1] = new Tile(Color::red);
            matrix[1][2] = new Tile(Color::red);
            anchorPositionX = 1; // Spalte 1
            anchorPositionY = 1; // Reihe 1
            angle = 0; 
        }
};