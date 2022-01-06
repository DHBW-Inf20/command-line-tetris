#ifndef CLEVERLANDZ_H
#define CLEVERLANDZ_H
#include "../TetrisBlock.h"


class CleverlandZ : public TetrisBlock
{
public:
    CleverlandZ(const TetrisBlock& block);
    TetrisBlock* Clone() override;
    void RotateRight() override;
    CleverlandZ();
};

#endif //CLEVERLAND_H
