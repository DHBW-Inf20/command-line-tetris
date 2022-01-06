
#include "Smashboy.h"

#include "../TetrisBlock.h"


		Smashboy::Smashboy(const TetrisBlock& block) : TetrisBlock(block)
        {
        }

        TetrisBlock* Smashboy::Clone()
        {
	        auto* const a = new Smashboy(*this);
            return a;
        };

        
        void Smashboy::RotateRight()
        {
            // Do nothing
        }
        Smashboy::Smashboy()
        {
            /*    X X     
                  A X  */
            matrix[0][1] = new Tile(Color::yellow);
            matrix[0][2] = new Tile(Color::yellow);
            matrix[1][1] = new Tile(Color::yellow);
            matrix[1][2] = new Tile(Color::yellow);
            angle = 0;
        }
