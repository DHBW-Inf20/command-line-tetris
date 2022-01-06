#ifndef HERO_H
#define HERO_H


#include "../TetrisBlock.h"


class Hero : public TetrisBlock
{
public:
	Hero(const TetrisBlock& block);
	TetrisBlock* Clone() override;
	void RotateRight() override;
	Hero();
};


#endif // HERO_H
