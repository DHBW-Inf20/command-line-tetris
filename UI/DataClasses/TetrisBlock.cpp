#ifndef _tile_
#define _tile_
#include "Tile.cpp"
#endif

class TetrisBlock
{
    private:
        Tile matrix[4][4];
        int angle;
        int anchorPositionX;
        int anchorPositionY;

    public:
        void moveLeft();
        void moveRight();
        virtual void rotateRight()
        {

        }
        Tile** buildMatrix();
               
};