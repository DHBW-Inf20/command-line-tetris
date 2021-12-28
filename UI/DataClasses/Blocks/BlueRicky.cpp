#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class BlueRicky:TetrisBlock
{
    public:
        void rotateRight() override
        {
            switch (angle)
            {
            case 0:
                /*    X    
                      A
                    X X  */
                matrix[0][1] = matrix[0][0];
                matrix[1][1] = matrix[0][1];
                matrix[2][1] = matrix[0][2];
                matrix[2][0] = matrix[1][2];

                // Zurücksetzen der nun leeren Felder
                matrix[0][0] = nullptr;
                matrix[0][2] = nullptr;
                matrix[1][2] = nullptr;

                anchorPositionX = 1; // Spalte 1
                anchorPositionY = 1; // Reihe 1
                angle = 90;
                break;
            case 90:
                /* code */
                break;
            case 180:
                /* code */
                break;
            case 270:
                /* code */
                break;
            default:
                break;
            }
        }
        
        BlueRicky()
        {
            /*  X A X    
                    X  */
            matrix[0][0] = new Tile(Color::orange);
            matrix[0][1] = new Tile(Color::orange);
            matrix[0][2] = new Tile(Color::orange);
            matrix[1][2] = new Tile(Color::orange);
            anchorPositionX = 1; // Spalte 1
            anchorPositionY = 0; // Reihe 0
            angle = 0;
        }
};