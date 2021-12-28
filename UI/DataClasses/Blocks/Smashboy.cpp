#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif
class Smashboy:TetrisBlock
{
    public:
        void rotateRight()override
        {
            
        }
        Smashboy()
        {
            /*    X X     
                  X X  */
            matrix[0][1] = new Tile(Color::yellow);
            matrix[0][2] = new Tile(Color::yellow);
            matrix[1][1] = new Tile(Color::yellow);
            matrix[1][2] = new Tile(Color::yellow);
            anchorPositionX = 1; // Spalte 1
            anchorPositionY = 1; // Reihe 1
            angle = 0;
        }
        }
};