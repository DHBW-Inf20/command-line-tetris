#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class OrangeRicky:TetrisBlock
{
    public:
        void rotateRight()override
        {
            
        }
        OrangeRicky()
        {
            /*  X A X    
                X      */
            matrix[0][0] = new Tile(Color::orange);
            matrix[0][1] = new Tile(Color::orange);
            matrix[0][2] = new Tile(Color::orange);
            matrix[1][0] = new Tile(Color::orange);
            anchorPositionX = 1; // Spalte 1
            anchorPositionY = 0; // Reihe 0
            angle = 0;
        }
};