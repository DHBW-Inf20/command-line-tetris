#ifndef TETRISBLOCK_H
#define TETRISBLOCK_H

#include "Tile.h"


#include "../../Utilities/Utilities.h"



class TetrisBlock
{

protected:
    std::vector<std::vector<Tile*>> matrix; // [Reihe][Spalte] -> [Y][X]
    int angle;
    int currentRow;
    int currentColumn;
    virtual void RotateRight() = 0;


    /*
        xxxx
        xOxx   <-- Ankerpunkt in der 4x4 Matrix
        xxxx
        xxxx
    */

public:
    virtual TetrisBlock* Clone() = 0;
    bool IsColumnEmpty(int column);

    bool IsRowEmpty(int row);

    bool TryMoveLeft();

    bool TryMoveRight();

    bool TryMoveDown();

    TetrisBlock();

    TetrisBlock(const TetrisBlock& block);


    bool TryRotateRight();

    std::vector<std::vector<Tile*>> BuildMatrix();
    // Erbende Klassen ggf. noch eine Init-Methode, wo die 4x4-Matrix bef�llt wird    

};

#endif //TETRISBLOCK_H
