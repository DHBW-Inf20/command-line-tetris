#include "../TetrisBlock.h"
#include "OrangeRicky.h"

#include "../../../Utilities/MemoryLeakDetection.h"


OrangeRicky::OrangeRicky(const TetrisBlock& block) : TetrisBlock(block)
        {
        
        }

        TetrisBlock* OrangeRicky::Clone()
        {
	        auto* const a = new OrangeRicky(*this);
            return a;
        };

        void OrangeRicky::RotateRight()
        {
            switch (angle)
            {
            case 0:
                /*  X X
                      A  
                      X    */
                matrix[0][0] = matrix[2][0];
                matrix[1][1] = matrix[1][1]; // same
                matrix[0][1] = matrix[1][0];
                matrix[2][1] = matrix[1][2];
                angle = 90;

                // Rücksetzen der nun leeren Felder
                matrix[2][0] = nullptr;
                matrix[1][0] = nullptr;
                matrix[1][2] = nullptr;
                break;

            case 90:
                /*      X
                    X A X   */
                matrix[0][2] = matrix[0][0];
                matrix[1][1] = matrix[1][1]; // same
                matrix[1][0] = matrix[2][1];
                matrix[1][2] = matrix[0][1];
                angle = 180;

                // Rücksetzen der nun leeren Felder
                matrix[0][0] = nullptr;
                matrix[2][1] = nullptr;
                matrix[0][1] = nullptr;
                break;

            case 180:
                /*    X
                      A
                      X X   */
                matrix[0][1] = matrix[1][0];
                matrix[1][1] = matrix[1][1]; // same
                matrix[2][1] = matrix[1][2];
                matrix[2][2] = matrix[0][2];
                angle = 270;

                // Rücksetzen der nun leeren Felder
                matrix[1][0] = nullptr;
                matrix[1][2] = nullptr;
                matrix[0][2] = nullptr;
                break;

            case 270:
                /*
                    X A X
                    X       */
                matrix[1][0] = matrix[2][1];
                matrix[1][1] = matrix[1][1]; // same
                matrix[1][2] = matrix[0][1];
                matrix[2][0] = matrix[2][2];
                angle = 0;

                // Rücksetzen der nun leeren Felder
                matrix[2][1] = nullptr;
                matrix[2][2] = nullptr;
                matrix[0][1] = nullptr;
                break;
            
            default:
                break;
            }
        }
        OrangeRicky::OrangeRicky()
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
