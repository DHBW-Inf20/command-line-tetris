#ifndef RHODEISLANDZ_H
#define RHODEISLANDZ_H



#include "../TetrisBlock.h"


class RhodeIslandZ : public TetrisBlock
{
public:
    RhodeIslandZ(const TetrisBlock& block);
    TetrisBlock* Clone() override;
    void RotateRight() override;
    RhodeIslandZ();
};
#endif // RHODEISLANDZ_H