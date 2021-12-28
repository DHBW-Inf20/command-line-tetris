#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class Teewee:public TetrisBlock
{
    public:
        void rotateRight()override
        {
            
        }
        Teewee()
        {
            // Color of Tiles: Purple
            /*  X A X     
                  X    */
            matrix[1][1] = new Tile(Color::purple);
            matrix[0][0] = new Tile(Color::purple);
            matrix[0][1] = new Tile(Color::purple);
            matrix[0][2] = new Tile(Color::purple);
            anchorPositionX = 1; // Spalte 1
            anchorPositionY = 0; // Reihe 0
            angle = 0; 
        }
};