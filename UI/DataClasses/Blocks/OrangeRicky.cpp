#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class OrangeRicky:public TetrisBlock
{
    public:
        void rotateRight()override
        {
            
        }
        OrangeRicky()
        {
            /*  
                X A X    
                X      */
            matrix[1][0] = new Tile(Color::orange);
            matrix[1][1] = new Tile(Color::orange);
            matrix[1][2] = new Tile(Color::orange);
            matrix[2][0] = new Tile(Color::orange);
            angle = 0;
        }
};