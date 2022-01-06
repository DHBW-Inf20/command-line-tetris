#ifndef SMASHBOY_H
#define SMASHBOY_H


#include "../TetrisBlock.h"


class Smashboy : public TetrisBlock
{
public:
    Smashboy(const TetrisBlock& block);
    TetrisBlock* Clone() override;
    void RotateRight() override;
    Smashboy();
};


#endif // SMASHBOY_H