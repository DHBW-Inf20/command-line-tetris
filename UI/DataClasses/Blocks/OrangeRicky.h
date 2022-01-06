#ifndef ORANGERICKY_H
#define ORANGERICKY_H



#include "../TetrisBlock.h"


class OrangeRicky: public TetrisBlock
{
public:
    OrangeRicky(const TetrisBlock& block);
    TetrisBlock* Clone() override;
    void RotateRight() override;
    OrangeRicky();
};



#endif // ORANGERICKY_H