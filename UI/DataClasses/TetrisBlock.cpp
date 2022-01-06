#include "TetrisBlock.h"


#include "../Config.h"
#include "../../Utilities/Utilities.h"

bool TetrisBlock::IsColumnEmpty(const int column)
{
	for (auto& i : matrix)
	{
		if (i[column] != nullptr)
		{
			return false; // Es gibt ein Element in dieser Spalte
		}
	}
	return true;
}

bool TetrisBlock::IsRowEmpty(const int row)
{
	for (unsigned int i = 0; i < matrix.size(); i++)
	{
		if (matrix[row][i] != nullptr)
			return false; // Es gibt ein Element in dieser Reihe
	}
	return true;
}

bool TetrisBlock::TryMoveLeft()
{
	if ((currentColumn > 0 && IsColumnEmpty(0)) || currentColumn > 1)
	{
		currentColumn--;
		return true;
	}
	return false;
}

bool TetrisBlock::TryMoveRight()
{
	if ((currentColumn < 9 && (IsColumnEmpty(3) && IsColumnEmpty(2))) || (currentColumn < 8 && IsColumnEmpty(3)) || (
		currentColumn < 7))
	{
		currentColumn++;
		return true;
	}
	return false;
}

bool TetrisBlock::TryMoveDown()
{
	if ((currentRow < rowCount - 2 && IsRowEmpty(3) && IsRowEmpty(2)) || (currentRow < rowCount - 3 && IsRowEmpty(3)) ||
		(currentRow < rowCount - 4))
	{
		currentRow++;
		return true;
	}
	return false;
}

TetrisBlock::TetrisBlock(): angle(0)
{
	matrix = Create2DArray<Tile*>(4, 4);
	/* 
        0 1 2 3 4 5 6 7 8 9 10 11
      0 W N N N M M M M N N N  W
      1 W N N N M A M M N N N  W
      2 W N N N M M M M N N N  W
      3 W N N N M M M M N N N  W
      4 W N N N N N N N N N N  W
     */
	currentRow = 2;
	currentColumn = 5;
}

TetrisBlock::TetrisBlock(const TetrisBlock& block)
{
	angle = block.angle;
	currentRow = block.currentRow;
	currentColumn = block.currentColumn;
	matrix = block.matrix;
}

TetrisBlock::~TetrisBlock()
{
}

bool TetrisBlock::TryRotateRight()
{
	RotateRight();
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			if (matrix[i][j] != nullptr)
			{
				if (i + currentRow >= rowCount - 1 || j + currentColumn >= columnCount - 1 || i + currentRow < 1 || i +
					currentColumn < 1)
				{
					RotateRight(); //Originaldrehung wiederherstellen
					RotateRight();
					RotateRight();
					return false;
				}
			}
		}
	}
	return true;
}

std::vector<std::vector<Tile*>> TetrisBlock::BuildMatrix()
{
	auto field = Create2DArray<Tile*>(rowCount, columnCount);

	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			if (i + currentRow < rowCount && j + currentColumn < columnCount)
				//Ist der Block ganz am Boden können Teile der Matrix mit Verschiebung außerhalb des Spielfelds sein (diese werden igonoriert)
			{
				field[i + currentRow][j + currentColumn] = matrix[i][j];
			}
		}
	}
	return field;
}

