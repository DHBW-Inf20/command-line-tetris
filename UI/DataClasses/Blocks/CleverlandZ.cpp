#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class CleverlandZ: public TetrisBlock
{
    public:
        void rotateRight()override
        {
            switch (angle)
            {
            case 0:
            /* case 180: */
                /*      X    
                      A X
                      X    */
                matrix[0][2] = matrix[0][0];
                matrix[1][2] = matrix[0][1];
                matrix[1][1] = matrix[1][1]; // stays same
                matrix[2][1] = matrix[1][2];

                // Zurücksetzen der nun leeren Felder
                matrix[0][0] = nullptr;
                matrix[0][1] = nullptr;

                angle = 90; 
                break;
            case 90:
            /* case 270: */
                /*  X X     
                      A X  */
                matrix[0][0] = matrix[0][2];
                matrix[0][1] = matrix[1][2];
                matrix[1][1] = matrix[1][1]; // stays same
                matrix[1][2] = matrix[2][1];

                // Zurücksetzen der nun leeren Felder
                matrix[0][2] = nullptr;
                matrix[2][1] = nullptr;

                angle = 0; 
                break;
            
            default:
                break;
            }
        }
        CleverlandZ()
        {
            /*  X X     
                  A X  */
            matrix[0][0] = new Tile(Color::red);
            matrix[0][1] = new Tile(Color::red);
            matrix[1][1] = new Tile(Color::red);
            matrix[1][2] = new Tile(Color::red);
            angle = 0; 
        }
};