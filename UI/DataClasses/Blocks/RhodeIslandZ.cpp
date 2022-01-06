#include "../TetrisBlock.h"
#include "RhodeIslandZ.h"


		RhodeIslandZ::RhodeIslandZ(const TetrisBlock& block) : TetrisBlock(block)
        {
        }

        TetrisBlock* RhodeIslandZ::Clone()
        {
	        auto* const a = new RhodeIslandZ(*this);
            return a;
        };

        
        void RhodeIslandZ::RotateRight()
        {
            switch (angle)
            {
            case 0:
            /* case 180: */
                /*    X    
                      A X
                        X   */
                matrix[0][1] = matrix[1][0];
                matrix[1][2] = matrix[0][1];
                matrix[1][1] = matrix[1][1]; // same
                matrix[2][2] = matrix[0][2];
                angle = 90;

                // Zurücksetzen der nicht mehr genutzten Felder
                matrix[1][0] = nullptr;
                matrix[0][2] = nullptr;

                break;
            
            case 90:
            /* case 270: */
                /*    X X     
                    X A    */
                matrix[0][1] = matrix[1][2];
                matrix[0][2] = matrix[2][2];
                matrix[1][1] = matrix[1][1]; // same
                matrix[1][0] = matrix[0][1];
                angle = 0;

                // Zurücksetzen der nicht mehr genutzten Felder
                matrix[1][2] = nullptr;
                matrix[2][2] = nullptr;

                break;

            default:
                break;
            }
        }
        RhodeIslandZ::RhodeIslandZ()
        {
            /*    X X     
                X A    */
            matrix[0][2] = new Tile(Color::green);
            matrix[0][1] = new Tile(Color::green);
            matrix[1][1] = new Tile(Color::green);
            matrix[1][0] = new Tile(Color::green);
            angle = 0; 
        }
