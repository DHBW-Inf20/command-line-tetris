#ifndef TILE_H
#define TILE_H

#include "Color.h"

class Tile
{
private:
    Color color;
public:
    Tile(Color col);

    Tile();
    Tile(const Tile& tile);

    Tile* Clone();

    Color GetColor() const;
};

#endif // TILE_H
