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
            /*  
                X A X     
                  X    */
            matrix[2][1] = new Tile(Color::purple);
            matrix[1][0] = new Tile(Color::purple);
            matrix[1][1] = new Tile(Color::purple);
            matrix[1][2] = new Tile(Color::purple);
            angle = 0; 
        }
};