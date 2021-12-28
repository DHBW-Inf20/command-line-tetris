#ifndef _tile_
#define _tile_
#include "Tile.cpp"
#endif

class TetrisBlock
{
    protected:
        Tile * matrix[4][4]; // [Reihe][Spalte] -> [Y][X]
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
        // Erbende Klassen ggf. noch eine Init-Methode, wo die 4x4-Matrix befüllt wird
               
};