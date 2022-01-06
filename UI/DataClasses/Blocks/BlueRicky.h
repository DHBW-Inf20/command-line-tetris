#ifndef BLUERICKY_H
#define BLUERICKY_H



#include "../TetrisBlock.h"


class BlueRicky : public TetrisBlock
{
public:
   BlueRicky();
   BlueRicky(const TetrisBlock& block);
	
    TetrisBlock* Clone() override;
    void RotateRight() override;
};

#endif // BLUERICKY_H
