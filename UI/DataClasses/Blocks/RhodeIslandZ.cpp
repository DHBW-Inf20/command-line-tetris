#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class RhodeIslandZ:TetrisBlock
{
    public:
        void rotateRight()override
        {
            
        }
        RhodeIslandZ()
        {
            /*    X X     
                X A    */
            matrix[0][2] = new Tile(Color::green);
            matrix[0][1] = new Tile(Color::green);
            matrix[1][1] = new Tile(Color::green);
            matrix[1][0] = new Tile(Color::green);
            anchorPositionX = 1; // Spalte 1
            anchorPositionY = 1; // Reihe 1
            angle = 0; 
        }
        }
};