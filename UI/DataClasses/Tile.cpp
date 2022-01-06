#include "Tile.h"

#include "Color.h"


Tile::Tile(const Color col)
{
	this->color = col;
}

Tile::Tile()
{
	this->color = Color::white;
}

Color Tile::GetColor() const
{
	return this->color;
}
