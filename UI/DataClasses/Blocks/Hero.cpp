#include "../TetrisBlock.h"
#include "Hero.h"

#include "../../../Utilities/MemoryLeakDetection.h"

Hero::Hero(const TetrisBlock& block): TetrisBlock(block)
{
	
}

TetrisBlock* Hero::Clone()
{
	auto* const a = new Hero(*this);
	return a;
}

void Hero::RotateRight()
{
	switch (angle)
	{
	case 0:
		/* case 180: */
		// Color of Tiles: Turquise
		/*    X
		      A 
		      X
		      X */
		matrix[0][1] = matrix[1][0];
		matrix[1][1] = matrix[1][1]; // stays same
		matrix[2][1] = matrix[1][2];
		matrix[3][1] = matrix[1][3];

		// Zurücksetzen der nun leeren Felder
		matrix[1][0] = nullptr;
		matrix[1][2] = nullptr;
		matrix[1][3] = nullptr;

		angle = 90;
		break;
	case 90:
		/* case 270: */
		/*  
		    X A X X  */
		matrix[1][0] = matrix[0][1];
		matrix[1][1] = matrix[1][1]; // stays same
		matrix[1][2] = matrix[2][1];
		matrix[1][3] = matrix[3][1];

		// Zurücksetzen der nun leeren Felder
		matrix[0][1] = nullptr;
		matrix[2][1] = nullptr;
		matrix[3][1] = nullptr;

		angle = 0;
		break;
	default:
		break;
	}
}

Hero::Hero()
{
	// Color of Tiles: Turquise
	/*  
	    X A X X  */
	matrix[1][0] = new Tile(Color::turquoise);
	matrix[1][1] = new Tile(Color::turquoise);
	matrix[1][2] = new Tile(Color::turquoise);
	matrix[1][3] = new Tile(Color::turquoise);
	angle = 0;
}
