#ifndef _tetrisblock_
#define _tetrisblock_
#include "../TetrisBlock.cpp"
#endif
class Smashboy:public TetrisBlock
{
    public:
        Smashboy(const TetrisBlock& block) : TetrisBlock(block)
        {
        }

        TetrisBlock* clone(TetrisBlock* block) override
        {
            auto a = new Smashboy(*block);
            return a;
        };
        
        void rotateRight() override
        {
            // Do nothing
        }
        Smashboy()
        {
            /*    X X     
                  A X  */
            matrix[0][1] = new Tile(Color::yellow);
            matrix[0][2] = new Tile(Color::yellow);
            matrix[1][1] = new Tile(Color::yellow);
            matrix[1][2] = new Tile(Color::yellow);
            angle = 0;
        }
};