#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif

class Teewee:public TetrisBlock
{
    public:
        Teewee(const TetrisBlock& block) : TetrisBlock(block)
        {
        }

        TetrisBlock* clone(TetrisBlock* block) override
        {
            auto a = new Teewee(*block);
            return a;
        };
        
        void rotateRight() override
        {
            switch (angle)
            {
            case 0:
                /*    X
                    X A     
                      X  */
                matrix[0][1] = matrix[1][0];
                matrix[1][0] = matrix[2][1];
                matrix[1][1] = matrix[1][1]; // same
                matrix[2][1] = matrix[1][2];
                
                // Zurücksetzen der nun leeren Felder
                matrix[1][2] = nullptr;

                angle = 90; 
                break;

            case 90:
                /*    X
                    X A X   */
                matrix[0][1] = matrix[1][0];
                matrix[1][0] = matrix[2][1];
                matrix[1][1] = matrix[1][1]; // same
                matrix[1][2] = matrix[0][1];
                
                // Zurücksetzen der nun leeren Felder
                matrix[2][1] = nullptr;

                angle = 180; 
                break;

            case 180:
                /*    X
                      A X
                      X     */
                matrix[0][1] = matrix[1][0];
                matrix[1][2] = matrix[0][1];
                matrix[1][1] = matrix[1][1]; // same
                matrix[2][1] = matrix[1][2];
                
                // Zurücksetzen der nun leeren Felder
                matrix[1][0] = nullptr;

                angle = 270; 
                break;

            case 270:
                /*    
                    X A X
                      X     */
                matrix[1][0] = matrix[2][1];
                matrix[1][2] = matrix[0][1];
                matrix[1][1] = matrix[1][1]; // same
                matrix[2][1] = matrix[1][2];
                
                // Zurücksetzen der nun leeren Felder
                matrix[0][1] = nullptr;

                angle = 0; 
                break;

            default:
                break;
            }
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