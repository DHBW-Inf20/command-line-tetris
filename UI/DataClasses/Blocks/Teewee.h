#ifndef TEEWEE_H
#define TEEWEE_H



#include "../TetrisBlock.h"


class Teewee : public TetrisBlock
{
public:
    Teewee(const TetrisBlock& block);
    TetrisBlock* Clone() override;
    void RotateRight() override;
    Teewee();
};


#endif // TEEWEE_H
