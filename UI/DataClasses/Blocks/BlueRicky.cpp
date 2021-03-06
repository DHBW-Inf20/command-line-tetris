#include "BlueRicky.h"
#include "../TetrisBlock.h"
#include "../../../Utilities/MemoryLeakDetection.h"



BlueRicky::BlueRicky(const TetrisBlock& block) : TetrisBlock(block)
       {
       }

          TetrisBlock* BlueRicky::Clone()
        {
	        auto* const a = new BlueRicky(*this);
            return a;
        };

        void BlueRicky::RotateRight()
        {
            switch (angle)
            {
            case 0:
                /*    X    
                      A
                    X X  */
                matrix[0][1] = matrix[1][0];
                matrix[1][1] = matrix[1][1]; //stays same
                matrix[2][1] = matrix[1][2];
                matrix[2][0] = matrix[2][2];

                // Zurücksetzen der nun leeren Felder
                matrix[1][0] = nullptr;
                matrix[1][2] = nullptr;
                matrix[2][2] = nullptr;

                angle = 90;
                break;

            case 90:
                /*  X    
                    X A X
                      */
                matrix[0][0] = matrix[2][0];
                matrix[1][0] = matrix[2][1];
                matrix[1][1] = matrix[1][1]; //stays same
                matrix[1][2] = matrix[0][1];

                // Zurücksetzen der nun leeren Felder
                matrix[2][0] = nullptr;
                matrix[2][1] = nullptr;
                matrix[0][1] = nullptr;

                angle = 180;
                break;

            case 180:
                 /*    X X 
                       A 
                       X     */
                matrix[0][2] = matrix[0][0];
                matrix[0][1] = matrix[1][0];
                matrix[1][1] = matrix[1][1]; //stays same
                matrix[2][1] = matrix[1][2];

                // Zurücksetzen der nun leeren Felder
                matrix[0][0] = nullptr;
                matrix[1][0] = nullptr;
                matrix[1][2] = nullptr;

                angle = 270;
                break;

            case 270:
                 /*     
                    X  A  X
                          X   */

                matrix[2][2] = matrix[0][2];
                matrix[1][2] = matrix[0][1];
                matrix[1][1] = matrix[1][1]; //stays same
                matrix[1][0] = matrix[2][1];

                // Zurücksetzen der nun leeren Felder
                matrix[0][2] = nullptr;
                matrix[0][1] = nullptr;
                matrix[2][1] = nullptr;

                angle = 0;
                break;
                
            default:
                break;
            }
        }
        
        BlueRicky::BlueRicky()
        {                       
            /*
                X A X       
                    X  */
            matrix[1][0] = new Tile(Color::blue);
            matrix[1][1] = new Tile(Color::blue);
            matrix[1][2] = new Tile(Color::blue);
            matrix[2][2] = new Tile(Color::blue);
            angle = 0;
        }
